#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "IO/Compression/HuffmanTree.hpp"

namespace Krys::IO
{
  class HuffmanDecoder
  {
  public:
    HuffmanDecoder(const HuffmanTree &tree) noexcept;

    /// @brief Decode a binary string into the original text or data.
    NO_DISCARD string Decode(const string &input) const noexcept;

    /// @brief Decode a list of binary data into the original text or data.
    NO_DISCARD string Decode(const List<uchar> &input) const noexcept;

  private:
    HuffmanTree _tree;
  };
}