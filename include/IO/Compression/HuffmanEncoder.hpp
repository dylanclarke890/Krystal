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
    /// @brief Encode a list of binary data into a binary string.
    NO_DISCARD string Encode(const List<uchar> &data) noexcept
    {
      _frequencies = GenerateFrequencies(data);
      _tree.Init(_frequencies);

      string encoded;
      for (uchar c : data)
        encoded += _tree.GetCode(c);
      return encoded;
    }

    /// @brief Encode a text string into a binary string.
    NO_DISCARD string Encode(const string &text) noexcept
    {
      List<uchar> data(text.begin(), text.end());
      return Encode(data);
    }

    /// @brief Gets the frequencies used for the latest encoding run. Will be null if no encoding has been
    /// done yet.
    NO_DISCARD const freq_map_t &GetFrequencies() const noexcept
    {
      return _frequencies;
    }

  private:
    /// @brief Returns a map of symbols to the frequencies they are used within the list of data.
    freq_map_t GenerateFrequencies(const List<uchar> &data) const noexcept
    {
      freq_map_t frequencies;
      for (uchar c : data)
        frequencies[c]++;

      return frequencies;
    }

  private:
    HuffmanTree _tree;
    freq_map_t _frequencies;
  };
}