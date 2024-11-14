#pragma once

#include "Base/Concepts.hpp"
#include "Base/Defines.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Matrices/Mat2x2.hpp"
#include "Core/Maths/Matrices/Mat2x3.hpp"
#include "Core/Maths/Matrices/Mat2x4.hpp"
#include "Core/Maths/Matrices/Mat3x2.hpp"
#include "Core/Maths/Matrices/Mat3x3.hpp"
#include "Core/Maths/Matrices/Mat3x4.hpp"
#include "Core/Maths/Matrices/Mat4x2.hpp"
#include "Core/Maths/Matrices/Mat4x3.hpp"
#include "Core/Maths/Matrices/Mat4x4.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using mat2x2_t = MTL::Matrix<TComponent, 2, 2>;
  using Mat2 = mat2x2_t<float>;
  using Mat2b = mat2x2_t<bool>;
  using Mat2f = mat2x2_t<float>;
  using Mat2d = mat2x2_t<double>;
  using Mat2i = mat2x2_t<int>;
  using Mat2u = mat2x2_t<uint>;
  using Mat2c = mat2x2_t<char>;
  using Mat2uc = mat2x2_t<uchar>;
  using Mat2s = mat2x2_t<short>;
  using Mat2us = mat2x2_t<ushort>;
  using Mat2l = mat2x2_t<long>;
  using Mat2ul = mat2x2_t<ulong>;
  using Mat2ll = mat2x2_t<long long>;
  using Mat2ull = mat2x2_t<unsigned long long>;

  template <IsArithmeticT TComponent>
  using mat2x3_t = MTL::Matrix<TComponent, 2, 3>;

  template <IsArithmeticT TComponent>
  using mat2x4_t = MTL::Matrix<TComponent, 2, 4>;

  template <IsArithmeticT TComponent>
  using mat3x2_t = MTL::Matrix<TComponent, 3, 2>;

  template <IsArithmeticT TComponent>
  using mat3x3_t = MTL::Matrix<TComponent, 3, 3>;
  using Mat3 = mat3x3_t<float>;

  template <IsArithmeticT TComponent>
  using mat3x4_t = MTL::Matrix<TComponent, 3, 4>;

  template <IsArithmeticT TComponent>
  using mat4x2_t = MTL::Matrix<TComponent, 4, 2>;

  template <IsArithmeticT TComponent>
  using mat4x3_t = MTL::Matrix<TComponent, 4, 3>;

  template <IsArithmeticT TComponent>
  using mat4x4_t = MTL::Matrix<TComponent, 4, 4>;
}