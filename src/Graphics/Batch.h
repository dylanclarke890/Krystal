#pragma once

#include "Types.h"
#include "Graphics/Enums.h"

namespace Krys::Graphics
{
  struct BatchKey
  {
    PrimitiveType PrimitiveType;

    bool operator==(const BatchKey &other) const noexcept
    {
      return PrimitiveType == other.PrimitiveType;
    }
  };

  struct BatchKeyHasher
  {
    size_t operator()(const BatchKey &k) const
    {
      size_t hash = 0;
      hash ^= std::hash<uint32>()(static_cast<uint32>(k.PrimitiveType)) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
      return hash;
    }
  };

  struct Batch
  {
    BatchKey Key;
  };
}