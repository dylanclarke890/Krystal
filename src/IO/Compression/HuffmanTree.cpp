#include "IO/Compression/HuffmanTree.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::IO
{
  HuffmanTree::HuffmanTree() noexcept : _root(nullptr)
  {
  }

  HuffmanTree::HuffmanTree(const HuffmanTree &other) noexcept
      : _root(other._root), _huffmanCodes(other._huffmanCodes)
  {
  }

  void HuffmanTree::Init(const HuffmanTree::freq_map_t &frequencies) noexcept
  {
    InitTree(frequencies);
    GenerateCodes(_root, "");
  }

  void HuffmanTree::InitTree(const HuffmanTree::freq_map_t &frequencies) noexcept
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

  void HuffmanTree::GenerateCodes(const Ref<HuffmanTreeNode> &node, const string &currentCode) noexcept
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

  NO_DISCARD string HuffmanTree::GetCode(uchar symbol) const noexcept
  {
    KRYS_ASSERT(!_huffmanCodes.empty(), "Tree was not initialised", 0);
    return _huffmanCodes.at(symbol);
  }

  NO_DISCARD HuffmanTree::node_t HuffmanTree::GetRoot() const noexcept
  {
    return _root;
  }
}