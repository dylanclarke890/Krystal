#include "MTL/Matrices/Ext/Format.hpp"

#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat2x3.hpp"
#include "MTL/Matrices/Mat2x4.hpp"
#include "MTL/Matrices/Mat3x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x2.hpp"
#include "MTL/Matrices/Mat4x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  template <typename MatT>
  constexpr auto format = [](const MatT &m)
  {
    return std::format("{}", m);
  };

  static int Test_Mat2x2_Format()
  {
    int result = 0;

    using mat_t = mat2x2_t<int>;

    const mat_t a(1, 2, 3, 4);
    const mat_t b(4, 3, 2, 1);

    result += format<mat_t>(a) == "[1, 2]\n[3, 4]";
    result += format<mat_t>(b) == "[4, 3]\n[2, 1]";

    return result;
  }

  static int Test_Mat2x3_Format()
  {
    int result = 0;

    using mat_t = mat2x3_t<int>;

    const mat_t a(1, 2, 3, 4, 5, 6);
    const mat_t b(6, 5, 4, 3, 2, 1);

    result += format<mat_t>(a) == "[1, 2, 3]\n[4, 5, 6]";
    result += format<mat_t>(b) == "[6, 5, 4]\n[3, 2, 1]";

    return result;
  }

  static int Test_Mat2x4_Format()
  {
    int result = 0;

    using mat_t = mat2x4_t<int>;

    const mat_t a(1, 2, 3, 4, 5, 6, 7, 8);
    const mat_t b(8, 7, 6, 5, 4, 3, 2, 1);

    result += format<mat_t>(a) == "[1, 2, 3, 4]\n[5, 6, 7, 8]";
    result += format<mat_t>(b) == "[8, 7, 6, 5]\n[4, 3, 2, 1]";

    return result;
  }

  static int Test_Mat3x2_Format()
  {
    int result = 0;

    using mat_t = mat3x2_t<int>;

    const mat_t a(1, 2, 3, 4, 5, 6);
    const mat_t b(6, 5, 4, 3, 2, 1);

    result += format<mat_t>(a) == "[1, 2]\n[3, 4]\n[5, 6]";
    result += format<mat_t>(b) == "[6, 5]\n[4, 3]\n[2, 1]";

    return result;
  }

  static int Test_Mat3x3_Format()
  {
    int result = 0;

    using mat_t = mat3x3_t<int>;

    const mat_t a(1, 2, 3, 4, 5, 6, 7, 8, 9);
    const mat_t b(9, 8, 7, 6, 5, 4, 3, 2, 1);

    result += format<mat_t>(a) == "[1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]";
    result += format<mat_t>(b) == "[9, 8, 7]\n[6, 5, 4]\n[3, 2, 1]";

    return result;
  }

  static int Test_Mat3x4_Format()
  {
    int result = 0;

    using mat_t = mat3x4_t<int>;

    const mat_t a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    const mat_t b(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);

    result += format<mat_t>(a) == "[1, 2, 3, 4]\n[5, 6, 7, 8]\n[9, 10, 11, 12]";
    result += format<mat_t>(b) == "[12, 11, 10, 9]\n[8, 7, 6, 5]\n[4, 3, 2, 1]";

    return result;
  }

  static int Test_Mat4x2_Format()
  {
    int result = 0;

    using mat_t = mat4x2_t<int>;

    const mat_t a(1, 2, 3, 4, 5, 6, 7, 8);
    const mat_t b(8, 7, 6, 5, 4, 3, 2, 1);

    result += format<mat_t>(a) == "[1, 2]\n[3, 4]\n[5, 6]\n[7, 8]";
    result += format<mat_t>(b) == "[8, 7]\n[6, 5]\n[4, 3]\n[2, 1]";

    return result;
  }

  static int Test_Mat4x3_Format()
  {
    int result = 0;

    using mat_t = mat4x3_t<int>;

    const mat_t a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    const mat_t b(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);

    result += format<mat_t>(a) == "[1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]\n[10, 11, 12]";
    result += format<mat_t>(b) == "[12, 11, 10]\n[9, 8, 7]\n[6, 5, 4]\n[3, 2, 1]";

    return result;
  }

  static int Test_Mat4x4_Format()
  {
    int result = 0;

    using mat_t = mat4x4_t<int>;

    const mat_t a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    const mat_t b(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);

    result += format<mat_t>(a) == "[1, 2, 3, 4]\n[5, 6, 7, 8]\n[9, 10, 11, 12]\n[13, 14, 15, 16]";
    result += format<mat_t>(b) == "[16, 15, 14, 13]\n[12, 11, 10, 9]\n[8, 7, 6, 5]\n[4, 3, 2, 1]";

    return result;
  }

  int main() noexcept
  {
    int result = 0;

    result += Test_Mat2x2_Format();
    result += Test_Mat2x3_Format();
    result += Test_Mat2x4_Format();
    result += Test_Mat3x2_Format();
    result += Test_Mat3x3_Format();
    result += Test_Mat3x4_Format();
    result += Test_Mat4x2_Format();
    result += Test_Mat4x3_Format();
    result += Test_Mat4x4_Format();

    return result;
  }
}