#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "IO/Readers/BitReader.hpp"
#include "IO/Readers/FileReader.hpp"

namespace Krys::IO
{
  struct ColorPaletteEntry
  {
    uint8 Blue;
    uint8 Green;
    uint8 Red;
    uint8 Alpha;
  };

  struct BMPImage
  {
    uint32 Width;
    uint32 Height;
    uint8 Channels;
    List<byte> Data;
    List<ColorPaletteEntry> Palette;
  };

  class BMP
  {
    struct FileHeader
    {
      uint16 Type;
      uint32 FileSize;
      uint16 Reserved1;
      uint16 Reserved2;
      uint32 Offset;
    };

    enum class HeaderType
    {
      BITMAPCOREHEADER,
      BITMAPINFOHEADER,
      BITMAPV4HEADER,
      BITMAPV5HEADER
    };

    struct InfoHeader
    {
      uint32 Size;
      int32 Width;
      int32 Height;
      uint16 Planes;
      uint16 BitsPerPixel;
      uint32 Compression;
      uint32 ImageSize;
      int32 XPixelsPerMeter;
      int32 YPixelsPerMeter;
      uint32 ColorsUsed;
      uint32 ImportantColors;
    };

    struct Bitmasks
    {
      uint32 RedMask {0u};
      uint32 GreenMask {0u};
      uint32 BlueMask {0u};
      uint32 AlphaMask {0u};
    };

    enum class CompressionType
    {
      BI_RGB = 0,
      BI_RLE8 = 1,
      BI_RLE4 = 2,
      BI_BITFIELDS = 3,
      BI_JPEG = 4,
      BI_PNG = 5,
      BI_ALPHABITFIELDS = 6,
      BI_CMYK = 11,
      BI_CMYKRLE8 = 12,
      BI_CMYKRLE4 = 13
    };

  public:
    BMP() = default;
    ~BMP() = default;

    /// @brief Loads a BMP image from the specified path.
    /// @param path The path to the BMP image file.
    NO_DISCARD Unique<BMPImage> Load(const string &path) noexcept
    {
      FileReader reader(path);
      reader.Open();

      auto header = ReadFileHeader(reader);
      if (!header)
      {
        return nullptr;
      }

      auto dibHeaderType = GetDIBHeaderType(reader);
      if (!dibHeaderType || dibHeaderType.value() != HeaderType::BITMAPINFOHEADER)
      {
        return nullptr;
      }

      auto dibHeader = ReadInfoHeader(reader);
      if (!dibHeader)
      {
        return nullptr;
      }

      auto result = CreateUnique<BMPImage>();

      result->Width = static_cast<uint32>(dibHeader->Width);
      result->Height = static_cast<uint32>(abs(dibHeader->Height));

      if (dibHeader->BitsPerPixel <= 8)
      {
        auto colorPaletteSize = dibHeader->ColorsUsed;
        if (colorPaletteSize == 0)
        {
          colorPaletteSize = GetColorPaletteSize(dibHeader->BitsPerPixel);
        }

        if (colorPaletteSize == 0)
        {
          return nullptr; // No color palette available
        }
        else
        {
          ReadColorPalette(reader, result->Palette, colorPaletteSize);
        }
      }

      Bitmasks bitmasks;
      if (dibHeader->Compression == 0)
      {
        if (dibHeader->BitsPerPixel == 16)
        {
          bitmasks.RedMask = 31u << 10;
          bitmasks.GreenMask = 31u << 5;
          bitmasks.BlueMask = 31u << 0;
        }
        else if (dibHeader->BitsPerPixel == 32)
        {
          bitmasks.RedMask = 0xffu << 16;
          bitmasks.GreenMask = 0xffu << 8;
          bitmasks.BlueMask = 0xffu << 0;
          bitmasks.AlphaMask = 0xffu << 24;
        }
        else
        {
          bitmasks.RedMask = bitmasks.GreenMask = bitmasks.BlueMask = bitmasks.AlphaMask = 0;
        }
      }
      else if (dibHeader->Compression == 3)
      {
        bitmasks.RedMask = reader.ReadBytes<uint32>();
        bitmasks.GreenMask = reader.ReadBytes<uint32>();
        bitmasks.BlueMask = reader.ReadBytes<uint32>();
      }
      else
      {
        bitmasks.RedMask = bitmasks.GreenMask = bitmasks.BlueMask = bitmasks.AlphaMask = 0;
      }

      result->Channels = bitmasks.AlphaMask ? 4 : 3;
      reader.Seek(header->Offset);

      auto rowSize = ((result->Width * dibHeader->BitsPerPixel + 31) / 32) * 4;
      Logger::Debug("Row size: {0}", rowSize);
      result->Data.reserve(result->Width * result->Height * result->Channels);

      auto bitsPerPixel = dibHeader->BitsPerPixel;
      for (uint32 y = 0; y < result->Height; y++)
      {
        List<byte> row(rowSize);
        reader.ReadBytes(row.data(), rowSize);
        BitReader<Endian::Type::Little> bitReader(&row);
        for (uint32 x = 0; x < result->Width; x++)
        {
          if (bitsPerPixel == 1 || bitsPerPixel == 2 || bitsPerPixel == 4 || bitsPerPixel == 8)
          {
            uint8 index = static_cast<uint8>(bitReader.ReadBits(bitsPerPixel));
            auto palette = result->Palette[index];
            result->Data.push_back(byte {palette.Red});
            result->Data.push_back(byte {palette.Green});
            result->Data.push_back(byte {palette.Blue});
          }
        }
      }

      return result;
    }

  private:
    Expected<FileHeader> ReadFileHeader(FileReader &reader) noexcept
    {
      FileHeader header;
      auto b = reader.ReadBytes<uint8>();
      auto m = reader.ReadBytes<uint8>();
      header.Type = b | (m << 8);
      if (b != 'B' || m != 'M')
      {
        return Unexpected("Invalid BMP file format");
      }

      header.FileSize = reader.ReadBytes<uint32>();
      header.Reserved1 = reader.ReadBytes<uint16>();
      header.Reserved2 = reader.ReadBytes<uint16>();
      header.Offset = reader.ReadBytes<uint32>();

      return header;
    }

    Expected<HeaderType> GetDIBHeaderType(FileReader &reader) noexcept
    {
      HeaderType type;
      auto size = reader.ReadBytes<uint32>();
      switch (size)
      {
        case 12:  type = HeaderType::BITMAPCOREHEADER; break;
        case 40:  type = HeaderType::BITMAPINFOHEADER; break;
        case 108: type = HeaderType::BITMAPV4HEADER; break;
        case 124: type = HeaderType::BITMAPV5HEADER; break;
        default:  return Unexpected("Unknown BMP DIB header size");
      }

      // Move back to the start of the header so that we can read it again when we read the entire header
      reader.Skip(-4);
      return type;
    }

    Expected<InfoHeader> ReadInfoHeader(FileReader &reader) noexcept
    {
      InfoHeader header;
      header.Size = reader.ReadBytes<uint32>();
      if (header.Size != 40)
      {
        return Unexpected("Invalid BMP DIB header size");
      }

      header.Width = reader.ReadBytes<int32>();
      header.Height = reader.ReadBytes<int32>();
      header.Planes = reader.ReadBytes<uint16>();
      header.BitsPerPixel = reader.ReadBytes<uint16>();
      header.Compression = reader.ReadBytes<uint32>();
      header.ImageSize = reader.ReadBytes<uint32>();
      header.XPixelsPerMeter = reader.ReadBytes<int32>();
      header.YPixelsPerMeter = reader.ReadBytes<int32>();
      header.ColorsUsed = reader.ReadBytes<uint32>();
      header.ImportantColors = reader.ReadBytes<uint32>();

      return header;
    }

    void ReadColorPalette(FileReader &reader, List<ColorPaletteEntry> &palette, uint32 size,
                          bool hasAlpha = true) noexcept
    {
      palette.resize(size);
      for (uint32 i = 0; i < size; ++i)
      {
        palette[i].Blue = reader.ReadBytes<uint8>();
        palette[i].Green = reader.ReadBytes<uint8>();
        palette[i].Red = reader.ReadBytes<uint8>();
        if (hasAlpha)
        {
          palette[i].Alpha = reader.ReadBytes<uint8>();
        }
        else
        {
          palette[i].Alpha = 0xFF;
        }
      }
    }

    uint32 GetColorPaletteSize(uint16 bps) noexcept
    {
      switch (bps)
      {
        case 1:  return 2;
        case 4:  return 16;
        case 8:  return 256;
        default: return 0;
      }
    }
  };
}