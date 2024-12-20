#include "IO/Compression/HuffmanEncoder.hpp"

namespace Krys::IO
{
  using freq_map_t = Map<uchar, uint>;

  NO_DISCARD const freq_map_t &HuffmanEncoder::GetFrequencies() const noexcept
  {
    return _frequencies;
  }

  NO_DISCARD string HuffmanEncoder::Encode(const string &text) noexcept
  {
    _frequencies = GenerateFrequencies(text);
    _tree.Init(_frequencies);

    string encoded;
    for (char c : text)
      encoded += _tree.GetCode(static_cast<uchar>(c));
    return encoded;
  }

  NO_DISCARD string HuffmanEncoder::Encode(const List<uchar> &data) noexcept
  {
    _frequencies = GenerateFrequencies(data);
    _tree.Init(_frequencies);

    string encoded;
    for (uchar c : data)
      encoded += _tree.GetCode(c);
    return encoded;
  }

  freq_map_t HuffmanEncoder::GenerateFrequencies(const string &data) const noexcept
  {
    freq_map_t frequencies;
    for (char c : data)
      frequencies[static_cast<uchar>(c)]++;

    return frequencies;
  }

  freq_map_t HuffmanEncoder::GenerateFrequencies(const List<uchar> &data) const noexcept
  {
    freq_map_t frequencies;
    for (uchar c : data)
      frequencies[c]++;

    return frequencies;
  }
}