#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent, vec_length_t L>
  class VectorIterator
  {
  public:
    using vec_t = vector_t<TComponent, L>;

    constexpr VectorIterator(const vec_t &vector, vec_length_t componentIndex) noexcept
        : _vector(vector), _index(componentIndex)
    {
    }

    constexpr VectorIterator &operator++() noexcept
    {
      ++_index;
      return *this;
    }

    NO_DISCARD constexpr bool operator!=(const VectorIterator &other) const noexcept
    {
      return _index != other._index;
    }

    NO_DISCARD constexpr TComponent operator*() const noexcept
    {
      return _vector[_index];
    }

  private:
    const vec_t &_vector;
    vec_length_t _index;
  };

  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Begin(const vector_t<TComponent, L> &v) noexcept
  {
    return VectorIterator<TComponent, L>(v, 0);
  }

  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto End(const vector_t<TComponent, L> &v) noexcept
  {
    return VectorIterator<TComponent, L>(v, L);
  }
}