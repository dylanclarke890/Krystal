#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Classification.hpp"
#include "Core/Maths/Vectors/Algorithms.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Checks if each component of the vector is NaN (Not a Number).
  /// @tparam TComponent A floating-point type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `true` if the corresponding component in `v` is NaN, otherwise
  /// `false`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<bool, L> IsNaN(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, L>(v, [](T val) -> bool { return MTL::IsNaN(val); });
  }

  /// @brief Checks if each component of the vector is finite.
  /// @tparam TComponent A floating-point type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `true` if the corresponding component in `v` is finite,
  /// otherwise `false`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<bool, L> IsFinite(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, L>(v, [](T val) -> bool { return MTL::IsFinite(val); });
  }

  /// @brief Checks if each component of the vector is infinite.
  /// @tparam TComponent A floating-point type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `true` if the corresponding component in `v` is infinite,
  /// otherwise `false`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<bool, L> IsInf(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, L>(v, [](T val) -> bool { return MTL::IsInf(val); });
  }

  /// @brief Checks if each component of the vector is normal.
  /// @tparam TComponent A floating-point type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `true` if the corresponding component in `v` is normal,
  /// otherwise `false`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<bool, L> IsNormal(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, L>(v, [](T val) -> bool { return MTL::IsNormal(val); });
  }

  /// @brief Checks if each component of the vector is denormalized.
  /// @tparam TComponent A floating-point type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `true` if the corresponding component in `v` is denormalized,
  /// otherwise `false`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<bool, L> IsDenormal(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, L>(v, [](T val) -> bool { return MTL::IsDenormal(val); });
  }

  /// @brief Checks if each component of the vector is even.
  /// @tparam TComponent An arithmetic type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `true` if the corresponding component in `v` is even, otherwise
  /// `false`.
  template <IsSignedT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<bool, L> IsEven(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, L>(v, [](T val) -> bool { return MTL::IsEven(val); });
  }

  /// @brief Checks if each component of the vector is odd.
  /// @tparam TComponent An arithmetic type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `true` if the corresponding component in `v` is odd, otherwise
  /// `false`.
  template <IsSignedT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<bool, L> IsOdd(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, L>(v, [](T val) -> bool { return MTL::IsOdd(val); });
  }

  /// @brief Checks if each component of the vector is positive.
  /// @tparam TComponent An arithmetic type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `true` if the corresponding component in `v` is positive,
  /// otherwise `false`.
  template <IsSignedT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<bool, L> IsPositive(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, L>(v, [](T val) -> bool { return MTL::IsPositive(val); });
  }

  /// @brief Checks if each component of the vector is negative.
  /// @tparam TComponent An arithmetic type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `true` if the corresponding component in `v` is negative,
  /// otherwise `false`.
  template <IsSignedT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<bool, L> IsNegative(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, bool, L>(v, [](T val) -> bool { return MTL::IsNegative(val); });
  }

  /// @brief Checks the sign of each component in the given vector.
  /// @tparam TComponent A signed arithmetic type.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @return A vector where each component is `1` if `v[i] > 0`, `0` if `v[i] == 0`, or `-1` if `v[i] < 0`.
  template <IsSignedT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Sign(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Sign(val); });
  }
}