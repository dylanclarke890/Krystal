#pragma once

#include <random>

#include "Core.h"
#include "Maths/Vector.h"

namespace Krys::Maths
{
  class Random
  {
  private:
    inline static std::mt19937 RandomEngine;
    inline static std::uniform_int_distribution<std::mt19937::result_type> Distribution;

    inline static uint32 Rand()
    {
      return Distribution(RandomEngine);
    }

  public:
    static void Init()
    {
      RandomEngine.seed(std::random_device()());
    }

    static uint32 UInt()
    {
      return Rand();
    }

    static uint32 UInt(uint32 max)
    {
      return Rand() % (max + 1);
    }

    static uint32 UInt(uint32 min, uint32 max)
    {
      return min + (Rand() % (max - min + 1));
    }

    static int32 Int()
    {
      return static_cast<int>(Rand());
    }

    static int32 Int(uint32 max)
    {
      return static_cast<int>(UInt(max));
    }

    static int32 Int(uint32 min, uint32 max)
    {
      return min + (Rand() % (max - min + 1));
    }

    static float Float()
    {
      return static_cast<float>(Rand()) / static_cast<float>(std::numeric_limits<uint32>::max());
    }

    static float Float(float max)
    {
      return Float(0, max);
    }

    static float Float(float min, float max)
    {
      return Float() * (max - min) + min;
    }

    static Vec2 Vector2()
    {
      return Vec2(Float(), Float());
    }

    static Vec2 Vector2(float min, float max)
    {
      return Vec2(Float() * (max - min) + min, Float() * (max - min) + min);
    }
  };
}