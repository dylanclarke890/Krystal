#include "IO/Compression/HuffmanEncoder.hpp"

namespace Krys::IO
{
  NO_DISCARD string HuffmanEncoder::Encode(const List<uchar> &data) noexcept
  {
    _frequencies = GenerateFrequencies(data);
    _tree.Init(_frequencies);

    string encoded;
    for (uchar c : data)
      encoded += _tree.GetCode(c);
    return encoded;
  }

  NO_DISCARD string HuffmanEncoder::Encode(const string &text) noexcept
  {
    List<uchar> data(text.begin(), text.end());
    return Encode(data);
  }

  NO_DISCARD const HuffmanEncoder::freq_map_t &HuffmanEncoder::GetFrequencies() const noexcept
  {
    return _frequencies;
  }

  HuffmanEncoder::freq_map_t HuffmanEncoder::GenerateFrequencies(const List<uchar> &data) const noexcept
  {
    freq_map_t frequencies;
    for (uchar c : data)
      frequencies[c]++;

    return frequencies;
  }
}