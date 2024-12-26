#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
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
        return a->Frequency > b->Frequency; // lowest frequency has highest priority
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

    constexpr static void Setup() noexcept
    {
    }

    constexpr static output_t Execute(const input_t &data) noexcept
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

    constexpr static void Teardown() noexcept
    {
    }

    constexpr static void WriteTree(const Ref<HuffmanTreeNode> &node, bit_writer_t &writer,
                                    uint32 &treeLengthBits) noexcept
    {
      if (!node)
        return;

      if (!node->Left && !node->Right)
      {
        writer.Write(true);
        writer.Write(node->Symbol);
        treeLengthBits += 9;
      }
      else
      {
        writer.Write(false);
        treeLengthBits++;
        WriteTree(node->Left, writer, treeLengthBits);
        WriteTree(node->Right, writer, treeLengthBits);
      }
    }
  };

  template <typename TInput, typename TOutput>
  struct HuffmanDecoder
  {
  public:
    using input_t = TInput;
    using output_t = TOutput;

    constexpr static void Setup() noexcept
    {
    }

    constexpr static TOutput Execute(TInput data) noexcept
    {
      return data;
    }

    constexpr static void Teardown() noexcept
    {
    }
  };
}