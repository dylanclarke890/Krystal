#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Algorithms.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Scalars/Classification.hpp"

namespace Krys::MTL
{
  /// @brief Checks if each component of the matrix is NaN (Not a Number).
  /// @tparam TComponent A floating-point type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `true` if the corresponding component in `m` is NaN, otherwise
  /// `false`.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> IsNaN(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, CL, RL>(m, [](T val) -> bool { return MTL::IsNaN(val); });
  }

  /// @brief Checks if each component of the matrix is finite.
  /// @tparam TComponent A floating-point type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `true` if the corresponding component in `m` is finite,
  /// otherwise `false`.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> IsFinite(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, CL, RL>(m, [](T val) -> bool { return MTL::IsFinite(val); });
  }

  /// @brief Checks if each component of the matrix is infinite.
  /// @tparam TComponent A floating-point type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `true` if the corresponding component in `m` is infinite,
  /// otherwise `false`.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> IsInf(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, CL, RL>(m, [](T val) -> bool { return MTL::IsInf(val); });
  }

  /// @brief Checks if each component of the matrix is normal.
  /// @tparam TComponent A floating-point type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `true` if the corresponding component in `m` is normal,
  /// otherwise `false`.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> IsNormal(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, CL, RL>(m, [](T val) -> bool { return MTL::IsNormal(val); });
  }

  /// @brief Checks if each component of the matrix is denormalized.
  /// @tparam TComponent A floating-point type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `true` if the corresponding component in `m` is denormalized,
  /// otherwise `false`.
  template <IsFloatingPointT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> IsDenormal(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, CL, RL>(m, [](T val) -> bool { return MTL::IsDenormal(val); });
  }

  /// @brief Checks if each component of the matrix is even.
  /// @tparam TComponent An arithmetic type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `true` if the corresponding component in `m` is even, otherwise
  /// `false`.
  template <IsIntegralT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> IsEven(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, CL, RL>(m, [](T val) -> bool { return MTL::IsEven(val); });
  }

  /// @brief Checks if each component of the matrix is odd.
  /// @tparam TComponent An arithmetic type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `true` if the corresponding component in `m` is odd, otherwise
  /// `false`.
  template <IsIntegralT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> IsOdd(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, CL, RL>(m, [](T val) -> bool { return MTL::IsOdd(val); });
  }

  /// @brief Checks if each component of the matrix is positive.
  /// @tparam TComponent An arithmetic type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `true` if the corresponding component in `m` is positive,
  /// otherwise `false`.
  template <IsSignedT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> IsPositive(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, CL, RL>(m, [](T val) -> bool { return MTL::IsPositive(val); });
  }

  /// @brief Checks if each component of the matrix is negative.
  /// @tparam TComponent An arithmetic type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `true` if the corresponding component in `m` is negative,
  /// otherwise `false`.
  template <IsSignedT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> IsNegative(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, CL, RL>(m, [](T val) -> bool { return MTL::IsNegative(val); });
  }

  /// @brief Checks the sign of each component in the given matrix.
  /// @tparam TComponent A signed arithmetic type.
  /// @tparam CL The column length of the matrix.
  /// @tparam RL The row length of the matrix.
  /// @param m The input matrix.
  /// @return A matrix where each component is `1` if `m[i][j] > 0`, `0` if `m[i][j] == 0`, or `-1` if
  /// `m[i][j] < 0`.
  template <IsSignedT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<TComponent, CL, RL> Sign(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, CL, RL>(m, [](T val) -> T { return MTL::Sign(val); });
  }
}
