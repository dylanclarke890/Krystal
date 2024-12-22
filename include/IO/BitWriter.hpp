#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Endian.hpp"
#include "Base/Types.hpp"
#include "IO/BinaryFileWriter.hpp"

#include <bitset>

namespace Krys::IO
{
  // TODO: customize for different padding requirements for partial buffer writes
  // Do we pad them to the left or right?
  // Do we pad them with 1s or 0s?
  // Right now, we're just going to cast the buffer as-is.
  template <IsIntegralT T, Endian::Type TDestination>
  class BitWriter
  {
  public:
    BitWriter(const string &filepath) noexcept : _buffer(0), _bufferIndex(0), _writer(filepath)
    {
      _writer.OpenStream();
    }

    ~BitWriter() noexcept
    {
      if (_bufferIndex > 0)
        Flush();

      _writer.CloseStream();
    }

    void Write(bool bit) noexcept
    {
      _buffer.set(_bufferIndex, bit);
      _bufferIndex++;

      if (_bufferIndex == BufferSize)
        Flush();
    }

    void Flush() noexcept
    {
      _writer.Write(static_cast<T>(_buffer.to_ullong()));
      _buffer.reset();
      _bufferIndex = 0;
    }

  private:
    static constexpr size_t BufferSize = 8 * sizeof(T);

    std::bitset<BufferSize> _buffer;
    size_t _bufferIndex;
    BinaryFileWriter<Endian::Type::System, TDestination> _writer;
  };
}