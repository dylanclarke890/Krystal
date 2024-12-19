#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "IO/BinaryFileReader.hpp"

namespace Krys::IO
{
  constexpr int MaxImageDimensions = 1 << 24;
  constexpr uchar DepthScaleTable[9] = {0, 0xff, 0x55, 0, 0x11, 0, 0, 0, 0x01};
  enum class ImageFileType
  {
    PNG
  };

  enum class PNGErrorType
  {
    None,
    InvalidSignature,
    IHDRNotFirst,
    IHDRMultipleFound,
    InvalidIHDR_ZeroWidthImage,
    InvalidIHDR_ZeroHeightImage,
    InvalidIHDR_InvalidChunkLength,
    InvalidIHDR_ImageWidthTooLarge,
    InvalidIHDR_ImageHeightTooLarge,
    InvalidIHDR_InvalidDepth,
    InvalidIHDR_InvalidColor,
    InvalidIHDR_InvalidCompressionMethod,
    InvalidIHDR_InvalidFilterMethod,
    InvalidIHDR_InvalidInterlaceMethod,
    InvalidPLTE_InvalidPaletteSize,
    InvalidPLTE_MultipleFound,
    InvalidtRNS_AppearedAfterIDAT,
    InvalidtRNS_AppearedBeforePLTE,
    InvalidtRNS_SizeGreaterThanPalette,
    InvalidtRNS_DataAlreadyContainsAlphaChannel,
    InvalidtRNS_InvalidLength,
    InvalidIDAT_PLTERequiredButMissing,
    InvalidIDAT_ChunkTooLarge,
    InvalidIEND_AppearedBeforeIDAT,
    UnexpectedCriticalChunk,
  };

  struct PNGDecodeResult
  {
    size_t Width, Height;
    uint8 Depth, Components;
    bool IsIphone, IsPaletted, Has_tRNS;
    uchar CompressionMethod, FilterMethod, InterlaceMethod;
    List<uchar> Palette;
    List<uchar> ImageData;

    PNGErrorType Error;

    NO_DISCARD bool Success() const noexcept
    {
      return Error == PNGErrorType::None;
    }
  };

  struct PNGChunk
  {
    uint32 Type;
    uint32 Length;
  };

  NO_DISCARD constexpr inline uint32 PNGChunkType(char a, char b, char c, char d) noexcept
  {
    return ((static_cast<unsigned>(a) << 24) + (static_cast<unsigned>(b) << 16)
            + (static_cast<unsigned>(c) << 8) + static_cast<unsigned>(d));
  }

  class PNGDecoder
  {
  public:
    void Parse() noexcept
    {
      _reader.SetFilepath("./textures/crate-specular.png");
      _reader.OpenStream();

      ValidateFileHeader();
      if (!_result.Success())
        return;

      constexpr auto IHDRChunkType = PNGChunkType('I', 'H', 'D', 'R');
      
      uchar tc[3] = {0};
      uint16 tc16[3] = {0};

      bool first = true;
      bool processedLastChunk = false;
      while (!processedLastChunk)
      {
        const PNGChunk chunk = GetPNGChunk();
        if (first && chunk.Type != IHDRChunkType)
        {
          _result.Error = PNGErrorType::IHDRNotFirst;
          return;
        }
        else if (!first && chunk.Type == IHDRChunkType)
        {
          _result.Error = PNGErrorType::IHDRMultipleFound;
          return;
        }
        else
        {
          first = false;
        }

        switch (chunk.Type)
        {
          // IHDR
          case IHDRChunkType:
          {
            if (chunk.Length != 13)
            {
              _result.Error = PNGErrorType::InvalidIHDR_InvalidChunkLength;
              return;
            }

            uint32 width = _reader.Read<uint32>();
            uint32 height = _reader.Read<uint32>();
            if (width == 0)
              _result.Error = PNGErrorType::InvalidIHDR_ZeroWidthImage;
            else if (height == 0)
              _result.Error = PNGErrorType::InvalidIHDR_ZeroHeightImage;
            else if (width > MaxImageDimensions)
              _result.Error = PNGErrorType::InvalidIHDR_ImageWidthTooLarge;
            else if (height > MaxImageDimensions)
              _result.Error = PNGErrorType::InvalidIHDR_ImageHeightTooLarge;
            if (!_result.Success())
              return;

            _result.Width = width;
            _result.Height = height;

            uchar depth = _reader.Read<uchar>();
            if (depth != 1 && depth != 2 && depth != 4 && depth != 8 && depth != 16)
            {
              _result.Error = PNGErrorType::InvalidIHDR_InvalidDepth;
              return;
            }
            _result.Depth = depth;

            uchar color = _reader.Read<uchar>();
            if (color > 6)
              _result.Error = PNGErrorType::InvalidIHDR_InvalidColor;
            else if (color == 3 && depth == 16)
              _result.Error = PNGErrorType::InvalidIHDR_InvalidDepth;
            if (color == 3)
            {
              _result.IsPaletted = true;
              _result.Components = 3;
            }
            else if (color & 1)
              _result.Error = PNGErrorType::InvalidIHDR_InvalidColor;

            if (!_result.Success())
              return;

            _result.CompressionMethod = _reader.Read<uchar>();
            if (_result.CompressionMethod)
            {
              // Only '0' is currently supported in the standard.
              _result.Error = PNGErrorType::InvalidIHDR_InvalidCompressionMethod;
              return;
            }

            _result.FilterMethod = _reader.Read<uchar>();
            if (_result.FilterMethod)
            {
              // Only '0' is currently supported in the standard.
              _result.Error = PNGErrorType::InvalidIHDR_InvalidFilterMethod;
              return;
            }

            _result.InterlaceMethod = _reader.Read<uchar>();
            if (_result.InterlaceMethod > 1)
            {
              _result.Error = PNGErrorType::InvalidIHDR_InvalidInterlaceMethod;
              return;
            }

            if (!_result.IsPaletted)
              _result.Components = (color & 2 ? 3 : 1) + (color & 4 ? 1 : 0);
            break;
          }

          // PLTE
          case PNGChunkType('P', 'L', 'T', 'E'):
          {
            if (_result.Palette.size() > 0)
            {
              _result.Error = PNGErrorType::InvalidPLTE_MultipleFound;
              return;
            }

            uint32 paletteLength = chunk.Length / 3;
            if (paletteLength > 256 || paletteLength * 3 != chunk.Length)
            {
              _result.Error = PNGErrorType::InvalidPLTE_InvalidPaletteSize;
              return;
            }
            _result.Palette.reserve(paletteLength * 4);

            for (uint32 i = 0; i < paletteLength; i++)
            {
              _result.Palette.push_back(_reader.Read<uchar>());
              _result.Palette.push_back(_reader.Read<uchar>());
              _result.Palette.push_back(_reader.Read<uchar>());
              _result.Palette.push_back(255);
            }
            break;
          }

          // tRNS
          case PNGChunkType('t', 'R', 'N', 'S'):
          {
            if (_result.ImageData.size() > 0)
            {
              _result.Error = PNGErrorType::InvalidtRNS_AppearedAfterIDAT;
              return;
            }

            if (_result.IsPaletted)
            {
              if (_result.Palette.size() == 0)
              {
                _result.Error = PNGErrorType::InvalidtRNS_AppearedBeforePLTE;
                return;
              }

              if (chunk.Length > _result.Palette.size())
              {

                _result.Error = PNGErrorType::InvalidtRNS_SizeGreaterThanPalette;
                return;
              }

              _result.Components = 4;
              for (uint32 i = 0; i < chunk.Length; ++i)
                _result.Palette[i * 4 + 3] = _reader.Read<uchar>();
            }
            else
            {
              if (!(_result.Components & 1))
              {
                _result.Error = PNGErrorType::InvalidtRNS_DataAlreadyContainsAlphaChannel;
                return;
              }

              if (chunk.Length != uint32(_result.Components * 2))
              {
                _result.Error = PNGErrorType::InvalidtRNS_InvalidLength;
                return;
              }

              _result.Has_tRNS = true;

              if (_result.Depth == 16)
              {
                for (int i = 0; i < _result.Components; i++)
                  tc16[i] = _reader.Read<uint16>(); // copy the values as-is
              }
              else
              {
                for (int i = 0; i < _result.Components; i++)
                  tc[i] = _reader.Read<uint16>()
                          & 255 * DepthScaleTable[_result.Depth]; // non 8-bit images will be larger
              }
            }
            break;
          }

          // IDAT
          case PNGChunkType('I', 'D', 'A', 'T'):
          {
            if (_result.IsPaletted && _result.Palette.size() == 0)
            {
              _result.Error = PNGErrorType::InvalidIDAT_PLTERequiredButMissing;
              return;
            }

            if (chunk.Length > (1u << 30))
            {
              _result.Error = PNGErrorType::InvalidIDAT_ChunkTooLarge;
              return;
            }

            size_t size = _result.ImageData.size();
            size_t capacity = _result.ImageData.capacity();
            if (size + chunk.Length > capacity)
            {
              if (capacity == 0)
                capacity = chunk.Length > 4'096 ? chunk.Length : 4'096;

              while (size + chunk.Length > capacity)
                capacity *= 2;

              _result.ImageData.reserve(capacity);
            }
            _result.ImageData.append_range(_reader.Read<uchar>(chunk.Length));
            break;
          }

          // CgBI
          case PNGChunkType('C', 'g', 'B', 'I'):
          {
            _result.IsIphone = true;
            _reader.SkipBytes(chunk.Length);
            break;
          }

          // IEND
          case PNGChunkType('I', 'E', 'N', 'D'):
          {
            if (_result.ImageData.size() == 0)
            {
              _result.Error = PNGErrorType::InvalidIEND_AppearedBeforeIDAT;
              return;
            }
            processedLastChunk = true;
            break;
          }

          default:
          {
            if ((chunk.Type & (1 << 29)) == 0)
            {
              _result.Error = PNGErrorType::UnexpectedCriticalChunk;
              return;
            }

            // Non-critical chunk; we can safely proceed.
            _reader.SkipBytes(chunk.Length);
            break;
          }
        }

        // Skip CRC (cyclic redundancy check) byte at the end of each chunk.
        _reader.SkipBytes(4);
      }
    }

  private:
      NO_DISCARD PNGChunk GetPNGChunk() noexcept
    {
      PNGChunk chunk;
      chunk.Length = _reader.Read<uint32>();
      chunk.Type = _reader.Read<uint32>();
      return chunk;
    }

    NO_DISCARD void ValidateFileHeader() noexcept
    {
      static const uchar signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
      for (int i = 0; i < 8; i++)
        if (_reader.Read<uchar>() != signature[i])
        {
          _result.Error = PNGErrorType::InvalidSignature;
          break;
        }
    }
  private:
    PNGDecodeResult _result;
    BinaryFileReader<Endian::Type::Big, Endian::Type::System> _reader;
  };
}