#pragma once

#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace std
{
  template <>
  struct hash<Krys::Vec1>
  {
    size_t operator()(const Krys::Vec1 &v) const noexcept
    {
      return std::hash<float> {}(v.x);
    }
  };

  template <>
  struct hash<Krys::Vec2>
  {
    size_t operator()(const Krys::Vec2 &v) const noexcept
    {
      return std::hash<float> {}(v.x) ^ std::hash<float> {}(v.y);
    }
  };

  template <>
  struct hash<Krys::Vec3>
  {
    size_t operator()(const Krys::Vec3 &v) const noexcept
    {
      return std::hash<float> {}(v.x) ^ std::hash<float> {}(v.y) ^ std::hash<float> {}(v.z);
    }
  };

  template <>
  struct hash<Krys::Vec4>
  {
    size_t operator()(const Krys::Vec4 &v) const noexcept
    {
      return std::hash<float> {}(v.x) ^ std::hash<float> {}(v.y) ^ std::hash<float> {}(v.z)
             ^ std::hash<float> {}(v.w);
    }
  };
}