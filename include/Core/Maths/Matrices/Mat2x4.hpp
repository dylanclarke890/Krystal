#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::Maths
{
  template <IsArithmeticT TComponent>
  struct Matrix<TComponent, 2, 2>
  {
  private:
    static constexpr vec_length_t ColumnLength = 2;
    static constexpr vec_length_t RowLength = 2;

  public:
    using component_t = TComponent;
    using column_t = Vector<component_t, ColumnLength>;
    using row_t = Vector<component_t, RowLength>;

    using mat_t = Matrix<component_t, ColumnLength, RowLength>;
    using mat_transpose_t = Matrix<component_t, RowLength, ColumnLength>;

  private:
    column_t values[2];
  };
}