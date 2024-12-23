#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Types.hpp"
#include "IO/BinaryFileReader.hpp"
#include "IO/BitWriter.hpp"
#include "IO/Compression/HuffmanTree.hpp"

#include <algorithm>
#include <numeric>

namespace Krys::IO
{
  template <IsIntegralT TCode, Endian::Type TDestination>
  class HuffmanEncoder
  {
    using freq_map_t = Map<uchar, uint>;
    using tree_t = HuffmanTree<TCode>;
    using code_t = HuffmanTree<TCode>::HuffmanCode;
    using bit_writer_t = BitWriter<TCode, TDestination>;
    using binary_reader_t = BinaryFileReader<Endian::Type::System, Endian::Type::System>;

  public:
    HuffmanEncoder(const string &fileIn, const string &fileOut) noexcept : _fileIn(fileIn), _fileOut(fileOut)
    {
    }

    NO_DISCARD void Encode() noexcept
    {
      binary_reader_t reader(_fileIn);
      reader.OpenStream();
      auto data = reader.ReadAllBytes();
      reader.CloseStream();

      freq_map_t frequencies;
      for (const auto &symbol : data)
        frequencies[static_cast<uchar>(symbol)]++;
      _tree.Init(frequencies);
      _frequencies = frequencies;

      List<code_t> codes;
      codes.reserve(data.size());
      uint32 sizeInBits = 0;

      for (const auto &symbol : data)
      {
        const auto code = _tree.GetCode(static_cast<uchar>(symbol));
        codes.emplace_back(code);
        sizeInBits += code.Length;
      }

      bit_writer_t writer(_fileOut);

      const auto WriteHuffmanCode = [&](const code_t &huffmanCode)
      {
        for (auto i = huffmanCode.Length - 1; i >= 0; i--)
        {
          bool bit = ((huffmanCode.Code >> i) & 1) != 0;
          writer.Write(bit);
        }
      };

      writer.GetBinaryWriter().Write<uint32>(sizeInBits);
      std::for_each(codes.begin(), codes.end(), WriteHuffmanCode);
    }

    const tree_t &GetTree() const noexcept
    {
      return _tree;
    }

  private:
    string _fileIn, _fileOut;
    freq_map_t _frequencies;
    tree_t _tree;
  };
}