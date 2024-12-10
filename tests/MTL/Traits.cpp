#include "MTL/Traits.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Scalar_Traits()
  {
    using test_t = float;
    KRYS_EXPECT_FALSE("Traits - Scalar(IsVec)", MTL::Traits<test_t>::IsVec);
    KRYS_EXPECT_FALSE("Traits - Scalar(IsMat)", MTL::Traits<test_t>::IsMat);
    KRYS_EXPECT_EQUAL("Traits - Scalar(TotalComponents)", MTL::Traits<test_t>::TotalComponents, 1);
  }

  static void Test_Vector_Traits()
  {
    using test_t = MTL::vector_t<float, 4>;
    KRYS_EXPECT_TRUE("Traits - Vector(IsVec)", MTL::Traits<test_t>::IsVec);
    KRYS_EXPECT_FALSE("Traits - Vector(IsMat)", MTL::Traits<test_t>::IsMat);
    KRYS_EXPECT_EQUAL("Traits - Vector(TotalComponents)", MTL::Traits<test_t>::TotalComponents, 4);
    KRYS_EXPECT_EQUAL("Traits - Vector(Length)", MTL::Traits<test_t>::Length, 4);
  }

  static void Test_Matrix_Traits()
  {
    using test_t = MTL::matrix_t<float, 4, 4>;
    KRYS_EXPECT_FALSE("Traits - Matrix(IsVec)", MTL::Traits<test_t>::IsVec);
    KRYS_EXPECT_TRUE("Traits - Matrix(IsMat)", MTL::Traits<test_t>::IsMat);
    KRYS_EXPECT_FALSE("Traits - Matrix(IsRowMajor)", MTL::Traits<test_t>::IsRowMajor);
    KRYS_EXPECT_TRUE("Traits - Matrix(IsSquareMatrix)", MTL::Traits<test_t>::IsSquareMatrix);
    KRYS_EXPECT_EQUAL("Traits - Matrix(TotalComponents)", MTL::Traits<test_t>::TotalComponents, 16);
  }
}