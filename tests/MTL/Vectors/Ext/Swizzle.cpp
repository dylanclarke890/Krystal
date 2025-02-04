#include "MTL/Vectors/Ext/Swizzle.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  constexpr Vec1 v1 = {1};
  constexpr Vec2 v2 = {1, 2};
  constexpr Vec3 v3 = {1, 2, 3};
  constexpr Vec4 v4 = {1, 2, 3, 4};

#pragma region Two Components

  static void Test_Swizzle_xx()
  {
    KRYS_EXPECT_EQUAL("Vec1 Swizzle xx", xx(v1), Vec2(1, 1));
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xx", xx(v2), Vec2(1, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xx", xx(v3), Vec2(1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xx", xx(v4), Vec2(1, 1));
  }

  static void Test_Swizzle_xy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xy", xy(v2), Vec2(1, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xy", xy(v3), Vec2(1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xy", xy(v4), Vec2(1, 2));
  }

  static void Test_Swizzle_xz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xz", xz(v3), Vec2(1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xz", xz(v4), Vec2(1, 3));
  }

  static void Test_Swizzle_xw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xw", xw(v4), Vec2(1, 4));
  }

  static void Test_Swizzle_yx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yx", yx(v2), Vec2(2, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yx", yx(v3), Vec2(2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yx", yx(v4), Vec2(2, 1));
  }

  static void Test_Swizzle_yy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yy", yy(v2), Vec2(2, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yy", yy(v3), Vec2(2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yy", yy(v4), Vec2(2, 2));
  }

  static void Test_Swizzle_yz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yz", yz(v3), Vec2(2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yz", yz(v4), Vec2(2, 3));
  }

  static void Test_Swizzle_yw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yw", yw(v4), Vec2(2, 4));
  }

  static void Test_Swizzle_zx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zx", zx(v3), Vec2(3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zx", zx(v4), Vec2(3, 1));
  }

  static void Test_Swizzle_zy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zy", zy(v3), Vec2(3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zy", zy(v4), Vec2(3, 2));
  }

  static void Test_Swizzle_zz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zz", zz(v3), Vec2(3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zz", zz(v4), Vec2(3, 3));
  }

  static void Test_Swizzle_zw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zw", zw(v4), Vec2(3, 4));
  }

  static void Test_Swizzle_wx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wx", wx(v4), Vec2(4, 1));
  }

  static void Test_Swizzle_wy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wy", wy(v4), Vec2(4, 2));
  }

  static void Test_Swizzle_wz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wz", wz(v4), Vec2(4, 3));
  }

  static void Test_Swizzle_ww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ww", ww(v4), Vec2(4, 4));
  }

#pragma endregion Two Components

#pragma region Three Components

  static void Test_Swizzle_xxx()
  {
    KRYS_EXPECT_EQUAL("Vec1 Swizzle xxx", xxx(v1), Vec3(1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xxx", xxx(v2), Vec3(1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxx", xxx(v3), Vec3(1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxx", xxx(v4), Vec3(1, 1, 1));
  }

  static void Test_Swizzle_xxy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xxy", xxy(v2), Vec3(1, 1, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxy", xxy(v3), Vec3(1, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxy", xxy(v4), Vec3(1, 1, 2));
  }

  static void Test_Swizzle_xxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxz", xxz(v3), Vec3(1, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxz", xxz(v4), Vec3(1, 1, 3));
  }

  static void Test_Swizzle_xxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxw", xxw(v4), Vec3(1, 1, 4));
  }

  static void Test_Swizzle_xyx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xyx", xyx(v2), Vec3(1, 2, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyx", xyx(v3), Vec3(1, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyx", xyx(v4), Vec3(1, 2, 1));
  }

  static void Test_Swizzle_xyy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xyy", xyy(v2), Vec3(1, 2, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyy", xyy(v3), Vec3(1, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyy", xyy(v4), Vec3(1, 2, 2));
  }

  static void Test_Swizzle_xyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyz", xyz(v3), Vec3(1, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyz", xyz(v4), Vec3(1, 2, 3));
  }

  static void Test_Swizzle_xyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyw", xyw(v4), Vec3(1, 2, 4));
  }

  static void Test_Swizzle_xzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzx", xzx(v3), Vec3(1, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzx", xzx(v4), Vec3(1, 3, 1));
  }

  static void Test_Swizzle_xzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzy", xzy(v3), Vec3(1, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzy", xzy(v4), Vec3(1, 3, 2));
  }

  static void Test_Swizzle_xzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzz", xzz(v3), Vec3(1, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzz", xzz(v4), Vec3(1, 3, 3));
  }

  static void Test_Swizzle_xzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzw", xzw(v4), Vec3(1, 3, 4));
  }

  static void Test_Swizzle_xwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwx", xwx(v4), Vec3(1, 4, 1));
  }

  static void Test_Swizzle_xwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwy", xwy(v4), Vec3(1, 4, 2));
  }

  static void Test_Swizzle_xwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwz", xwz(v4), Vec3(1, 4, 3));
  }

  static void Test_Swizzle_xww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xww", xww(v4), Vec3(1, 4, 4));
  }

  static void Test_Swizzle_yxx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yxx", yxx(v2), Vec3(2, 1, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxx", yxx(v3), Vec3(2, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxx", yxx(v4), Vec3(2, 1, 1));
  }

  static void Test_Swizzle_yxy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yxy", yxy(v2), Vec3(2, 1, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxy", yxy(v3), Vec3(2, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxy", yxy(v4), Vec3(2, 1, 2));
  }

  static void Test_Swizzle_yxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxz", yxz(v3), Vec3(2, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxz", yxz(v4), Vec3(2, 1, 3));
  }

  static void Test_Swizzle_yxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxw", yxw(v4), Vec3(2, 1, 4));
  }

  static void Test_Swizzle_yyx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yyx", yyx(v2), Vec3(2, 2, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyx", yyx(v3), Vec3(2, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyx", yyx(v4), Vec3(2, 2, 1));
  }

  static void Test_Swizzle_yyy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yyy", yyy(v2), Vec3(2, 2, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyy", yyy(v3), Vec3(2, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyy", yyy(v4), Vec3(2, 2, 2));
  }

  static void Test_Swizzle_yyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyz", yyz(v3), Vec3(2, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyz", yyz(v4), Vec3(2, 2, 3));
  }

  static void Test_Swizzle_yyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyw", yyw(v4), Vec3(2, 2, 4));
  }

  static void Test_Swizzle_yzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzx", yzx(v3), Vec3(2, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzx", yzx(v4), Vec3(2, 3, 1));
  }

  static void Test_Swizzle_yzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzy", yzy(v3), Vec3(2, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzy", yzy(v4), Vec3(2, 3, 2));
  }

  static void Test_Swizzle_yzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzz", yzz(v3), Vec3(2, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzz", yzz(v4), Vec3(2, 3, 3));
  }

  static void Test_Swizzle_yzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzw", yzw(v4), Vec3(2, 3, 4));
  }

  static void Test_Swizzle_ywx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywx", ywx(v4), Vec3(2, 4, 1));
  }

  static void Test_Swizzle_ywy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywy", ywy(v4), Vec3(2, 4, 2));
  }

  static void Test_Swizzle_ywz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywz", ywz(v4), Vec3(2, 4, 3));
  }

  static void Test_Swizzle_yww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yww", yww(v4), Vec3(2, 4, 4));
  }

  static void Test_Swizzle_zxx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxx", zxx(v3), Vec3(3, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxx", zxx(v4), Vec3(3, 1, 1));
  }

  static void Test_Swizzle_zxy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxy", zxy(v3), Vec3(3, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxy", zxy(v4), Vec3(3, 1, 2));
  }

  static void Test_Swizzle_zxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxz", zxz(v3), Vec3(3, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxz", zxz(v4), Vec3(3, 1, 3));
  }

  static void Test_Swizzle_zxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxw", zxw(v4), Vec3(3, 1, 4));
  }

  static void Test_Swizzle_zyx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyx", zyx(v3), Vec3(3, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyx", zyx(v4), Vec3(3, 2, 1));
  }

  static void Test_Swizzle_zyy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyy", zyy(v3), Vec3(3, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyy", zyy(v4), Vec3(3, 2, 2));
  }

  static void Test_Swizzle_zyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyz", zyz(v3), Vec3(3, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyz", zyz(v4), Vec3(3, 2, 3));
  }

  static void Test_Swizzle_zyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyw", zyw(v4), Vec3(3, 2, 4));
  }

  static void Test_Swizzle_zzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzx", zzx(v3), Vec3(3, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzx", zzx(v4), Vec3(3, 3, 1));
  }

  static void Test_Swizzle_zzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzy", zzy(v3), Vec3(3, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzy", zzy(v4), Vec3(3, 3, 2));
  }

  static void Test_Swizzle_zzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzz", zzz(v3), Vec3(3, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzz", zzz(v4), Vec3(3, 3, 3));
  }

  static void Test_Swizzle_zzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzw", zzw(v4), Vec3(3, 3, 4));
  }

  static void Test_Swizzle_zwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwx", zwx(v4), Vec3(3, 4, 1));
  }

  static void Test_Swizzle_zwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwy", zwy(v4), Vec3(3, 4, 2));
  }

  static void Test_Swizzle_zwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwz", zwz(v4), Vec3(3, 4, 3));
  }

  static void Test_Swizzle_zww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zww", zww(v4), Vec3(3, 4, 4));
  }

  static void Test_Swizzle_wxx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxx", wxx(v4), Vec3(4, 1, 1));
  }

  static void Test_Swizzle_wxy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxy", wxy(v4), Vec3(4, 1, 2));
  }

  static void Test_Swizzle_wxz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxz", wxz(v4), Vec3(4, 1, 3));
  }

  static void Test_Swizzle_wxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxw", wxw(v4), Vec3(4, 1, 4));
  }

  static void Test_Swizzle_wyx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyx", wyx(v4), Vec3(4, 2, 1));
  }

  static void Test_Swizzle_wyy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyy", wyy(v4), Vec3(4, 2, 2));
  }

  static void Test_Swizzle_wyz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyz", wyz(v4), Vec3(4, 2, 3));
  }

  static void Test_Swizzle_wyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyw", wyw(v4), Vec3(4, 2, 4));
  }

  static void Test_Swizzle_wzx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzx", wzx(v4), Vec3(4, 3, 1));
  }

  static void Test_Swizzle_wzy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzy", wzy(v4), Vec3(4, 3, 2));
  }

  static void Test_Swizzle_wzz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzz", wzz(v4), Vec3(4, 3, 3));
  }

  static void Test_Swizzle_wzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzw", wzw(v4), Vec3(4, 3, 4));
  }

  static void Test_Swizzle_wwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwx", wwx(v4), Vec3(4, 4, 1));
  }

  static void Test_Swizzle_wwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwy", wwy(v4), Vec3(4, 4, 2));
  }

  static void Test_Swizzle_wwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwz", wwz(v4), Vec3(4, 4, 3));
  }

  static void Test_Swizzle_www()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle www", www(v4), Vec3(4, 4, 4));
  }

#pragma endregion Three Components

#pragma region Four Components

  static void Test_Swizzle_xxxx()
  {
    KRYS_EXPECT_EQUAL("Vec1 Swizzle xxxx", xxxx(v1), Vec4(1, 1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xxxx", xxxx(v2), Vec4(1, 1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxxx", xxxx(v3), Vec4(1, 1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxxx", xxxx(v4), Vec4(1, 1, 1, 1));
  }

  static void Test_Swizzle_xxxy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xxxy", xxxy(v2), Vec4(1, 1, 1, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxxy", xxxy(v3), Vec4(1, 1, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxxy", xxxy(v4), Vec4(1, 1, 1, 2));
  }

  static void Test_Swizzle_xxxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxxz", xxxz(v3), Vec4(1, 1, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxxz", xxxz(v4), Vec4(1, 1, 1, 3));
  }

  static void Test_Swizzle_xxxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxxw", xxxw(v4), Vec4(1, 1, 1, 4));
  }

  static void Test_Swizzle_xxyx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xxyx", xxyx(v2), Vec4(1, 1, 2, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxyx", xxyx(v3), Vec4(1, 1, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxyx", xxyx(v4), Vec4(1, 1, 2, 1));
  }

  static void Test_Swizzle_xxyy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xxyy", xxyy(v2), Vec4(1, 1, 2, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxyy", xxyy(v3), Vec4(1, 1, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxyy", xxyy(v4), Vec4(1, 1, 2, 2));
  }

  static void Test_Swizzle_xxyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxyz", xxyz(v3), Vec4(1, 1, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxyz", xxyz(v4), Vec4(1, 1, 2, 3));
  }

  static void Test_Swizzle_xxyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxyw", xxyw(v4), Vec4(1, 1, 2, 4));
  }

  static void Test_Swizzle_xxzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxzx", xxzx(v3), Vec4(1, 1, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxzx", xxzx(v4), Vec4(1, 1, 3, 1));
  }

  static void Test_Swizzle_xxzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxzy", xxzy(v3), Vec4(1, 1, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxzy", xxzy(v4), Vec4(1, 1, 3, 2));
  }

  static void Test_Swizzle_xxzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xxzz", xxzz(v3), Vec4(1, 1, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxzz", xxzz(v4), Vec4(1, 1, 3, 3));
  }

  static void Test_Swizzle_xxzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxzw", xxzw(v4), Vec4(1, 1, 3, 4));
  }

  static void Test_Swizzle_xxwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxwx", xxwx(v4), Vec4(1, 1, 4, 1));
  }

  static void Test_Swizzle_xxwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxwy", xxwy(v4), Vec4(1, 1, 4, 2));
  }

  static void Test_Swizzle_xxwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxwz", xxwz(v4), Vec4(1, 1, 4, 3));
  }

  static void Test_Swizzle_xxww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xxww", xxww(v4), Vec4(1, 1, 4, 4));
  }

  static void Test_Swizzle_xyxx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xyxx", xyxx(v2), Vec4(1, 2, 1, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyxx", xyxx(v3), Vec4(1, 2, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyxx", xyxx(v4), Vec4(1, 2, 1, 1));
  }

  static void Test_Swizzle_xyxy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xyxy", xyxy(v2), Vec4(1, 2, 1, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyxy", xyxy(v3), Vec4(1, 2, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyxy", xyxy(v4), Vec4(1, 2, 1, 2));
  }

  static void Test_Swizzle_xyxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyxz", xyxz(v3), Vec4(1, 2, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyxz", xyxz(v4), Vec4(1, 2, 1, 3));
  }

  static void Test_Swizzle_xyxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyxw", xyxw(v4), Vec4(1, 2, 1, 4));
  }

  static void Test_Swizzle_xyyx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xyyx", xyyx(v2), Vec4(1, 2, 2, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyyx", xyyx(v3), Vec4(1, 2, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyyx", xyyx(v4), Vec4(1, 2, 2, 1));
  }

  static void Test_Swizzle_xyyy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle xyyy", xyyy(v2), Vec4(1, 2, 2, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyyy", xyyy(v3), Vec4(1, 2, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyyy", xyyy(v4), Vec4(1, 2, 2, 2));
  }

  static void Test_Swizzle_xyyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyyz", xyyz(v3), Vec4(1, 2, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyyz", xyyz(v4), Vec4(1, 2, 2, 3));
  }

  static void Test_Swizzle_xyyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyyw", xyyw(v4), Vec4(1, 2, 2, 4));
  }

  static void Test_Swizzle_xyzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyzx", xyzx(v3), Vec4(1, 2, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyzx", xyzx(v4), Vec4(1, 2, 3, 1));
  }

  static void Test_Swizzle_xyzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyzy", xyzy(v3), Vec4(1, 2, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyzy", xyzy(v4), Vec4(1, 2, 3, 2));
  }

  static void Test_Swizzle_xyzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xyzz", xyzz(v3), Vec4(1, 2, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyzz", xyzz(v4), Vec4(1, 2, 3, 3));
  }

  static void Test_Swizzle_xyzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyzw", xyzw(v4), Vec4(1, 2, 3, 4));
  }

  static void Test_Swizzle_xywx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xywx", xywx(v4), Vec4(1, 2, 4, 1));
  }

  static void Test_Swizzle_xywy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xywy", xywy(v4), Vec4(1, 2, 4, 2));
  }

  static void Test_Swizzle_xywz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xywz", xywz(v4), Vec4(1, 2, 4, 3));
  }

  static void Test_Swizzle_xyww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xyww", xyww(v4), Vec4(1, 2, 4, 4));
  }

  static void Test_Swizzle_xzxx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzxx", xzxx(v3), Vec4(1, 3, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzxx", xzxx(v4), Vec4(1, 3, 1, 1));
  }

  static void Test_Swizzle_xzxy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzxy", xzxy(v3), Vec4(1, 3, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzxy", xzxy(v4), Vec4(1, 3, 1, 2));
  }

  static void Test_Swizzle_xzxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzxz", xzxz(v3), Vec4(1, 3, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzxz", xzxz(v4), Vec4(1, 3, 1, 3));
  }

  static void Test_Swizzle_xzxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzxw", xzxw(v4), Vec4(1, 3, 1, 4));
  }

  static void Test_Swizzle_xzyx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzyx", xzyx(v3), Vec4(1, 3, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzyx", xzyx(v4), Vec4(1, 3, 2, 1));
  }

  static void Test_Swizzle_xzyy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzyy", xzyy(v3), Vec4(1, 3, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzyy", xzyy(v4), Vec4(1, 3, 2, 2));
  }

  static void Test_Swizzle_xzyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzyz", xzyz(v3), Vec4(1, 3, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzyz", xzyz(v4), Vec4(1, 3, 2, 3));
  }

  static void Test_Swizzle_xzyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzyw", xzyw(v4), Vec4(1, 3, 2, 4));
  }

  static void Test_Swizzle_xzzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzzx", xzzx(v3), Vec4(1, 3, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzzx", xzzx(v4), Vec4(1, 3, 3, 1));
  }

  static void Test_Swizzle_xzzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzzy", xzzy(v3), Vec4(1, 3, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzzy", xzzy(v4), Vec4(1, 3, 3, 2));
  }

  static void Test_Swizzle_xzzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle xzzz", xzzz(v3), Vec4(1, 3, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzzz", xzzz(v4), Vec4(1, 3, 3, 3));
  }

  static void Test_Swizzle_xzzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzzw", xzzw(v4), Vec4(1, 3, 3, 4));
  }

  static void Test_Swizzle_xzwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzwx", xzwx(v4), Vec4(1, 3, 4, 1));
  }

  static void Test_Swizzle_xzwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzwy", xzwy(v4), Vec4(1, 3, 4, 2));
  }

  static void Test_Swizzle_xzwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzwz", xzwz(v4), Vec4(1, 3, 4, 3));
  }

  static void Test_Swizzle_xzww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xzww", xzww(v4), Vec4(1, 3, 4, 4));
  }

  static void Test_Swizzle_xwxx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwxx", xwxx(v4), Vec4(1, 4, 1, 1));
  }

  static void Test_Swizzle_xwxy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwxy", xwxy(v4), Vec4(1, 4, 1, 2));
  }

  static void Test_Swizzle_xwxz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwxz", xwxz(v4), Vec4(1, 4, 1, 3));
  }

  static void Test_Swizzle_xwxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwxw", xwxw(v4), Vec4(1, 4, 1, 4));
  }

  static void Test_Swizzle_xwyx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwyx", xwyx(v4), Vec4(1, 4, 2, 1));
  }

  static void Test_Swizzle_xwyy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwyy", xwyy(v4), Vec4(1, 4, 2, 2));
  }

  static void Test_Swizzle_xwyz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwyz", xwyz(v4), Vec4(1, 4, 2, 3));
  }

  static void Test_Swizzle_xwyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwyw", xwyw(v4), Vec4(1, 4, 2, 4));
  }

  static void Test_Swizzle_xwzx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwzx", xwzx(v4), Vec4(1, 4, 3, 1));
  }

  static void Test_Swizzle_xwzy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwzy", xwzy(v4), Vec4(1, 4, 3, 2));
  }

  static void Test_Swizzle_xwzz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwzz", xwzz(v4), Vec4(1, 4, 3, 3));
  }

  static void Test_Swizzle_xwzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwzw", xwzw(v4), Vec4(1, 4, 3, 4));
  }

  static void Test_Swizzle_xwwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwwx", xwwx(v4), Vec4(1, 4, 4, 1));
  }

  static void Test_Swizzle_xwwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwwy", xwwy(v4), Vec4(1, 4, 4, 2));
  }

  static void Test_Swizzle_xwwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwwz", xwwz(v4), Vec4(1, 4, 4, 3));
  }

  static void Test_Swizzle_xwww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle xwww", xwww(v4), Vec4(1, 4, 4, 4));
  }

  static void Test_Swizzle_yxxx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yxxx", yxxx(v2), Vec4(2, 1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxxx", yxxx(v3), Vec4(2, 1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxxx", yxxx(v4), Vec4(2, 1, 1, 1));
  }

  static void Test_Swizzle_yxxy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yxxy", yxxy(v2), Vec4(2, 1, 1, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxxy", yxxy(v3), Vec4(2, 1, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxxy", yxxy(v4), Vec4(2, 1, 1, 2));
  }

  static void Test_Swizzle_yxxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxxz", yxxz(v3), Vec4(2, 1, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxxz", yxxz(v4), Vec4(2, 1, 1, 3));
  }

  static void Test_Swizzle_yxxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxxw", yxxw(v4), Vec4(2, 1, 1, 4));
  }

  static void Test_Swizzle_yxyx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yxyx", yxyx(v2), Vec4(2, 1, 2, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxyx", yxyx(v3), Vec4(2, 1, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxyx", yxyx(v4), Vec4(2, 1, 2, 1));
  }

  static void Test_Swizzle_yxyy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yxyy", yxyy(v2), Vec4(2, 1, 2, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxyy", yxyy(v3), Vec4(2, 1, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxyy", yxyy(v4), Vec4(2, 1, 2, 2));
  }

  static void Test_Swizzle_yxyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxyz", yxyz(v3), Vec4(2, 1, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxyz", yxyz(v4), Vec4(2, 1, 2, 3));
  }

  static void Test_Swizzle_yxyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxyw", yxyw(v4), Vec4(2, 1, 2, 4));
  }

  static void Test_Swizzle_yxzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxzx", yxzx(v3), Vec4(2, 1, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxzx", yxzx(v4), Vec4(2, 1, 3, 1));
  }

  static void Test_Swizzle_yxzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxzy", yxzy(v3), Vec4(2, 1, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxzy", yxzy(v4), Vec4(2, 1, 3, 2));
  }

  static void Test_Swizzle_yxzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yxzz", yxzz(v3), Vec4(2, 1, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxzz", yxzz(v4), Vec4(2, 1, 3, 3));
  }

  static void Test_Swizzle_yxzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxzw", yxzw(v4), Vec4(2, 1, 3, 4));
  }

  static void Test_Swizzle_yxwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxwx", yxwx(v4), Vec4(2, 1, 4, 1));
  }

  static void Test_Swizzle_yxwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxwy", yxwy(v4), Vec4(2, 1, 4, 2));
  }

  static void Test_Swizzle_yxwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxwz", yxwz(v4), Vec4(2, 1, 4, 3));
  }

  static void Test_Swizzle_yxww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yxww", yxww(v4), Vec4(2, 1, 4, 4));
  }

  static void Test_Swizzle_yyxx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yyxx", yyxx(v2), Vec4(2, 2, 1, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyxx", yyxx(v3), Vec4(2, 2, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyxx", yyxx(v4), Vec4(2, 2, 1, 1));
  }

  static void Test_Swizzle_yyxy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yyxy", yyxy(v2), Vec4(2, 2, 1, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyxy", yyxy(v3), Vec4(2, 2, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyxy", yyxy(v4), Vec4(2, 2, 1, 2));
  }

  static void Test_Swizzle_yyxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyxz", yyxz(v3), Vec4(2, 2, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyxz", yyxz(v4), Vec4(2, 2, 1, 3));
  }

  static void Test_Swizzle_yyxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyxw", yyxw(v4), Vec4(2, 2, 1, 4));
  }

  static void Test_Swizzle_yyyx()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yyyx", yyyx(v2), Vec4(2, 2, 2, 1));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyyx", yyyx(v3), Vec4(2, 2, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyyx", yyyx(v4), Vec4(2, 2, 2, 1));
  }

  static void Test_Swizzle_yyyy()
  {
    KRYS_EXPECT_EQUAL("Vec2 Swizzle yyyy", yyyy(v2), Vec4(2, 2, 2, 2));
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyyy", yyyy(v3), Vec4(2, 2, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyyy", yyyy(v4), Vec4(2, 2, 2, 2));
  }

  static void Test_Swizzle_yyyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyyz", yyyz(v3), Vec4(2, 2, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyyz", yyyz(v4), Vec4(2, 2, 2, 3));
  }

  static void Test_Swizzle_yyyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyyw", yyyw(v4), Vec4(2, 2, 2, 4));
  }

  static void Test_Swizzle_yyzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyzx", yyzx(v3), Vec4(2, 2, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyzx", yyzx(v4), Vec4(2, 2, 3, 1));
  }

  static void Test_Swizzle_yyzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyzy", yyzy(v3), Vec4(2, 2, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyzy", yyzy(v4), Vec4(2, 2, 3, 2));
  }

  static void Test_Swizzle_yyzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yyzz", yyzz(v3), Vec4(2, 2, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyzz", yyzz(v4), Vec4(2, 2, 3, 3));
  }

  static void Test_Swizzle_yyzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyzw", yyzw(v4), Vec4(2, 2, 3, 4));
  }

  static void Test_Swizzle_yywx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yywx", yywx(v4), Vec4(2, 2, 4, 1));
  }

  static void Test_Swizzle_yywy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yywy", yywy(v4), Vec4(2, 2, 4, 2));
  }

  static void Test_Swizzle_yywz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yywz", yywz(v4), Vec4(2, 2, 4, 3));
  }

  static void Test_Swizzle_yyww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yyww", yyww(v4), Vec4(2, 2, 4, 4));
  }

  static void Test_Swizzle_yzxx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzxx", yzxx(v3), Vec4(2, 3, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzxx", yzxx(v4), Vec4(2, 3, 1, 1));
  }

  static void Test_Swizzle_yzxy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzxy", yzxy(v3), Vec4(2, 3, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzxy", yzxy(v4), Vec4(2, 3, 1, 2));
  }

  static void Test_Swizzle_yzxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzxz", yzxz(v3), Vec4(2, 3, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzxz", yzxz(v4), Vec4(2, 3, 1, 3));
  }

  static void Test_Swizzle_yzxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzxw", yzxw(v4), Vec4(2, 3, 1, 4));
  }

  static void Test_Swizzle_yzyx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzyx", yzyx(v3), Vec4(2, 3, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzyx", yzyx(v4), Vec4(2, 3, 2, 1));
  }

  static void Test_Swizzle_yzyy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzyy", yzyy(v3), Vec4(2, 3, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzyy", yzyy(v4), Vec4(2, 3, 2, 2));
  }

  static void Test_Swizzle_yzyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzyz", yzyz(v3), Vec4(2, 3, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzyz", yzyz(v4), Vec4(2, 3, 2, 3));
  }

  static void Test_Swizzle_yzyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzyw", yzyw(v4), Vec4(2, 3, 2, 4));
  }

  static void Test_Swizzle_yzzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzzx", yzzx(v3), Vec4(2, 3, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzzx", yzzx(v4), Vec4(2, 3, 3, 1));
  }

  static void Test_Swizzle_yzzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzzy", yzzy(v3), Vec4(2, 3, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzzy", yzzy(v4), Vec4(2, 3, 3, 2));
  }

  static void Test_Swizzle_yzzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle yzzz", yzzz(v3), Vec4(2, 3, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzzz", yzzz(v4), Vec4(2, 3, 3, 3));
  }

  static void Test_Swizzle_yzzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzzw", yzzw(v4), Vec4(2, 3, 3, 4));
  }

  static void Test_Swizzle_yzwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzwx", yzwx(v4), Vec4(2, 3, 4, 1));
  }

  static void Test_Swizzle_yzwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzwy", yzwy(v4), Vec4(2, 3, 4, 2));
  }

  static void Test_Swizzle_yzwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzwz", yzwz(v4), Vec4(2, 3, 4, 3));
  }

  static void Test_Swizzle_yzww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle yzww", yzww(v4), Vec4(2, 3, 4, 4));
  }

  static void Test_Swizzle_ywxx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywxx", ywxx(v4), Vec4(2, 4, 1, 1));
  }

  static void Test_Swizzle_ywxy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywxy", ywxy(v4), Vec4(2, 4, 1, 2));
  }

  static void Test_Swizzle_ywxz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywxz", ywxz(v4), Vec4(2, 4, 1, 3));
  }

  static void Test_Swizzle_ywxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywxw", ywxw(v4), Vec4(2, 4, 1, 4));
  }

  static void Test_Swizzle_ywyx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywyx", ywyx(v4), Vec4(2, 4, 2, 1));
  }

  static void Test_Swizzle_ywyy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywyy", ywyy(v4), Vec4(2, 4, 2, 2));
  }

  static void Test_Swizzle_ywyz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywyz", ywyz(v4), Vec4(2, 4, 2, 3));
  }

  static void Test_Swizzle_ywyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywyw", ywyw(v4), Vec4(2, 4, 2, 4));
  }

  static void Test_Swizzle_ywzx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywzx", ywzx(v4), Vec4(2, 4, 3, 1));
  }

  static void Test_Swizzle_ywzy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywzy", ywzy(v4), Vec4(2, 4, 3, 2));
  }

  static void Test_Swizzle_ywzz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywzz", ywzz(v4), Vec4(2, 4, 3, 3));
  }

  static void Test_Swizzle_ywzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywzw", ywzw(v4), Vec4(2, 4, 3, 4));
  }

  static void Test_Swizzle_ywwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywwx", ywwx(v4), Vec4(2, 4, 4, 1));
  }

  static void Test_Swizzle_ywwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywwy", ywwy(v4), Vec4(2, 4, 4, 2));
  }

  static void Test_Swizzle_ywwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywwz", ywwz(v4), Vec4(2, 4, 4, 3));
  }

  static void Test_Swizzle_ywww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle ywww", ywww(v4), Vec4(2, 4, 4, 4));
  }

  static void Test_Swizzle_zxxx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxxx", zxxx(v3), Vec4(3, 1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxxx", zxxx(v4), Vec4(3, 1, 1, 1));
  }

  static void Test_Swizzle_zxxy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxxy", zxxy(v3), Vec4(3, 1, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxxy", zxxy(v4), Vec4(3, 1, 1, 2));
  }

  static void Test_Swizzle_zxxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxxz", zxxz(v3), Vec4(3, 1, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxxz", zxxz(v4), Vec4(3, 1, 1, 3));
  }

  static void Test_Swizzle_zxxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxxw", zxxw(v4), Vec4(3, 1, 1, 4));
  }

  static void Test_Swizzle_zxyx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxyx", zxyx(v3), Vec4(3, 1, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxyx", zxyx(v4), Vec4(3, 1, 2, 1));
  }

  static void Test_Swizzle_zxyy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxyy", zxyy(v3), Vec4(3, 1, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxyy", zxyy(v4), Vec4(3, 1, 2, 2));
  }

  static void Test_Swizzle_zxyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxyz", zxyz(v3), Vec4(3, 1, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxyz", zxyz(v4), Vec4(3, 1, 2, 3));
  }

  static void Test_Swizzle_zxyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxyw", zxyw(v4), Vec4(3, 1, 2, 4));
  }

  static void Test_Swizzle_zxzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxzx", zxzx(v3), Vec4(3, 1, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxzx", zxzx(v4), Vec4(3, 1, 3, 1));
  }

  static void Test_Swizzle_zxzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxzy", zxzy(v3), Vec4(3, 1, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxzy", zxzy(v4), Vec4(3, 1, 3, 2));
  }

  static void Test_Swizzle_zxzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zxzz", zxzz(v3), Vec4(3, 1, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxzz", zxzz(v4), Vec4(3, 1, 3, 3));
  }

  static void Test_Swizzle_zxzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxzw", zxzw(v4), Vec4(3, 1, 3, 4));
  }

  static void Test_Swizzle_zxwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxwx", zxwx(v4), Vec4(3, 1, 4, 1));
  }

  static void Test_Swizzle_zxwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxwy", zxwy(v4), Vec4(3, 1, 4, 2));
  }

  static void Test_Swizzle_zxwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxwz", zxwz(v4), Vec4(3, 1, 4, 3));
  }

  static void Test_Swizzle_zxww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zxww", zxww(v4), Vec4(3, 1, 4, 4));
  }

  static void Test_Swizzle_zyxx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyxx", zyxx(v3), Vec4(3, 2, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyxx", zyxx(v4), Vec4(3, 2, 1, 1));
  }

  static void Test_Swizzle_zyxy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyxy", zyxy(v3), Vec4(3, 2, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyxy", zyxy(v4), Vec4(3, 2, 1, 2));
  }

  static void Test_Swizzle_zyxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyxz", zyxz(v3), Vec4(3, 2, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyxz", zyxz(v4), Vec4(3, 2, 1, 3));
  }

  static void Test_Swizzle_zyxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyxw", zyxw(v4), Vec4(3, 2, 1, 4));
  }

  static void Test_Swizzle_zyyx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyyx", zyyx(v3), Vec4(3, 2, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyyx", zyyx(v4), Vec4(3, 2, 2, 1));
  }

  static void Test_Swizzle_zyyy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyyy", zyyy(v3), Vec4(3, 2, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyyy", zyyy(v4), Vec4(3, 2, 2, 2));
  }

  static void Test_Swizzle_zyyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyyz", zyyz(v3), Vec4(3, 2, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyyz", zyyz(v4), Vec4(3, 2, 2, 3));
  }

  static void Test_Swizzle_zyyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyyw", zyyw(v4), Vec4(3, 2, 2, 4));
  }

  static void Test_Swizzle_zyzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyzx", zyzx(v3), Vec4(3, 2, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyzx", zyzx(v4), Vec4(3, 2, 3, 1));
  }

  static void Test_Swizzle_zyzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyzy", zyzy(v3), Vec4(3, 2, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyzy", zyzy(v4), Vec4(3, 2, 3, 2));
  }

  static void Test_Swizzle_zyzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zyzz", zyzz(v3), Vec4(3, 2, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyzz", zyzz(v4), Vec4(3, 2, 3, 3));
  }

  static void Test_Swizzle_zyzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyzw", zyzw(v4), Vec4(3, 2, 3, 4));
  }

  static void Test_Swizzle_zywx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zywx", zywx(v4), Vec4(3, 2, 4, 1));
  }

  static void Test_Swizzle_zywy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zywy", zywy(v4), Vec4(3, 2, 4, 2));
  }

  static void Test_Swizzle_zywz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zywz", zywz(v4), Vec4(3, 2, 4, 3));
  }

  static void Test_Swizzle_zyww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zyww", zyww(v4), Vec4(3, 2, 4, 4));
  }

  static void Test_Swizzle_zzxx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzxx", zzxx(v3), Vec4(3, 3, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzxx", zzxx(v4), Vec4(3, 3, 1, 1));
  }

  static void Test_Swizzle_zzxy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzxy", zzxy(v3), Vec4(3, 3, 1, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzxy", zzxy(v4), Vec4(3, 3, 1, 2));
  }

  static void Test_Swizzle_zzxz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzxz", zzxz(v3), Vec4(3, 3, 1, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzxz", zzxz(v4), Vec4(3, 3, 1, 3));
  }

  static void Test_Swizzle_zzxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzxw", zzxw(v4), Vec4(3, 3, 1, 4));
  }

  static void Test_Swizzle_zzyx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzyx", zzyx(v3), Vec4(3, 3, 2, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzyx", zzyx(v4), Vec4(3, 3, 2, 1));
  }

  static void Test_Swizzle_zzyy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzyy", zzyy(v3), Vec4(3, 3, 2, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzyy", zzyy(v4), Vec4(3, 3, 2, 2));
  }

  static void Test_Swizzle_zzyz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzyz", zzyz(v3), Vec4(3, 3, 2, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzyz", zzyz(v4), Vec4(3, 3, 2, 3));
  }

  static void Test_Swizzle_zzyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzyw", zzyw(v4), Vec4(3, 3, 2, 4));
  }

  static void Test_Swizzle_zzzx()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzzx", zzzx(v3), Vec4(3, 3, 3, 1));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzzx", zzzx(v4), Vec4(3, 3, 3, 1));
  }

  static void Test_Swizzle_zzzy()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzzy", zzzy(v3), Vec4(3, 3, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzzy", zzzy(v4), Vec4(3, 3, 3, 2));
  }

  static void Test_Swizzle_zzzz()
  {
    KRYS_EXPECT_EQUAL("Vec3 Swizzle zzzz", zzzz(v3), Vec4(3, 3, 3, 3));
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzzz", zzzz(v4), Vec4(3, 3, 3, 3));
  }

  static void Test_Swizzle_zzzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzzw", zzzw(v4), Vec4(3, 3, 3, 4));
  }

  static void Test_Swizzle_zzwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzwx", zzwx(v4), Vec4(3, 3, 4, 1));
  }

  static void Test_Swizzle_zzwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzwy", zzwy(v4), Vec4(3, 3, 4, 2));
  }

  static void Test_Swizzle_zzwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzwz", zzwz(v4), Vec4(3, 3, 4, 3));
  }

  static void Test_Swizzle_zzww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zzww", zzww(v4), Vec4(3, 3, 4, 4));
  }

  static void Test_Swizzle_zwxx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwxx", zwxx(v4), Vec4(3, 4, 1, 1));
  }

  static void Test_Swizzle_zwxy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwxy", zwxy(v4), Vec4(3, 4, 1, 2));
  }

  static void Test_Swizzle_zwxz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwxz", zwxz(v4), Vec4(3, 4, 1, 3));
  }

  static void Test_Swizzle_zwxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwxw", zwxw(v4), Vec4(3, 4, 1, 4));
  }

  static void Test_Swizzle_zwyx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwyx", zwyx(v4), Vec4(3, 4, 2, 1));
  }

  static void Test_Swizzle_zwyy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwyy", zwyy(v4), Vec4(3, 4, 2, 2));
  }

  static void Test_Swizzle_zwyz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwyz", zwyz(v4), Vec4(3, 4, 2, 3));
  }

  static void Test_Swizzle_zwyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwyw", zwyw(v4), Vec4(3, 4, 2, 4));
  }

  static void Test_Swizzle_zwzx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwzx", zwzx(v4), Vec4(3, 4, 3, 1));
  }

  static void Test_Swizzle_zwzy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwzy", zwzy(v4), Vec4(3, 4, 3, 2));
  }

  static void Test_Swizzle_zwzz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwzz", zwzz(v4), Vec4(3, 4, 3, 3));
  }

  static void Test_Swizzle_zwzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwzw", zwzw(v4), Vec4(3, 4, 3, 4));
  }

  static void Test_Swizzle_zwwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwwx", zwwx(v4), Vec4(3, 4, 4, 1));
  }

  static void Test_Swizzle_zwwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwwy", zwwy(v4), Vec4(3, 4, 4, 2));
  }

  static void Test_Swizzle_zwwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwwz", zwwz(v4), Vec4(3, 4, 4, 3));
  }

  static void Test_Swizzle_zwww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle zwww", zwww(v4), Vec4(3, 4, 4, 4));
  }

  static void Test_Swizzle_wxxx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxxx", wxxx(v4), Vec4(4, 1, 1, 1));
  }

  static void Test_Swizzle_wxxy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxxy", wxxy(v4), Vec4(4, 1, 1, 2));
  }

  static void Test_Swizzle_wxxz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxxz", wxxz(v4), Vec4(4, 1, 1, 3));
  }

  static void Test_Swizzle_wxxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxxw", wxxw(v4), Vec4(4, 1, 1, 4));
  }

  static void Test_Swizzle_wxyx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxyx", wxyx(v4), Vec4(4, 1, 2, 1));
  }

  static void Test_Swizzle_wxyy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxyy", wxyy(v4), Vec4(4, 1, 2, 2));
  }

  static void Test_Swizzle_wxyz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxyz", wxyz(v4), Vec4(4, 1, 2, 3));
  }

  static void Test_Swizzle_wxyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxyw", wxyw(v4), Vec4(4, 1, 2, 4));
  }

  static void Test_Swizzle_wxzx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxzx", wxzx(v4), Vec4(4, 1, 3, 1));
  }

  static void Test_Swizzle_wxzy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxzy", wxzy(v4), Vec4(4, 1, 3, 2));
  }

  static void Test_Swizzle_wxzz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxzz", wxzz(v4), Vec4(4, 1, 3, 3));
  }

  static void Test_Swizzle_wxzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxzw", wxzw(v4), Vec4(4, 1, 3, 4));
  }

  static void Test_Swizzle_wxwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxwx", wxwx(v4), Vec4(4, 1, 4, 1));
  }

  static void Test_Swizzle_wxwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxwy", wxwy(v4), Vec4(4, 1, 4, 2));
  }

  static void Test_Swizzle_wxwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxwz", wxwz(v4), Vec4(4, 1, 4, 3));
  }

  static void Test_Swizzle_wxww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wxww", wxww(v4), Vec4(4, 1, 4, 4));
  }

  static void Test_Swizzle_wyxx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyxx", wyxx(v4), Vec4(4, 2, 1, 1));
  }

  static void Test_Swizzle_wyxy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyxy", wyxy(v4), Vec4(4, 2, 1, 2));
  }

  static void Test_Swizzle_wyxz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyxz", wyxz(v4), Vec4(4, 2, 1, 3));
  }

  static void Test_Swizzle_wyxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyxw", wyxw(v4), Vec4(4, 2, 1, 4));
  }

  static void Test_Swizzle_wyyx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyyx", wyyx(v4), Vec4(4, 2, 2, 1));
  }

  static void Test_Swizzle_wyyy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyyy", wyyy(v4), Vec4(4, 2, 2, 2));
  }

  static void Test_Swizzle_wyyz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyyz", wyyz(v4), Vec4(4, 2, 2, 3));
  }

  static void Test_Swizzle_wyyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyyw", wyyw(v4), Vec4(4, 2, 2, 4));
  }

  static void Test_Swizzle_wyzx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyzx", wyzx(v4), Vec4(4, 2, 3, 1));
  }

  static void Test_Swizzle_wyzy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyzy", wyzy(v4), Vec4(4, 2, 3, 2));
  }

  static void Test_Swizzle_wyzz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyzz", wyzz(v4), Vec4(4, 2, 3, 3));
  }

  static void Test_Swizzle_wyzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyzw", wyzw(v4), Vec4(4, 2, 3, 4));
  }

  static void Test_Swizzle_wywx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wywx", wywx(v4), Vec4(4, 2, 4, 1));
  }

  static void Test_Swizzle_wywy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wywy", wywy(v4), Vec4(4, 2, 4, 2));
  }

  static void Test_Swizzle_wywz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wywz", wywz(v4), Vec4(4, 2, 4, 3));
  }

  static void Test_Swizzle_wyww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wyww", wyww(v4), Vec4(4, 2, 4, 4));
  }

  static void Test_Swizzle_wzxx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzxx", wzxx(v4), Vec4(4, 3, 1, 1));
  }

  static void Test_Swizzle_wzxy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzxy", wzxy(v4), Vec4(4, 3, 1, 2));
  }

  static void Test_Swizzle_wzxz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzxz", wzxz(v4), Vec4(4, 3, 1, 3));
  }

  static void Test_Swizzle_wzxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzxw", wzxw(v4), Vec4(4, 3, 1, 4));
  }

  static void Test_Swizzle_wzyx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzyx", wzyx(v4), Vec4(4, 3, 2, 1));
  }

  static void Test_Swizzle_wzyy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzyy", wzyy(v4), Vec4(4, 3, 2, 2));
  }

  static void Test_Swizzle_wzyz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzyz", wzyz(v4), Vec4(4, 3, 2, 3));
  }

  static void Test_Swizzle_wzyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzyw", wzyw(v4), Vec4(4, 3, 2, 4));
  }

  static void Test_Swizzle_wzzx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzzx", wzzx(v4), Vec4(4, 3, 3, 1));
  }

  static void Test_Swizzle_wzzy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzzy", wzzy(v4), Vec4(4, 3, 3, 2));
  }

  static void Test_Swizzle_wzzz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzzz", wzzz(v4), Vec4(4, 3, 3, 3));
  }

  static void Test_Swizzle_wzzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzzw", wzzw(v4), Vec4(4, 3, 3, 4));
  }

  static void Test_Swizzle_wzwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzwx", wzwx(v4), Vec4(4, 3, 4, 1));
  }

  static void Test_Swizzle_wzwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzwy", wzwy(v4), Vec4(4, 3, 4, 2));
  }

  static void Test_Swizzle_wzwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzwz", wzwz(v4), Vec4(4, 3, 4, 3));
  }

  static void Test_Swizzle_wzww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wzww", wzww(v4), Vec4(4, 3, 4, 4));
  }

  static void Test_Swizzle_wwxx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwxx", wwxx(v4), Vec4(4, 4, 1, 1));
  }

  static void Test_Swizzle_wwxy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwxy", wwxy(v4), Vec4(4, 4, 1, 2));
  }

  static void Test_Swizzle_wwxz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwxz", wwxz(v4), Vec4(4, 4, 1, 3));
  }

  static void Test_Swizzle_wwxw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwxw", wwxw(v4), Vec4(4, 4, 1, 4));
  }

  static void Test_Swizzle_wwyx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwyx", wwyx(v4), Vec4(4, 4, 2, 1));
  }

  static void Test_Swizzle_wwyy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwyy", wwyy(v4), Vec4(4, 4, 2, 2));
  }

  static void Test_Swizzle_wwyz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwyz", wwyz(v4), Vec4(4, 4, 2, 3));
  }

  static void Test_Swizzle_wwyw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwyw", wwyw(v4), Vec4(4, 4, 2, 4));
  }

  static void Test_Swizzle_wwzx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwzx", wwzx(v4), Vec4(4, 4, 3, 1));
  }

  static void Test_Swizzle_wwzy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwzy", wwzy(v4), Vec4(4, 4, 3, 2));
  }

  static void Test_Swizzle_wwzz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwzz", wwzz(v4), Vec4(4, 4, 3, 3));
  }

  static void Test_Swizzle_wwzw()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwzw", wwzw(v4), Vec4(4, 4, 3, 4));
  }

  static void Test_Swizzle_wwwx()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwwx", wwwx(v4), Vec4(4, 4, 4, 1));
  }

  static void Test_Swizzle_wwwy()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwwy", wwwy(v4), Vec4(4, 4, 4, 2));
  }

  static void Test_Swizzle_wwwz()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwwz", wwwz(v4), Vec4(4, 4, 4, 3));
  }

  static void Test_Swizzle_wwww()
  {
    KRYS_EXPECT_EQUAL("Vec4 Swizzle wwww", wwww(v4), Vec4(4, 4, 4, 4));
  }

#pragma endregion Four Components
}