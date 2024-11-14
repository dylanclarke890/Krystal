#pragma once

#include "Base/Concepts.hpp"
#include "Core/Maths/Vectors/Base.hpp"
#include "Core/Maths/Vectors/Vec1.hpp"
#include "Core/Maths/Vectors/Vec2.hpp"
#include "Core/Maths/Vectors/Vec3.hpp"
#include "Core/Maths/Vectors/Vec4.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using vec1_t = MTL::Vector<TComponent, 1>;
  using Vec1 = vec1_t<float>;

  template <IsArithmeticT TComponent>
  using vec2_t = MTL::Vector<TComponent, 2>;
  using Vec2 = vec2_t<float>;

  template <IsArithmeticT TComponent>
  using vec3_t = MTL::Vector<TComponent, 3>;
  using Vec3 = vec3_t<float>;

  template <IsArithmeticT TComponent>
  using vec4_t = MTL::Vector<TComponent, 4>;
  using Vec4 = vec4_t<float>;
}