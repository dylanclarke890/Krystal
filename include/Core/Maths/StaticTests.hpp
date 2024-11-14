#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Base.hpp"
#include "Core/Maths/Matrix.hpp"
#include "Core/Maths/Vector.hpp"
#include "Core/Maths/Vectors/Base.hpp"

#pragma region Test Macros

/// @brief Ensures that `VType` conforms to the `IsVector` concept for the given `CType`.
#define KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, CType)                                                          \
  static_assert(MTL::IsVector<VType<CType>, CType>,                                                          \
                "'" #VType "(" #CType ")' is not a valid Vector implementation.");

/// @brief Ensures that `MType` conforms to the `IsMatrix` concept for the given `CType`.
#define KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, CType)                                                          \
  static_assert(MTL::IsMatrix<MType<CType>, CType>,                                                          \
                "'" #MType "(" #CType ")' is not a valid Matrix implementation.");

/// @brief Ensures that `MType` conforms to the `IsSquareMatrix` concept for the given `CType`.
#define KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, CType)                                                   \
  static_assert(MTL::IsSquareMatrix<MType<CType>, CType>,                                                    \
                "'" #MType "(" #CType ")' is not a valid square Matrix implementation.");

/// @brief Ensures that `VType` conforms to the `IsVector` concept for the supported range of types.
#define KRYS_TEST_VECTOR_CONCEPT(VType)                                                                      \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, bool);                                                                \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, float);                                                               \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, double);                                                              \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, uchar);                                                               \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, char);                                                                \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, ushort);                                                              \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, short);                                                               \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, uint);                                                                \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, int);                                                                 \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, ulong);                                                               \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, long);                                                                \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, unsigned long long);                                                  \
  KRYS_TEST_VECTOR_CONCEPT_TYPE(VType, long long)

/// @brief Ensures that `MType` conforms to the `IsMatrix` concept for the supported range of types.
#define KRYS_TEST_MATRIX_CONCEPT(MType)                                                                      \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, bool);                                                                \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, float);                                                               \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, double);                                                              \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, uchar);                                                               \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, char);                                                                \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, ushort);                                                              \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, short);                                                               \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, uint);                                                                \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, int);                                                                 \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, ulong);                                                               \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, long);                                                                \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, unsigned long long);                                                  \
  KRYS_TEST_MATRIX_CONCEPT_TYPE(MType, long long)

/// @brief Ensures that `MType` conforms to the `IsSquareMatrix` concept for the supported range of types.
#define KRYS_TEST_SQUARE_MATRIX_CONCEPT(MType)                                                               \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, bool);                                                         \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, float);                                                        \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, double);                                                       \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, uchar);                                                        \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, char);                                                         \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, ushort);                                                       \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, short);                                                        \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, uint);                                                         \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, int);                                                          \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, ulong);                                                        \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, long);                                                         \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, unsigned long long);                                           \
  KRYS_TEST_SQUARE_MATRIX_CONCEPT_TYPE(MType, long long)

#define KRYS_MTL_FAIL_MSG(TestName, Type) #TestName " failed for '" #Type "'."

/// @brief Performs basic static tests on `VType` for the common vector methods.
#define KRYS_TEST_COMMON_VECTOR_METHODS(VType)                                                               \
  static_assert(VType(1.0f) == VType(1.0f), KRYS_MTL_FAIL_MSG("Equality comparison", VType));                \
  static_assert(-VType(1.0f) == VType(-1.0f), KRYS_MTL_FAIL_MSG("Unary minus", VType));                      \
  static_assert(VType(1.0f)[0] == 1.0f, KRYS_MTL_FAIL_MSG("'[0]'", VType));                                  \
  static_assert(VType(1.0f) + VType(2.0f) == VType(3.0f), KRYS_MTL_FAIL_MSG("Vec-Vec '+'", VType));          \
  static_assert((VType(1.0f) += VType(2.0f)) == VType(3.0f), KRYS_MTL_FAIL_MSG("Vec-Vec '+='", VType));      \
  static_assert(VType(3.0f) - VType(2.0f) == VType(1.0f), KRYS_MTL_FAIL_MSG("Vec-Vec '-'", VType));          \
  static_assert((VType(3.0f) -= VType(2.0f)) == VType(1.0f), KRYS_MTL_FAIL_MSG("Vec-Vec '-='", VType));      \
  static_assert(VType(3.0f) / VType(3.0f) == VType(1.0f), KRYS_MTL_FAIL_MSG("Vec-Vec '/'", VType));          \
  static_assert((VType(3.0f) /= VType(3.0f)) == VType(1.0f), KRYS_MTL_FAIL_MSG("Vec-Vec '/='", VType));      \
  static_assert(VType(1.0f) * VType(3.0f) == VType(3.0f), KRYS_MTL_FAIL_MSG("Vec-Vec '*'", VType));          \
  static_assert((VType(1.0f) *= VType(3.0f)) == VType(3.0f), KRYS_MTL_FAIL_MSG("Vec-Vec '*='", VType));      \
  static_assert(VType(1.0f) + 2.0f == VType(3.0f), KRYS_MTL_FAIL_MSG("Vec-Scalar '+'", VType));              \
  static_assert((VType(1.0f) += 2.0f) == VType(3.0f), KRYS_MTL_FAIL_MSG("Vec-Scalar '+='", VType));          \
  static_assert(VType(3.0f) - 2.0f == VType(1.0f), KRYS_MTL_FAIL_MSG("Vec-Scalar '-'", VType));              \
  static_assert((VType(3.0f) -= 2.0f) == VType(1.0f), KRYS_MTL_FAIL_MSG("Vec-Scalar '-='", VType));          \
  static_assert(VType(3.0f) / 3.0f == VType(1.0f), KRYS_MTL_FAIL_MSG("Vec-Scalar '/'", VType));              \
  static_assert((VType(3.0f) /= 3.0f) == VType(1.0f), KRYS_MTL_FAIL_MSG("Vec-Scalar '/='", VType));          \
  static_assert(VType(1.0f) * 3.0f == VType(3.0f), KRYS_MTL_FAIL_MSG("Vec-Scalar '*'", VType));              \
  static_assert((VType(1.0f) *= 3.0f) == VType(3.0f), KRYS_MTL_FAIL_MSG("Vec-Scalar '*='", VType))

/// @brief Performs basic static tests on `MType` for the common square matrix methods.
#define KRYS_TEST_COMMON_SQUARE_MATRIX_METHODS(MType)                                                        \
  static_assert(MType(1.0f) == MType(1.0f), KRYS_MTL_FAIL_MSG("Equality comparison", MType));                \
  static_assert(-MType(1.0f) == MType(-1.0f), KRYS_MTL_FAIL_MSG("Unary minus", MType));                      \
  static_assert(MType(1.0f) + MType(2.0f) == MType(3.0f), KRYS_MTL_FAIL_MSG("Mat-Mat '+'", MType));          \
  static_assert((MType(1.0f) += MType(2.0f)) == MType(3.0f), KRYS_MTL_FAIL_MSG("Mat-Mat '+='", MType));      \
  static_assert(MType(3.0f) - MType(2.0f) == MType(1.0f), KRYS_MTL_FAIL_MSG("Mat-Mat '+'", MType));          \
  static_assert((MType(3.0f) -= MType(2.0f)) == MType(1.0f), KRYS_MTL_FAIL_MSG("Mat-Mat '+'", MType));       \
  static_assert(MType(3.0f) / 3.0f == MType(1.0f), KRYS_MTL_FAIL_MSG("Mat-Scalar '/'", MType));              \
  static_assert((MType(3.0f) /= 3.0f) == MType(1.0f), KRYS_MTL_FAIL_MSG("Mat-Scalar '/='", MType));          \
  static_assert(MType(1.0f) * 3.0f == MType(3.0f), KRYS_MTL_FAIL_MSG("Mat-Scalar '*'", MType));              \
  static_assert((MType(1.0f) *= 3.0f) == MType(3.0f), KRYS_MTL_FAIL_MSG("Mat-Scalar '*='", MType));

#pragma endregion Test Macros

namespace Krys::Tests
{
  namespace Vectors
  {
    KRYS_TEST_VECTOR_CONCEPT(vec1_t);
    KRYS_TEST_COMMON_VECTOR_METHODS(Vec1);

    KRYS_TEST_VECTOR_CONCEPT(vec2_t);
    KRYS_TEST_COMMON_VECTOR_METHODS(Vec2);
    static_assert(Vec2(1.0f, 2.0f)[1] == 2.0f, KRYS_MTL_FAIL_MSG("'[1]'", Vec2));

    KRYS_TEST_VECTOR_CONCEPT(vec3_t);
    KRYS_TEST_COMMON_VECTOR_METHODS(Vec3);
    static_assert(Vec3(1.0f, 2.0f, 3.0f)[1] == 2.0f, KRYS_MTL_FAIL_MSG("'[1]'", Vec3));
    static_assert(Vec3(1.0f, 2.0f, 3.0f)[2] == 3.0f, KRYS_MTL_FAIL_MSG("'[2]'", Vec3));

    KRYS_TEST_VECTOR_CONCEPT(vec4_t);
    KRYS_TEST_COMMON_VECTOR_METHODS(Vec4);
    static_assert(Vec4(1.0f, 2.0f, 3.0f, 4.0f)[1] == 2.0f, KRYS_MTL_FAIL_MSG("'[1]'", Vec4));
    static_assert(Vec4(1.0f, 2.0f, 3.0f, 4.0f)[2] == 3.0f, KRYS_MTL_FAIL_MSG("'[2]'", Vec4));
    static_assert(Vec4(1.0f, 2.0f, 3.0f, 4.0f)[3] == 4.0f, KRYS_MTL_FAIL_MSG("'[3]'", Vec4));
  }

  namespace Matrices
  {
    KRYS_TEST_SQUARE_MATRIX_CONCEPT(mat2x2_t);
    KRYS_TEST_COMMON_SQUARE_MATRIX_METHODS(Mat2);
    static_assert(Mat2(1.0f)[0] == Vec2(1.0f, 0.0f), KRYS_MTL_FAIL_MSG("'[0]'", Mat2));
    static_assert(Mat2(1.0f)[1] == Vec2(0.0f, 1.0f), KRYS_MTL_FAIL_MSG("'[1]'", Mat2));
    static_assert(Mat2(1.0f) * Mat2(3.0f) == Mat2(3.0f), KRYS_MTL_FAIL_MSG("Mat-Mat '*'", Mat2));
    static_assert((Mat2(1.0f) *= Mat2(3.0f)) == Mat2(3.0f), KRYS_MTL_FAIL_MSG("Mat-Mat '*='", Mat2));
    static_assert(Mat2(1.0f) + 2.0f == Mat2(Vec2(3.0f, 2.0f), Vec2(2.0f, 3.0f)),
                  KRYS_MTL_FAIL_MSG("Mat-Scalar '+'", Mat2));
    static_assert((Mat2(1.0f) += 2.0f) == Mat2(Vec2(3.0f, 2.0f), Vec2(2.0f, 3.0f)),
                  KRYS_MTL_FAIL_MSG("Mat-Scalar '+='", Mat2));
    static_assert(Mat2(3.0f) - 2.0f == Mat2(Vec2(1.0f, -2.0f), Vec2(-2.0, 1.0f)),
                  KRYS_MTL_FAIL_MSG("Mat-Scalar '-'", Mat2));
    static_assert((Mat2(3.0f) -= 2.0f) == Mat2(Vec2(1.0f, -2.0f), Vec2(-2.0, 1.0f)),
                  KRYS_MTL_FAIL_MSG("Mat-Scalar '-='", Mat2));

    // KRYS_TEST_MATRIX_CONCEPT(mat2x3_t);

    // KRYS_TEST_MATRIX_CONCEPT(mat2x4_t);

    // KRYS_TEST_MATRIX_CONCEPT(mat3x2_t);

    // KRYS_TEST_MATRIX_CONCEPT(mat3x3_t);

    // KRYS_TEST_MATRIX_CONCEPT(mat3x4_t);

    // KRYS_TEST_MATRIX_CONCEPT(mat4x2_t);

    // KRYS_TEST_MATRIX_CONCEPT(mat4x3_t);

    // KRYS_TEST_MATRIX_CONCEPT(mat4x4_t);
  }
}