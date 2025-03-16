#pragma once

#include "Base/Types.hpp"
#include "Utils/Bytes.hpp"
#include "IO/IO.hpp"
#include "Debug/Macros.hpp"

namespace Krys::IO
{
  class FileReader
  {
  public:
    explicit FileReader(const string &path) noexcept : _path(path)
    {
      KRYS_ASSERT(!path.empty(), "IO: Path is empty");
      KRYS_ASSERT(IO::PathExists(path), "IO: File '{0}' does not exist", path);
    }

    ~FileReader() noexcept
    {
      if (_stream.is_open())
      {
        _stream.close();
      }
    }

    FileReader(const FileReader &) = delete;
    FileReader &operator=(const FileReader &) = delete;

    FileReader(FileReader &&other) noexcept
        : _path(std::move(other._path)), _stream(std::move(other._stream))
    {
    }

    FileReader &operator=(FileReader &&other) noexcept
    {
      if (this != &other)
      {
        _path = std::move(other._path);
        _stream = std::move(other._stream);
      }
      return *this;
    }

    void Open(bool binary = false) noexcept 
    {
      KRYS_ASSERT(IO::PathExists(_path), "IO: File '{0}' does not exist", _path);

      int mode = std::ios::in;
      if (binary)
      {
        mode |= std::ios::binary;
      }

      _stream.open(_path.c_str(), mode);
      KRYS_ASSERT(_stream.is_open(), "IO: Unable to open '{0}'.", _path);
    }

    void Close() noexcept 
    {
      if (_stream.is_open())
      {
        _stream.close();
      }
    }

    bool IsEOS() const noexcept 
    {
      return _stream.eof();
    }

    uint8 NextByte() noexcept 
    {
      return static_cast<uint8>(_stream.get());
    }

    uint8 PeekNextByte() noexcept 
    {
      return static_cast<uint8>(_stream.peek());
    }

    uintmax_t GetSize() noexcept 
    {
      const auto pos = _stream.tellg();
      _stream.seekg(0, std::ios::end);
      const auto size = _stream.tellg();
      _stream.seekg(pos);
      return size;
    }

    string ReadLine() noexcept 
    {
      string line;
      std::getline(_stream, line);
      return line;
    }

    string ReadAll() noexcept 
    {
      return IO::ReadFileText(_path);
    }

    template <IsArithmeticT T, Endian::Type Endianess = Endian::Type::Little>
    T ReadBytes() noexcept 
    {
      List<byte> buffer(sizeof(T));
      _stream.read(reinterpret_cast<char *>(buffer.data()), sizeof(T));
      return Bytes::AsNumeric<T, Endianess>(buffer);
    }

    void ReadBytes(byte *data, uintmax_t size) noexcept 
    {
      _stream.read(reinterpret_cast<char *>(data), size);
    }

    void SkipWhitespace() noexcept 
    {
      while (!IsEOS() && std::isspace(_stream.peek()))
      {
        _stream.ignore();
      }
    }

  private:
    string _path;
    std::ifstream _stream;
  };
}