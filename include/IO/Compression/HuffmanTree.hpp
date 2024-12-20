#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"

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
    HuffmanTree() noexcept;
    HuffmanTree(const HuffmanTree &other) noexcept;

    void Init(const freq_map_t &frequencies) noexcept;

    NO_DISCARD node_t GetRoot() const noexcept;
    NO_DISCARD string GetCode(uchar symbol) const noexcept;

  private:
    void InitTree(const freq_map_t &frequencies) noexcept;

    /// @brief Generates Huffman codes for the current tree.
    void GenerateCodes(const Ref<HuffmanTreeNode> &node, const string &currentCode) noexcept;

  private:
    node_t _root;
    huffman_codes_t _huffmanCodes;
  };
}