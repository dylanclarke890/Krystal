#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"

namespace Krys::IO
{
  // TODO: implement relevant suggestions from AVA
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

  struct HuffmanNodeComparator
  {
    bool operator()(const Ref<HuffmanTreeNode> &a, const Ref<HuffmanTreeNode> &b) noexcept
    {
      return a->Frequency > b->Frequency; // lowest frequency has highest priority
    }
  };
  class HuffmanTree
  {

  public:
    HuffmanTree() noexcept : _root(nullptr)
    {
    }

    HuffmanTree(const Map<uchar, uint> &frequencies) noexcept : _root(nullptr)
    {
      BuildNodes(frequencies);
      GenerateCodes(_root, "");
    }

    /// @brief Encode a given text string into a binary string.
    NO_DISCARD string Encode(const string &text) noexcept
    {
      if (!_root)
      {
        const Map<uchar, uint> frequencies = GenerateFrequencies(text);
        BuildNodes(frequencies);
        GenerateCodes(_root, "");
      }

      string encoded;
      for (char c : text)
        encoded += _huffmanCodes.at(static_cast<uchar>(c));
      return encoded;
    }

    /// @brief Encode a list of binary data into a binary string.
    NO_DISCARD string Encode(const List<uchar> &data) noexcept
    {
      if (!_root)
      {
        const Map<uchar, uint> frequencies = GenerateFrequencies(data);
        BuildNodes(frequencies);
        GenerateCodes(_root, "");
      }

      string encoded;
      for (uchar c : data)
        encoded += _huffmanCodes.at(c);
      return encoded;
    }

    /// @brief Decode a binary string into the original text or data.
    NO_DISCARD string Decode(const string &binaryInput) noexcept
    {
      string decoded;
      Ref<HuffmanTreeNode> current = _root;

      for (char bit : binaryInput)
      {
        if (bit == '0')
          current = current->Left;
        else if (bit == '1')
          current = current->Right;

        // If a leaf node is reached
        if (!current->Left && !current->Right)
        {
          decoded += static_cast<char>(current->Symbol);
          current = _root; // Reset to the root for the next symbol
        }
      }

      return decoded;
    }

    /// @brief Decode a list of binary data into the original text or data.
    NO_DISCARD string Decode(const List<uchar> &binaryData) noexcept
    {
      string decoded;
      Ref<HuffmanTreeNode> current = _root;

      for (uchar bit : binaryData)
      {
        if (bit == '0')
          current = current->Left;
        else if (bit == '1')
          current = current->Right;

        // If a leaf node is reached
        if (!current->Left && !current->Right)
        {
          decoded += static_cast<char>(current->Symbol);
          current = _root; // Reset to the root for the next symbol
        }
      }

      return decoded;
    }

  private:
    /// @brief Constructs the Huffman tree.
    void BuildNodes(const Map<uchar, uint> &frequencies) noexcept
    {
      using min_heap_t =
        std::priority_queue<Ref<HuffmanTreeNode>, List<Ref<HuffmanTreeNode>>, HuffmanNodeComparator>;

      min_heap_t frequencyHeap;
      for (const auto &pair : frequencies)
        frequencyHeap.push(CreateRef<HuffmanTreeNode>(pair.first, pair.second));

      while (frequencyHeap.size() > 1)
      {
        Ref<HuffmanTreeNode> left = frequencyHeap.top();
        frequencyHeap.pop();
        Ref<HuffmanTreeNode> right = frequencyHeap.top();
        frequencyHeap.pop();

        auto internalNode = CreateRef<HuffmanTreeNode>('\0', left->Frequency + right->Frequency);
        internalNode->Left = left;
        internalNode->Right = right;
        frequencyHeap.push(internalNode);
      }

      _root = frequencyHeap.top();
      frequencyHeap.pop();
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

    /// @brief Generates a frequency map from a list of binary data.
    Map<uchar, uint> GenerateFrequencies(const List<uchar> &data) noexcept
    {
      Map<uchar, uint> frequencies;
      for (uchar c : data)
        frequencies[c]++;

      return frequencies;
    }

    /// @brief Generates a frequency map from a text string.
    Map<uchar, uint> GenerateFrequencies(const string &data) noexcept
    {
      Map<uchar, uint> frequencies;
      for (char c : data)
        frequencies[static_cast<uchar>(c)]++;

      return frequencies;
    }

  private:
    Ref<HuffmanTreeNode> _root;
    Map<uchar, string> _huffmanCodes;
  };
}