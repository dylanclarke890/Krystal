#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "IO/Compression/HuffmanTree.hpp"

namespace Krys::IO
{
  class HuffmanDecoder
  {
  public:
    HuffmanDecoder(const HuffmanTree &tree) noexcept : _tree(tree)
    {
    }

    /// @brief Decode a binary string into the original text or data.
    NO_DISCARD string Decode(const string &input) const noexcept
    {
      List<uchar> data(input.begin(), input.end());
      return Decode(data);
    }

    /// @brief Decode a list of binary data into the original text or data.
    NO_DISCARD string Decode(const List<uchar> &data) const noexcept
    {
      auto root = _tree.GetRoot();
      KRYS_ASSERT(root, "Tree was not initialised", 0);
      auto current = root;

      string decoded;
      for (uchar bit : data)
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

  private:
    HuffmanTree _tree;
  };
}