#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "IO/IO.hpp"
#include "IO/Readers/BitReader.hpp"
#include "IO/Readers/FileReader.hpp"

namespace Krys::IO
{
  enum class PNMType
  {
    PBMA,
    PBMB,
    PGMA,
    PGMB,
    PPMA,
    PPMB,
  };

  struct PNMImage
  {
    uint32 Width;
    uint32 Height;
    uint8 Channels;
    PNMType Type;
    uint16 MaxValue {255};
    List<byte> Data;
  };

  class PNM
  {
  public:
    PNM() = default;
    ~PNM() = default;

    /// @brief Loads a PNM image from the specified path.
    /// @param path The path to the PNM image file.
    /// @return A unique pointer to the loaded PNM image, or nullptr if the loading failed.
    /// @details The function supports the following PNM formats:
    ///          - PBMA: Portable Bitmap (ASCII)
    ///          - PBMB: Portable Bitmap (Binary)
    ///          - PGMA: Portable Graymap (ASCII)
    ///          - PGMB: Portable Graymap (Binary)
    ///          - PPMA: Portable Pixmap (ASCII)
    ///          - PPMB: Portable Pixmap (Binary)
    NO_DISCARD Unique<PNMImage> Load(const string &path) noexcept
    {
      FileReader reader(path);
      reader.Open(true);

      const auto type = ReadMagicNumber(reader);
      if (!type)
      {
        return nullptr;
      }

      switch (*type)
      {
        case PNMType::PBMA: return LoadPBMA(reader);
        case PNMType::PBMB: return LoadPBMB(reader);
        case PNMType::PGMA: return LoadPGMA(reader);
        case PNMType::PGMB: return LoadPGMB(reader);
        case PNMType::PPMA: return LoadPPMA(reader);
        case PNMType::PPMB: return LoadPPMB(reader);
        default:            return nullptr;
      }

      return nullptr;
    }

  private:
#pragma region Header

    Expected<PNMType> ReadMagicNumber(FileReader &reader) noexcept
    {
      const auto firstChar = reader.NextByte();
      if (firstChar != 'P')
      {
        return Unexpected("Invalid PNM header");
      }

      const auto secondChar = reader.NextByte();
      SkipWhitespace(reader);
      switch (secondChar)
      {
        case '1': return PNMType::PBMA;
        case '2': return PNMType::PGMA;
        case '3': return PNMType::PPMA;
        case '4': return PNMType::PBMB;
        case '5': return PNMType::PGMB;
        case '6': return PNMType::PPMB;
        default:  return Unexpected("Invalid PNM header");
      }
    }

    bool ReadSize(FileReader &reader, PNMImage &result) noexcept
    {
      result.Width = ReadASCIINumber(reader);
      result.Height = ReadASCIINumber(reader);
      SkipWhitespace(reader);

      return true;
    }

    NO_DISCARD bool ReadMaxValue(FileReader &reader, PNMImage &result) noexcept
    {
      auto maxValue = ReadASCIINumber(reader);
      if (maxValue >= static_cast<ulong>(std::numeric_limits<uint16>::max() + 1))
      {
        return false;
      }

      result.MaxValue = static_cast<uint16>(maxValue);
      SkipWhitespace(reader);
      return true;
    }

#pragma endregion Header

#pragma region Loaders

    /// @brief Portable Bitmap (PBM) - ASCII
    /// @details 1-bit monochrome image format. Each pixel is represented by an ASCII character
    ///          (0 or 1).
    NO_DISCARD Unique<PNMImage> LoadPBMA(FileReader &reader) noexcept
    {
      auto result = CreateUnique<PNMImage>();
      result->Channels = 1;
      result->Type = PNMType::PBMA;

      if (!ReadSize(reader, *result))
      {
        return nullptr;
      }

      auto size = result->Width * result->Height;
      result->Data.reserve(size);

      for (uint32 i = 0; i < size; i++)
      {
        SkipWhitespace(reader);
        auto value = ReadASCIINumber(reader);
        if (value > 255)
        {
          return nullptr;
        }

        // In PBM, 1 is black and 0 is white
        result->Data.push_back(value ? byte {0} : byte {255});
      }

      return result;
    }

    /// @brief Portable Bitmap (PBM) - Binary
    /// @details 1-bit monochrome image format. Each pixel is represented by a single bit.
    /// @details The data is packed into bytes, with each bit representing a pixel.
    NO_DISCARD Unique<PNMImage> LoadPBMB(FileReader &reader) noexcept
    {
      auto result = CreateUnique<PNMImage>();
      result->Channels = 1;
      result->Type = PNMType::PBMB;

      if (!ReadSize(reader, *result))
      {
        return nullptr;
      }

      auto size = result->Width * result->Height;
      result->Data.reserve(size);
      size = (size + 7) / 8;

      List<byte> data(size);
      reader.ReadBytes(data.data(), size);

      BitReader<Endian::Type::Big, Endian::Type::System> bitReader(&data);
      for (uint32 i = 0; i < result->Width * result->Height; i++)
      {
        // In PBM, 1 is black and 0 is white
        result->Data.push_back(bitReader.ReadBit() ? byte {0} : byte {255});
      }

      return result;
    }

    /// @brief Portable Graymap (PGM) - ASCII
    /// @details 8-bit grayscale image format. Each pixel is represented by an ASCII number. The value is in
    /// the range [0, maxValue].
    NO_DISCARD Unique<PNMImage> LoadPGMA(FileReader &reader) noexcept
    {
      auto result = CreateUnique<PNMImage>();
      result->Channels = 1;
      result->Type = PNMType::PGMA;

      if (!ReadSize(reader, *result))
      {
        return nullptr;
      }

      if (!ReadMaxValue(reader, *result))
      {
        return nullptr;
      }

      auto size = result->Width * result->Height;
      result->Data.reserve(size);

      for (uint32 i = 0; i < size; i++)
      {
        SkipWhitespace(reader);
        auto value = ReadASCIINumber(reader);
        if (value > result->MaxValue)
        {
          return nullptr;
        }
        result->Data.push_back(MapToByte(static_cast<uint16>(value), result->MaxValue));
      }

      return result;
    }

    /// @brief Portable Graymap (PGM) - Binary
    /// @details 8-bit grayscale image format. Each pixel is represented by a single byte. The value is in
    /// the range [0, maxValue]. The data is stored in big-endian format.
    NO_DISCARD Unique<PNMImage> LoadPGMB(FileReader &reader) noexcept
    {
      auto result = CreateUnique<PNMImage>();
      result->Channels = 1;
      result->Type = PNMType::PGMB;

      if (!ReadSize(reader, *result))
      {
        return nullptr;
      }

      if (!ReadMaxValue(reader, *result))
      {
        return nullptr;
      }

      auto size = result->Width * result->Height;
      result->Data.reserve(size);

      for (uint32 i = 0; i < size; i++)
      {
        if (result->MaxValue > 255)
        {
          auto value = reader.ReadBytes<uint16, Endian::Type::Big>();
          result->Data.push_back(MapToByte(value, result->MaxValue));
        }
        else
        {
          auto value = reader.NextByte();
          result->Data.push_back(MapToByte(value, result->MaxValue));
        }
      }

      return result;
    }

    /// @brief Portable Pixmap (PPM) - ASCII
    /// @details 24-bit RGB image format. Each pixel is represented by three ASCII numbers (R, G, B).
    ///          The values are in the range [0, maxValue].
    NO_DISCARD Unique<PNMImage> LoadPPMA(FileReader &reader) noexcept
    {
      auto result = CreateUnique<PNMImage>();
      result->Channels = 3;
      result->Type = PNMType::PPMA;

      if (!ReadSize(reader, *result))
      {
        return nullptr;
      }

      if (!ReadMaxValue(reader, *result))
      {
        return nullptr;
      }

      auto size = result->Width * result->Height;
      result->Data.reserve(size * 3);

      for (uint32 i = 0; i < size; i++)
      {
        SkipWhitespace(reader);
        auto value = ReadASCIINumber(reader);
        if (value > result->MaxValue)
        {
          return nullptr;
        }
        result->Data.push_back(MapToByte(static_cast<uint16>(value), result->MaxValue));
      }

      return result;
    }

    /// @brief Portable Pixmap (PPM) - Binary
    /// @details 24-bit RGB image format. Each pixel is represented by three bytes (R, G, B).
    ///          The values are in the range [0, maxValue]. The data is stored in big-endian format.
    NO_DISCARD Unique<PNMImage> LoadPPMB(FileReader &reader) noexcept
    {
      auto result = CreateUnique<PNMImage>();
      result->Channels = 3;
      result->Type = PNMType::PPMB;

      if (!ReadSize(reader, *result))
      {
        return nullptr;
      }

      if (!ReadMaxValue(reader, *result))
      {
        return nullptr;
      }

      auto size = result->Width * result->Height;
      result->Data.reserve(size * 3);

      for (uint32 i = 0; i < size; i++)
      {
        if (result->MaxValue > 255)
        {
          auto value = reader.ReadBytes<uint16, Endian::Type::Big>();
          result->Data.push_back(MapToByte(value, result->MaxValue));
        }
        else
        {
          auto value = reader.NextByte();
          result->Data.push_back(MapToByte(value, result->MaxValue));
        }
      }

      return result;
    }

#pragma endregion Loaders

#pragma region Utils

    NO_DISCARD ulong ReadASCIINumber(FileReader &reader) noexcept
    {
      SkipWhitespace(reader);
      string number;
      while (!reader.IsEOS())
      {
        const auto c = reader.PeekNextByte();
        if (IsWhiteSpace(c))
        {
          break;
        }
        else if (IsComment(c))
        {
          reader.ReadLine();
          continue;
        }
        number += reader.NextByte();
      }

      return std::stoul(number);
    }

    NO_DISCARD bool IsWhiteSpace(char c) const noexcept
    {
      return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    NO_DISCARD bool IsComment(char c) const noexcept
    {
      return c == '#';
    }

    void SkipWhitespace(FileReader &reader) noexcept
    {
      while (!reader.IsEOS())
      {
        const auto c = reader.PeekNextByte();
        if (IsWhiteSpace(c))
        {
          reader.NextByte();
        }
        else if (IsComment(c))
        {
          reader.ReadLine();
        }
        else
        {
          break;
        }
      }
    }

    NO_DISCARD byte MapToByte(uint16 value, uint16 maxValue) const noexcept
    {
      if (maxValue == 0)
      {
        return byte {0};
      }

      return static_cast<byte>((value * 255 + maxValue / 2) / maxValue);
    }

#pragma endregion Utils
  };
}