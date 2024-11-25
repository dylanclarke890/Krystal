#pragma once

#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Base/Attributes.hpp"

namespace Krys::MTL
{
  using vec_length_t = ushort;

  template <IsArithmeticT TComponent, vec_length_t Length>
  struct Vector;

  template <IsArithmeticT TComponent, vec_length_t Length>
  using vector_t = Vector<TComponent, Length>;

  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto operator+(const TComponent &scalar, const vector_t<TComponent, L> &obj)
  {
    return obj + scalar;
  }

  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto operator*(const TComponent &scalar, const vector_t<TComponent, L> &obj)
  {
    return obj * scalar;
  }

  /// @brief Checks that type `TVector` supports all basic maths operations, both with another `TVector` and
  /// with the primitive numeric type `TComponent`, along with other requirements such as being copyable and
  /// assignable etc.
  template <typename TVector, typename TComponent>
  concept IsVector = IsComparableT<TVector> && IsNegatableT<TVector> && IsCopyableT<TVector>
                     && SupportsArithmeticOperations<TVector, TVector> && requires(TVector vec) {
                          { vec.GetLength() } -> std::same_as<vec_length_t>;
                          { vec[0] } -> std::same_as<TComponent>;
                        } && IsArithmeticT<TComponent> && SupportsArithmeticOperations<TVector, TComponent>;
}