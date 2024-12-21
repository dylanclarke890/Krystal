#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "IO/Compression/LZ77Common.hpp"

namespace Krys::IO
{
  class LZ77Decoder
  {
  public:
    NO_DISCARD string Decode(const List<LZ77Token> &tokens) noexcept
    {
      string decompressedText;
      for (const LZ77Token &token : tokens)
      {
        if (token.length > 0)
        {
          // Copy the matching string from the window
          size_t startPos = decompressedText.size() - token.offset;
          for (size_t i = 0; i < token.length; ++i)
          {
            decompressedText += decompressedText[startPos + i];
          }
        }
        // Append the next character
        decompressedText += token.nextChar;
      }
      return decompressedText;
    }
  };
}