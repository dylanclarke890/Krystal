#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent>
  struct Matrix<TComponent, 2, 3>
  {
  private:
    static constexpr vec_length_t RowLength = 2;
    static constexpr vec_length_t ColLength = 3;

  public:
    using component_t = TComponent;
    using row_t = Vector<component_t, RowLength>;
    using column_t = Vector<component_t, ColLength>;

    using mat_t = Matrix<component_t, RowLength, ColLength>;
    using mat_transpose_t = Matrix<component_t, ColLength, RowLength>;

  private:
    column_t values[3];
  };
}