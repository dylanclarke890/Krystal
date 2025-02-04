#include "MTL/Vectors/Ext/Format.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  template <typename VecT>
  constexpr auto format = [](const VecT &v)
  {
    return std::format("{}", v);
  };

  static int Test_Vec1_Format() noexcept
  {
    int result = 0;

    using vec_t = vec1_t<int>;

    const vec_t a(1);
    const vec_t b(2);

    result += format<vec_t>(a) == "(1)";
    result += format<vec_t>(b) == "(2)";

    return result;
  }

  static int Test_Vec2_Format() noexcept
  {
    int result = 0;

    using vec_t = vec2_t<int>;

    const vec_t a(1, 2);
    const vec_t b(2, 1);

    result += format<vec_t>(a) == "(1, 2)";
    result += format<vec_t>(b) == "(2, 1)";

    return result;
  }

  static int Test_Vec3_Format() noexcept
  {
    int result = 0;

    using vec_t = vec3_t<int>;

    const vec_t a(1, 2, 3);
    const vec_t b(3, 2, 1);

    result += format<vec_t>(a) == "(1, 2, 3)";
    result += format<vec_t>(b) == "(3, 2, 1)";

    return result;
  }

  static int Test_Vec4_Format() noexcept
  {
    int result = 0;

    using vec_t = vec4_t<int>;

    const vec_t a(1, 2, 3, 4);
    const vec_t b(4, 3, 2, 1);

    result += format<vec_t>(a) == "(1, 2, 3, 4)";
    result += format<vec_t>(b) == "(4, 3, 2, 1)";

    return result;
  }

  int main() noexcept
  {
    int result = 0;

    result += Test_Vec1_Format();
    result += Test_Vec2_Format();
    result += Test_Vec3_Format();
    result += Test_Vec4_Format();

    return result;
  }
}