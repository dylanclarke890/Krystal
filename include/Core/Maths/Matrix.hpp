#pragma once

#include "Base/Concepts.hpp"
#include "Base/Defines.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Matrices/Mat2x2.hpp"
#include "Core/Maths/Matrices/Mat3x3.hpp"
#include "Core/Maths/Matrices/Mat4x4.hpp"

namespace Krys
{
#pragma region Square Matrices

  template <IsArithmeticT TComponent>
  using mat2x2_t = MTL::Matrix<TComponent, 2, 2>;
  using Mat2 = mat2x2_t<float>;

  template <IsArithmeticT TComponent>
  using mat3x3_t = MTL::Matrix<TComponent, 3, 3>;
  using Mat3 = mat3x3_t<float>;

  template <IsArithmeticT TComponent>
  using mat4x4_t = MTL::Matrix<TComponent, 4, 4>;
  using Mat4 = mat4x4_t<float>;

#pragma endregion Square Matrices
}