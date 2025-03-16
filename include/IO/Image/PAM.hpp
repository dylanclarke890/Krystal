#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"
#include "IO/IO.hpp"
#include "IO/Readers/FileReader.hpp"
#include "Utils/Bytes.hpp"

namespace Krys::IO
{
  enum class PAMType
  {
    BlackAndWhite,
    BlackAndWhiteAlpha,
    Grayscale,
    GrayscaleAlpha,
    RGB,
    RGBAlpha,
  };

  struct PAMImage
  {
    uint32 Width;
    uint32 Height;
    uint8 Channels;
    uint16 MaxValue {255};
    List<byte> Data;
    PAMType Type;
  };

  class PAM
  {
  public:
    PAM() = default;
    ~PAM() = default;

    /// @brief Loads a PAM image from the specified path.
    /// @param path The path to the PAM image file.
    /// @return A unique pointer to the loaded PAM image, or nullptr if the loading failed.
    NO_DISCARD Unique<PAMImage> Load(const string &path) noexcept
    {
      FileReader reader(path);
      reader.Open(true);

      auto result = CreateUnique<PAMImage>();
      auto magicNumber = reader.ReadLine();
      if (!magicNumber.starts_with("P7"))
      {
        return nullptr;
      }

      while (!reader.IsEOS())
      {
        auto line = reader.ReadLine();
        Logger::Debug("PAM Header: {0}", line);

        if (line.empty() || line.starts_with('#'))
        {
          continue;
        }

        if (line.starts_with("ENDHDR"))
        {
          break;
        }

        ReadHeaderPart(*result, line);
      }

      if (result->Width < 1 || result->Height < 1 || result->Channels < 1)
      {
        Logger::Error("Invalid PAM image dimensions: {0}x{1}x{2}", result->Width, result->Height,
                      result->Channels);
        return nullptr;
      }

      if (result->MaxValue < 1)
      {
        Logger::Error("Invalid PAM image max value: {0}", result->MaxValue);
        return nullptr;
      }

      if (result->Type == PAMType::BlackAndWhite)
      {
        result->Channels = 1;
        ReadBlackAndWhiteData(reader, *result);
      }
      else if (result->Type == PAMType::BlackAndWhiteAlpha)
      {
        result->Channels = 2;
        ReadBlackAndWhiteAlphaData(reader, *result);
      }
      else if (result->Type == PAMType::Grayscale)
      {
        result->Channels = 1;
        ReadGrayscaleData(reader, *result);
      }
      else if (result->Type == PAMType::GrayscaleAlpha)
      {
        result->Channels = 2;
        ReadGrayscaleAlphaData(reader, *result);
      }
      else if (result->Type == PAMType::RGB)
      {
        result->Channels = 3;
        ReadRGBData(reader, *result);
      }
      else if (result->Type == PAMType::RGBAlpha)
      {
        result->Channels = 4;
        ReadRGBAlphaData(reader, *result);
      }

      return result;
    }

  private:
    void ReadHeaderPart(PAMImage &image, const string &line) noexcept
    {
      if (line.starts_with("WIDTH"))
      {
        image.Width = std::stoul(line.substr(6));
      }
      else if (line.starts_with("HEIGHT"))
      {
        image.Height = std::stoul(line.substr(7));
      }
      else if (line.starts_with("DEPTH"))
      {
        image.Channels = static_cast<uint8>(std::stoul(line.substr(6)));
      }
      else if (line.starts_with("MAXVAL"))
      {
        image.MaxValue = static_cast<uint16>(std::stoul(line.substr(7)));
      }
      else if (line.starts_with("TUPLETYPE"))
      {
        auto type = line.substr(10);
        std::transform(type.begin(), type.end(), type.begin(),
                       [](unsigned char c) { return static_cast<uchar>(std::toupper(c)); });

        if (type.starts_with("BLACKANDWHITE"))
        {
          image.Type = PAMType::BlackAndWhite;
        }
        else if (type.starts_with("BLACKANDWHITE_ALPHA"))
        {
          image.Type = PAMType::BlackAndWhiteAlpha;
        }
        else if (type.starts_with("GRAYSCALE"))
        {
          image.Type = PAMType::Grayscale;
        }
        else if (type.starts_with("GRAYSCALE_ALPHA"))
        {
          image.Type = PAMType::GrayscaleAlpha;
        }
        else if (type.starts_with("RGB"))
        {
          image.Type = PAMType::RGB;
        }
        else if (type.starts_with("RGB_ALPHA"))
        {
          image.Type = PAMType::RGBAlpha;
        }
        else
        {
          Logger::Error("Unsupported PAM type: {0}", type);
        }
      }
    }

#pragma region ReadData

    void ReadBlackAndWhiteData(FileReader &reader, PAMImage &image) noexcept
    {
      auto size = image.Width * image.Height;
      image.Data.reserve(size);

      for (uint32 i = 0; i < size; i++)
      {
        auto value = reader.NextByte();
        image.Data.push_back(value ? byte {255} : byte {0});
      }
    }

    void ReadBlackAndWhiteAlphaData(FileReader &reader, PAMImage &image) noexcept
    {
      auto size = image.Width * image.Height;
      image.Data.reserve(size * 2);

      for (uint32 i = 0; i < size; i++)
      {
        auto colour = reader.NextByte();
        image.Data.push_back(colour ? byte {255} : byte {0});

        // The alpha channel is always 1 byte that is either 0 or 1
        auto alpha = reader.NextByte();
        image.Data.push_back(alpha ? byte {255} : byte {0});
      }
    }

    void ReadGrayscaleData(FileReader &reader, PAMImage &image) noexcept
    {
      auto size = image.Width * image.Height;
      image.Data.reserve(size);

      for (uint32 i = 0; i < size; i++)
      {
        if (image.MaxValue > 255)
        {
          auto value = reader.ReadBytes<uint16, Endian::Type::Big>();
          image.Data.push_back(MapToByte(value, image.MaxValue));
        }
        else
        {
          auto value = reader.NextByte();
          image.Data.push_back(MapToByte(value, image.MaxValue));
        }
      }
    }

    void ReadGrayscaleAlphaData(FileReader &reader, PAMImage &image) noexcept
    {
      auto size = image.Width * image.Height;
      image.Data.reserve(size * 2);

      for (uint32 i = 0; i < size; i++)
      {
        if (image.MaxValue > 255)
        {
          auto colour = reader.ReadBytes<uint16, Endian::Type::Big>();
          auto alpha = reader.ReadBytes<uint16, Endian::Type::Big>();
          image.Data.push_back(MapToByte(colour, image.MaxValue));
          image.Data.push_back(MapToByte(alpha, image.MaxValue));
        }
        else
        {
          auto colour = reader.NextByte();
          auto alpha = reader.NextByte();
          image.Data.push_back(MapToByte(colour, image.MaxValue));
          image.Data.push_back(MapToByte(alpha, image.MaxValue));
        }
      }
    }

    void ReadRGBData(FileReader &reader, PAMImage &image) noexcept
    {
      auto size = image.Width * image.Height;
      image.Data.reserve(size * 3);

      for (uint32 i = 0; i < size; i++)
      {
        if (image.MaxValue > 255)
        {
          auto r = reader.ReadBytes<uint16, Endian::Type::Big>();
          auto g = reader.ReadBytes<uint16, Endian::Type::Big>();
          auto b = reader.ReadBytes<uint16, Endian::Type::Big>();
          image.Data.push_back(MapToByte(r, image.MaxValue));
          image.Data.push_back(MapToByte(g, image.MaxValue));
          image.Data.push_back(MapToByte(b, image.MaxValue));
        }
        else
        {
          auto r = reader.NextByte();
          auto g = reader.NextByte();
          auto b = reader.NextByte();
          image.Data.push_back(MapToByte(r, image.MaxValue));
          image.Data.push_back(MapToByte(g, image.MaxValue));
          image.Data.push_back(MapToByte(b, image.MaxValue));
        }
      }
    }

    void ReadRGBAlphaData(FileReader &reader, PAMImage &image) noexcept
    {
      auto size = image.Width * image.Height;
      image.Data.reserve(size * 4);

      for (uint32 i = 0; i < size; i++)
      {
        if (image.MaxValue > 255)
        {
          auto r = reader.ReadBytes<uint16, Endian::Type::Big>();
          auto g = reader.ReadBytes<uint16, Endian::Type::Big>();
          auto b = reader.ReadBytes<uint16, Endian::Type::Big>();
          auto a = reader.ReadBytes<uint16, Endian::Type::Big>();
          image.Data.push_back(MapToByte(r, image.MaxValue));
          image.Data.push_back(MapToByte(g, image.MaxValue));
          image.Data.push_back(MapToByte(b, image.MaxValue));
          image.Data.push_back(MapToByte(a, image.MaxValue));
        }
        else
        {
          auto r = reader.NextByte();
          auto g = reader.NextByte();
          auto b = reader.NextByte();
          auto a = reader.NextByte();
          image.Data.push_back(MapToByte(r, image.MaxValue));
          image.Data.push_back(MapToByte(g, image.MaxValue));
          image.Data.push_back(MapToByte(b, image.MaxValue));
          image.Data.push_back(MapToByte(a, image.MaxValue));
        }
      }
    }

#pragma endregion ReadData

    NO_DISCARD byte MapToByte(uint16 value, uint16 maxValue) const noexcept
    {
      if (maxValue == 0)
      {
        return byte {0};
      }

      return static_cast<byte>((value * 255 + maxValue / 2) / maxValue);
    }
  };
}