#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "IO/Readers/BitReader.hpp"
#include "IO/Writers/BitWriter.hpp"
#include "Utils/Bytes.hpp"

#include <algorithm>
#include <numeric>

namespace Krys::IO
{
  struct HuffmanTreeNode
  {
    byte Symbol;
    uint Frequency;
    Ref<HuffmanTreeNode> Left, Right;

    HuffmanTreeNode(const byte symbol, uint freq) noexcept
        : Symbol(symbol), Frequency(freq), Left(nullptr), Right(nullptr)
    {
    }
  };

  template <IsIntegralT TCode>
  class HuffmanTree
  {
  public:
    struct HuffmanCode
    {
      TCode Code;
      uint16 Length;
    };

  private:
    using node_t = Ref<HuffmanTreeNode>;
    using code_t = HuffmanCode;
    using huffman_codes_t = Map<byte, code_t>;
    using freq_map_t = Map<byte, uint>;

    struct Compare
    {
      bool operator()(const node_t &a, const node_t &b) const noexcept
      {
        // Rule 1: Compare frequencies (lower frequency has higher priority)
        if (a->Frequency != b->Frequency)
          return a->Frequency > b->Frequency;

        // Rule 2: If frequencies are equal, prioritize leaf nodes
        bool aIsLeaf = !a->Left && !a->Right;
        bool bIsLeaf = !b->Left && !b->Right;

        if (aIsLeaf != bIsLeaf)
          return bIsLeaf; // Leaf nodes have higher priority

        // Rule 3: If both are leaf nodes, order by ASCII value
        if (aIsLeaf && bIsLeaf)
          return a->Symbol > b->Symbol;

        // Rule 4: For non-leaf nodes, order by creation time (arbitrary fallback)
        return false;
      }
    };
    using min_heap_t = std::priority_queue<node_t, List<node_t>, Compare>;

  public:
    HuffmanTree() noexcept : _root(nullptr)
    {
    }

    HuffmanTree(const HuffmanTree<TCode> &other) noexcept
        : _root(other._root), _huffmanCodes(other._huffmanCodes)
    {
    }

    void Init(const freq_map_t &frequencies) noexcept
    {
      InitTree(frequencies);
      GenerateCodes(_root, 0, 0);
    }

    void SetRoot(const node_t &root) noexcept
    {
      _root = root;
    }

    NO_DISCARD node_t GetRoot() const noexcept
    {
      return _root;
    }

    NO_DISCARD code_t GetCode(byte symbol) const noexcept
    {
      KRYS_ASSERT(!_huffmanCodes.empty(), "Tree was not initialised", 0);
      return _huffmanCodes.at(symbol);
    }

    NO_DISCARD const huffman_codes_t &GetCodes() const noexcept
    {
      return _huffmanCodes;
    }

  private:
    void InitTree(const freq_map_t &frequencies) noexcept
    {
      min_heap_t frequencyHeap;
      for (const auto &pair : frequencies)
        frequencyHeap.push(CreateRef<HuffmanTreeNode>(pair.first, pair.second));

      while (frequencyHeap.size() > 1)
      {
        node_t left = frequencyHeap.top();
        frequencyHeap.pop();
        node_t right = frequencyHeap.top();
        frequencyHeap.pop();

        auto internalNode = CreateRef<HuffmanTreeNode>(byte {0}, left->Frequency + right->Frequency);
        internalNode->Left = left;
        internalNode->Right = right;
        frequencyHeap.push(internalNode);
      }

      _root = frequencyHeap.top();
    }

    /// @brief Generates Huffman codes for the current tree.
    void GenerateCodes(const Ref<HuffmanTreeNode> &node, const TCode &code, const uint16 codeLength) noexcept
    {
      if (!node)
        return;

      // If it's a leaf node, add the symbol and its code to the map
      if (!node->Left && !node->Right)
      {
        _huffmanCodes[node->Symbol] = code_t {code, codeLength};
        return;
      }

      GenerateCodes(node->Left, code << 1, codeLength + 1);
      GenerateCodes(node->Right, code << 1 | 1, codeLength + 1);
    }

  private:
    node_t _root;
    huffman_codes_t _huffmanCodes;
  };
}

namespace Krys::IO::Stage
{
  template <IsIntegralT TCode, Endian::Type TSource, Endian::Type TDestination>
  struct HuffmanEncoder
  {
  public:
    using input_t = List<byte>;
    using output_t = List<byte>;
    using freq_map_t = Map<byte, uint>;
    using tree_t = HuffmanTree<TCode>;
    using code_t = HuffmanTree<TCode>::HuffmanCode;
    using bit_writer_t = BitWriter;

    constexpr void Setup() noexcept
    {
    }

    constexpr output_t ProcessChunk(const input_t &data) noexcept
    {
      // The output format is as follows:
      // 4 bytes - The length of the compressed data (in bits).
      // 4 bytes - The length of the tree (in bits).
      // 4 bytes - The length of the original data (in bytes).
      // n bytes - The tree data.
      // m bytes - The compressed data.

      freq_map_t frequencies {};
      for (const byte symbol : data)
        frequencies[symbol]++;
      tree_t tree {};
      tree.Init(frequencies);

      List<byte> treeData {};
      uint32 treeLengthBits = 0;

      bit_writer_t writer(&treeData);
      WriteTree(tree.GetRoot(), writer, treeLengthBits);
      writer.Write(false); // End of tree
      treeLengthBits++;
      writer.Flush();

      List<code_t> encodedData {};
      encodedData.reserve(data.size());
      uint32 encodedDataLength = 0;

      for (const byte symbol : data)
      {
        const auto code = tree.GetCode(symbol);
        encodedData.emplace_back(code);
        encodedDataLength += code.Length;
      }

      List<byte> output {};
      output.append_range(Bytes::From<uint32, TSource, TDestination>(encodedDataLength));
      output.append_range(Bytes::From<uint32, TSource, TDestination>(treeLengthBits));
      output.append_range(Bytes::From<uint32, TSource, TDestination>(static_cast<uint32>(data.size())));

      output.append_range(treeData);

      writer.SetBuffer(&output);
      for (const auto &code : encodedData)
        writer.Write(code.Code, code.Length);
      writer.Flush();

      return output;
    }

    constexpr void Teardown() noexcept
    {
    }

    constexpr void WriteTree(const Ref<HuffmanTreeNode> &node, bit_writer_t &writer,
                             uint32 &treeLengthBits) noexcept
    {
      if (!node)
        return;

      treeLengthBits++;
      if (!node->Left && !node->Right)
      {
        writer.Write(true);
        writer.Write(node->Symbol);
      }
      else
      {
        WriteTree(node->Left, writer, treeLengthBits);
        WriteTree(node->Right, writer, treeLengthBits);
        writer.Write(false);
      }
    }
  };

  template <IsIntegralT TCode, Endian::Type TSource, Endian::Type TDestination>
  struct HuffmanDecoder
  {
  public:
    using input_t = List<byte>;
    using output_t = List<byte>;
    using freq_map_t = Map<byte, uint>;
    using tree_t = HuffmanTree<TCode>;
    using code_t = HuffmanTree<TCode>::HuffmanCode;
    using bit_reader_t = BitReader<TSource, TDestination>;

    constexpr void Setup() noexcept
    {
    }

    constexpr output_t ProcessChunk(input_t data) noexcept
    {
      bit_reader_t reader(&data);
      const uint32 encodedDataLength = reader.template Read<uint32>();
      const uint32 treeLengthBits = reader.template Read<uint32>();
      const uint32 originalDataLength = reader.template Read<uint32>();

      tree_t tree = ReadTree(reader, treeLengthBits);
      auto root = tree.GetRoot();

      List<byte> output {};
      output.reserve(originalDataLength);

      Ref<HuffmanTreeNode> current = root;
      for (uint32 i = 0; i < encodedDataLength; i++)
      {
        if (static_cast<uint>(reader.ReadBit()) == uint {1})
          current = current->Right;
        else
          current = current->Left;

        if (!current->Left && !current->Right)
        {
          output.push_back(current->Symbol);
          current = root;
        }
      }

      KRYS_ASSERT(output.size() == originalDataLength, "Output size mismatch", 0);
      return output;
    }

    constexpr tree_t ReadTree(bit_reader_t &reader, const uint32 treeLengthBits) noexcept
    {
      List<Ref<HuffmanTreeNode>> nodes {};

      for (uint32 i = 0; i < treeLengthBits - 1; i++)
      {
        if (static_cast<uint>(reader.ReadBit()) == uint {1})
        {
          nodes.push_back(CreateRef<HuffmanTreeNode>(reader.ReadBits(8), 0));
        }
        else
        {
          auto internalNode = CreateRef<HuffmanTreeNode>(byte {0}, 0);
          internalNode->Right = nodes.back();
          nodes.pop_back();
          internalNode->Left = nodes.back();
          nodes.pop_back();
          nodes.push_back(internalNode);
        }
      }

      KRYS_ASSERT(nodes.size() == 1, "One node was not left in the list by the end of the tree construction.",
                  0);
      KRYS_ASSERT_ALWAYS_EVAL(reader.ReadBit() == 0, "Tree did not end in a zero.", 0);
      reader.NextByte(); // skip padding bits and align to byte boundary.

      tree_t tree {};
      tree.SetRoot(nodes.back());

      return tree;
    }

    constexpr void Teardown() noexcept
    {
    }
  };
}