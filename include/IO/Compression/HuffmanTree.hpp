#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::IO
{
  struct HuffmanTreeNode
  {
    uchar Symbol;
    int Frequency;
    Ref<HuffmanTreeNode> Left, Right;

    HuffmanTreeNode(uchar symbol, int freq) noexcept
        : Symbol(symbol), Frequency(freq), Left(nullptr), Right(nullptr)
    {
    }
  };

  class HuffmanTree
  {
  private:
    using node_t = Ref<HuffmanTreeNode>;
    using huffman_codes_t = Map<uchar, string>;
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

    HuffmanTree(const HuffmanTree &other) noexcept : _root(other._root), _huffmanCodes(other._huffmanCodes)
    {
    }

    void Init(const freq_map_t &frequencies) noexcept
    {
      InitTree(frequencies);
      GenerateCodes(_root, "");
    }

    NO_DISCARD node_t GetRoot() const noexcept
    {
      return _root;
    }

    NO_DISCARD string GetCode(uchar symbol) const noexcept
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
    void GenerateCodes(const Ref<HuffmanTreeNode> &node, const string &currentCode) noexcept
    {
      if (!node)
        return;

      // If it's a leaf node, add the symbol and its code to the map
      if (!node->Left && !node->Right)
      {
        _huffmanCodes[node->Symbol] = currentCode;
        return;
      }

      GenerateCodes(node->Left, currentCode + "0");
      GenerateCodes(node->Right, currentCode + "1");
    }

  private:
    node_t _root;
    huffman_codes_t _huffmanCodes;
  };
}