#pragma once

#include "Base/Types.hpp"

namespace Krys::Maths
{
  using count_t = ushort;
  
  template <IsArithmeticT TComponent, count_t Count>
  struct Vector;

  template <typename TVector, typename TComponent>
  concept IVector =
    IsCopyableT<TVector> && IsArithmeticT<TComponent> && requires(TVector vec, TComponent scalar) {
      // Assignment
      { vec = vec } -> std::same_as<TVector &>;

      // Equality
      { vec == vec } -> std::same_as<bool>;
      { vec != vec } -> std::same_as<bool>;

      // Addition
      { vec + vec } -> std::same_as<TVector>;
      { vec += vec } -> std::same_as<TVector &>;
      { vec + scalar } -> std::same_as<TVector>;
      { vec += scalar } -> std::same_as<TVector &>;

      // Subtraction
      { vec - vec } -> std::same_as<TVector>;
      { vec -= vec } -> std::same_as<TVector &>;
      { vec - scalar } -> std::same_as<TVector>;
      { vec -= scalar } -> std::same_as<TVector &>;

      // Division
      { vec / vec } -> std::same_as<TVector>;
      { vec /= vec } -> std::same_as<TVector &>;
      { vec / scalar } -> std::same_as<TVector>;
      { vec /= scalar } -> std::same_as<TVector &>;

      // Multiplication
      { vec *vec } -> std::same_as<TVector>;
      { vec *= vec } -> std::same_as<TVector &>;
      { vec *scalar } -> std::same_as<TVector>;
      { vec *= scalar } -> std::same_as<TVector &>;

      // Unary operators
      { -vec } -> std::same_as<TVector>;
      { +vec } -> std::same_as<TVector>;
    };
}