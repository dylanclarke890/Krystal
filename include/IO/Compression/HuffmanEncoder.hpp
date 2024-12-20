#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "IO/Compression/HuffmanTree.hpp"

namespace Krys::IO
{
  class HuffmanEncoder
  {
    using freq_map_t = Map<uchar, uint>;

  public:
    /// @brief Encode a text string into a binary string.
    NO_DISCARD string Encode(const string &text) noexcept;

    /// @brief Encode a list of binary data into a binary string.
    NO_DISCARD string Encode(const List<uchar> &data) noexcept;

    NO_DISCARD const freq_map_t &GetFrequencies() const noexcept;

  private:
    /// @brief Generates a frequency map from a list of binary data.
    freq_map_t GenerateFrequencies(const List<uchar> &data) const noexcept;

    /// @brief Generates a frequency map from a text string.
    freq_map_t GenerateFrequencies(const string &data) const noexcept;

  private:
    HuffmanTree _tree;
    freq_map_t _frequencies;
  };
}