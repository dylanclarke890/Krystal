#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::IO
{
  struct HuffmanTreeNode
  {
    uchar Symbol;
    uint Frequency;
    Ref<HuffmanTreeNode> Left, Right;

    HuffmanTreeNode(uchar symbol, uint freq) noexcept
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
    using huffman_codes_t = Map<uchar, code_t>;
    using freq_map_t = Map<uchar, uint>;

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

    NO_DISCARD code_t GetCode(uchar symbol) const noexcept
    {
      KRYS_ASSERT(!_huffmanCodes.empty(), "Tree was not initialised", 0);
      return _huffmanCodes.at(symbol);
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

        auto internalNode = CreateRef<HuffmanTreeNode>('\0', left->Frequency + right->Frequency);
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