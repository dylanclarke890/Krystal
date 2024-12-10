#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  class MatrixIterator
  {
  public:
    using mat_t = matrix_t<TComponent, RL, CL>;

    constexpr MatrixIterator(const mat_t &matrix, vec_length_t componentIndex) noexcept
        : _matrix(matrix), _index(componentIndex)
    {
    }

    constexpr MatrixIterator &operator++() noexcept
    {
      ++_index;
      return *this;
    }

    NO_DISCARD constexpr bool operator!=(const MatrixIterator &other) const noexcept
    {
      return _index != other._index;
    }

    NO_DISCARD constexpr TComponent operator*() const noexcept
    {
      const auto col = _index / RL;
      const auto row = _index % RL;
      return _matrix[col][row];
    }

  private:
    const mat_t &_matrix;
    vec_length_t _index;
  };

  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Begin(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    return MatrixIterator<TComponent, RL, CL>(m, 0);
  }

  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto End(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    return MatrixIterator<TComponent, RL, CL>(m, RL * CL);
  }
}