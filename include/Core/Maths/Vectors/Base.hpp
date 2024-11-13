#pragma once

#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

namespace Krys::Maths
{
  using vec_length_t = ushort;

  template <IsArithmeticT TComponent, vec_length_t Length>
  struct Vector;

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