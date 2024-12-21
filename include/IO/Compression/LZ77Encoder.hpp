#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "IO/Compression/LZ77Common.hpp"

namespace Krys::IO
{
  class LZ77Encoder
  {
  public:
    NO_DISCARD List<LZ77Token> Encode(const string &input) noexcept
    {
      List<LZ77Token> tokens;

      size_t i = 0;
      while (i < input.size())
      {
        size_t maxMatchLength = 0;
        size_t maxMatchDistance = 0;
        size_t startWindow = (i < 1'024) ? 0 : i - 1'024;

        for (size_t j = startWindow; j < i; j++)
        {
          size_t matchLength = 0;
          while (input[i + matchLength] == input[j + matchLength])
          {
            matchLength++;
            if (i + matchLength >= input.size() || j + matchLength >= i)
              break;
          }

          if (matchLength > maxMatchLength)
          {
            maxMatchLength = matchLength;
            maxMatchDistance = i - j;
          }
        }

        if (maxMatchLength == 0)
        {
          maxMatchDistance = 0;
          maxMatchLength = 0;
        }

        tokens.emplace_back(maxMatchDistance, maxMatchLength, input[i + maxMatchLength]);
        i += maxMatchLength + 1;
      }

      return tokens;
    }
  };
}