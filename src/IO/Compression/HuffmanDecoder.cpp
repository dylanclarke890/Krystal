#include "IO/Compression/HuffmanDecoder.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::IO
{
  HuffmanDecoder::HuffmanDecoder(const HuffmanTree &tree) noexcept : _tree(tree)
  {
  }

  NO_DISCARD string HuffmanDecoder::Decode(const string &input) const noexcept
  {
    auto root = _tree.GetRoot();
    KRYS_ASSERT(root, "Tree was not initialised", 0);
    auto current = root;

    string decoded;
    for (char bit : input)
    {
      if (bit == '0')
        current = current->Left;
      else if (bit == '1')
        current = current->Right;

      // If a leaf node is reached
      if (!current->Left && !current->Right)
      {
        decoded += static_cast<char>(current->Symbol);
        current = root; // Reset to the root for the next symbol
      }
    }

    return decoded;
  }

  NO_DISCARD string HuffmanDecoder::Decode(const List<uchar> &input) const noexcept
  {
    auto root = _tree.GetRoot();
    KRYS_ASSERT(root, "Tree was not initialised", 0);
    auto current = root;

    string decoded;
    for (uchar bit : input)
    {
      if (bit == '0')
        current = current->Left;
      else if (bit == '1')
        current = current->Right;

      // If a leaf node is reached
      if (!current->Left && !current->Right)
      {
        decoded += static_cast<char>(current->Symbol);
        current = root; // Reset to the root for the next symbol
      }
    }
    return decoded;
  }
}