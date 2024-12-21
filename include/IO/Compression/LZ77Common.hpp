#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"

namespace Krys::IO
{
  struct LZ77Token
  {
    size_t offset; // Offset from the start of the window
    size_t length; // Match length
    char nextChar; // Next character after the match

    LZ77Token(size_t offset, size_t length, char nextChar)
        : offset(offset), length(length), nextChar(nextChar)
    {
    }
  };
}