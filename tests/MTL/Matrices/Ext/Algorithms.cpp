#include "MTL/Matrices/Ext/Algorithms.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat2x3.hpp"
#include "MTL/Matrices/Mat2x4.hpp"
#include "MTL/Matrices/Mat3x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x2.hpp"
#include "MTL/Matrices/Mat4x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

#pragma region Test Helpers

  constexpr auto Square = [](int value)
  {
    return value * value;
  };

  constexpr auto AddTwo = [](int left, int right)
  {
    return left + right;
  };

  constexpr auto AddThree = [](int first, int second, int third)
  {
    return first + second + third;
  };

#pragma endregion Test Helpers

  static void Test_Mat2x2_Algorithms()
  {
    using mat_t = mat2x2_t<int>;
    constexpr mat_t mat {{1, 2}, {3, 4}};

    constexpr int forEachSum = [&mat]()
    {
      int total = 0;
      ForEach(mat, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Mat2x2 ForEach", forEachSum, 10);
    KRYS_EXPECT_EQUAL("Mat2x2 MapEach", MapEach(mat, Square), mat_t({1, 4}, {9, 16}));
    KRYS_EXPECT_EQUAL("Mat2x2 Zip(Two)", Zip(mat, mat_t {{2, 3}, {4, 5}}, AddTwo), mat_t({3, 5}, {7, 9}));
    KRYS_EXPECT_EQUAL("Mat2x2 Zip(Three)", Zip(mat, mat_t {{2, 3}, {4, 5}}, mat_t {{2, 3}, {4, 5}}, AddThree),
                      mat_t({5, 8}, {11, 14}));
    KRYS_EXPECT_EQUAL("Mat2x2 Sum(Basic)", Sum(mat), 10);
    KRYS_EXPECT_EQUAL("Mat2x2 Sum(WithFunc)", Sum(mat, Square), 30);
    KRYS_EXPECT_EQUAL("Mat2x2 MinOf", MinOf(mat), 1);
    KRYS_EXPECT_EQUAL("Mat2x2 MaxOf", MaxOf(mat), 4);
  }

  static void Test_Mat2x3_Algorithms()
  {
    using mat_t = mat2x3_t<int>;
    constexpr mat_t mat {{1, 2}, {3, 4}, {5, 6}};

    constexpr int forEachSum = [&mat]()
    {
      int total = 0;
      ForEach(mat, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Mat2x3 ForEach", forEachSum, 21);
    KRYS_EXPECT_EQUAL("Mat2x3 MapEach", MapEach(mat, Square), mat_t({1, 4}, {9, 16}, {25, 36}));
    KRYS_EXPECT_EQUAL("Mat2x3 Zip(Two)", Zip(mat, mat_t {{2, 3}, {4, 5}, {6, 7}}, AddTwo),
                      mat_t({3, 5}, {7, 9}, {11, 13}));
    KRYS_EXPECT_EQUAL("Mat2x3 Zip(Three)",
                      Zip(mat, mat_t {{2, 3}, {4, 5}, {6, 7}}, mat_t {{2, 3}, {4, 5}, {6, 7}}, AddThree),
                      mat_t({5, 8}, {11, 14}, {17, 20}));
    KRYS_EXPECT_EQUAL("Mat2x3 Sum(Basic)", Sum(mat), 21);
    KRYS_EXPECT_EQUAL("Mat2x3 Sum(WithFunc)", Sum(mat, Square), 91);
    KRYS_EXPECT_EQUAL("Mat2x3 MinOf", MinOf(mat), 1);
    KRYS_EXPECT_EQUAL("Mat2x3 MaxOf", MaxOf(mat), 6);
  }

  static void Test_Mat2x4_Algorithms()
  {
    using mat_t = mat2x4_t<int>;
    constexpr mat_t mat {{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    constexpr int forEachSum = [&mat]()
    {
      int total = 0;
      ForEach(mat, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Mat2x4 ForEach", forEachSum, 36);
    KRYS_EXPECT_EQUAL("Mat2x4 MapEach", MapEach(mat, Square), mat_t({1, 4}, {9, 16}, {25, 36}, {49, 64}));
    KRYS_EXPECT_EQUAL("Mat2x4 Zip(Two)", Zip(mat, mat_t {{2, 3}, {4, 5}, {6, 7}, {6, 7}}, AddTwo),
                      mat_t({3, 5}, {7, 9}, {11, 13}, {13, 15}));
    KRYS_EXPECT_EQUAL(
      "Mat2x4 Zip(Three)",
      Zip(mat, mat_t {{2, 3}, {4, 5}, {6, 7}, {6, 7}}, mat_t {{2, 3}, {4, 5}, {6, 7}, {6, 7}}, AddThree),
      mat_t({5, 8}, {11, 14}, {17, 20}, {19, 22}));
    KRYS_EXPECT_EQUAL("Mat2x4 Sum(Basic)", Sum(mat), 36);
    KRYS_EXPECT_EQUAL("Mat2x4 Sum(WithFunc)", Sum(mat, Square), 204);
    KRYS_EXPECT_EQUAL("Mat2x4 MinOf", MinOf(mat), 1);
    KRYS_EXPECT_EQUAL("Mat2x4 MaxOf", MaxOf(mat), 8);
  }

  static void Test_Mat3x2_Algorithms()
  {
    using mat_t = mat3x2_t<int>;
    constexpr mat_t mat {{1, 2, 3}, {4, 5, 6}};

    constexpr int forEachSum = [&mat]()
    {
      int total = 0;
      ForEach(mat, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Mat3x2 ForEach", forEachSum, 21);
    KRYS_EXPECT_EQUAL("Mat3x2 MapEach", MapEach(mat, Square), mat_t({1, 4, 9}, {16, 25, 36}));
    KRYS_EXPECT_EQUAL("Mat3x2 Zip(Two)", Zip(mat, mat_t {{2, 3, 4}, {5, 6, 7}}, AddTwo),
                      mat_t({3, 5, 7}, {9, 11, 13}));
    KRYS_EXPECT_EQUAL("Mat3x2 Zip(Three)",
                      Zip(mat, mat_t {{2, 3, 4}, {5, 6, 7}}, mat_t {{2, 3, 4}, {5, 6, 7}}, AddThree),
                      mat_t({5, 8, 11}, {14, 17, 20}));
    KRYS_EXPECT_EQUAL("Mat3x2 Sum(Basic)", Sum(mat), 21);
    KRYS_EXPECT_EQUAL("Mat3x2 Sum(WithFunc)", Sum(mat, Square), 91);
    KRYS_EXPECT_EQUAL("Mat3x2 MinOf", MinOf(mat), 1);
    KRYS_EXPECT_EQUAL("Mat3x2 MaxOf", MaxOf(mat), 6);
  }

  static void Test_Mat3x3_Algorithms()
  {
    using mat_t = mat3x3_t<int>;
    constexpr mat_t mat {{1, 2, 3}, {4, 5, 4}, {3, 2, 1}};

    constexpr int forEachSum = [&mat]()
    {
      int total = 0;
      ForEach(mat, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Mat3x3 ForEach", forEachSum, 25);
    KRYS_EXPECT_EQUAL("Mat3x3 MapEach", MapEach(mat, Square), mat_t({1, 4, 9}, {16, 25, 16}, {9, 4, 1}));
    KRYS_EXPECT_EQUAL("Mat3x3 Zip(Two)", Zip(mat, mat_t {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}}, AddTwo),
                      mat_t({3, 5, 7}, {9, 11, 11}, {11, 11, 11}));
    KRYS_EXPECT_EQUAL(
      "Mat3x3 Zip(Three)",
      Zip(mat, mat_t {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}}, mat_t {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}}, AddThree),
      mat_t({5, 8, 11}, {14, 17, 18}, {19, 20, 21}));
    KRYS_EXPECT_EQUAL("Mat3x3 Sum(Basic)", Sum(mat), 25);
    KRYS_EXPECT_EQUAL("Mat3x3 Sum(WithFunc)", Sum(mat, Square), 85);
    KRYS_EXPECT_EQUAL("Mat3x3 MinOf", MinOf(mat), 1);
    KRYS_EXPECT_EQUAL("Mat3x3 MaxOf", MaxOf(mat), 5);
  }

  static void Test_Mat3x4_Algorithms()
  {
    using mat_t = mat3x4_t<int>;
    constexpr mat_t mat {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};

    constexpr int forEachSum = [&mat]()
    {
      int total = 0;
      ForEach(mat, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Mat3x4 ForEach", forEachSum, 78);
    KRYS_EXPECT_EQUAL("Mat3x4 MapEach", MapEach(mat, Square),
                      mat_t({1, 4, 9}, {16, 25, 36}, {49, 64, 81}, {100, 121, 144}));
    KRYS_EXPECT_EQUAL("Mat3x4 Zip(Two)",
                      Zip(mat, mat_t {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}, {11, 12, 13}}, AddTwo),
                      mat_t({3, 5, 7}, {9, 11, 13}, {15, 17, 19}, {21, 23, 25}));
    KRYS_EXPECT_EQUAL("Mat3x4 Zip(Three)",
                      Zip(mat, mat_t {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}, {11, 12, 13}},
                          mat_t {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}, {11, 12, 13}}, AddThree),
                      mat_t({5, 8, 11}, {14, 17, 20}, {23, 26, 29}, {32, 35, 38}));
    KRYS_EXPECT_EQUAL("Mat3x4 Sum(Basic)", Sum(mat), 78);
    KRYS_EXPECT_EQUAL("Mat3x4 Sum(WithFunc)", Sum(mat, Square), 650);
    KRYS_EXPECT_EQUAL("Mat3x4 MinOf", MinOf(mat), 1);
    KRYS_EXPECT_EQUAL("Mat3x4 MaxOf", MaxOf(mat), 12);
  }

  static void Test_Mat4x2_Algorithms()
  {
    using mat_t = mat4x2_t<int>;
    constexpr mat_t mat {{1, 2, 3, 4}, {5, 6, 7, 8}};

    constexpr int forEachSum = [&mat]()
    {
      int total = 0;
      ForEach(mat, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Mat4x2 ForEach", forEachSum, 36);
    KRYS_EXPECT_EQUAL("Mat4x2 MapEach", MapEach(mat, Square), mat_t({1, 4, 9, 16}, {25, 36, 49, 64}));
    KRYS_EXPECT_EQUAL("Mat4x2 Zip(Two)", Zip(mat, mat_t {{2, 3, 4, 5}, {6, 7, 8, 9}}, AddTwo),
                      mat_t({3, 5, 7, 9}, {11, 13, 15, 17}));
    KRYS_EXPECT_EQUAL(
      "Mat4x2 Zip(Three)",
      Zip(mat, mat_t {{2, 3, 4, 5}, {6, 7, 8, 9}}, mat_t {{2, 3, 4, 5}, {6, 7, 8, 9}}, AddThree),
      mat_t({5, 8, 11, 14}, {17, 20, 23, 26}));
    KRYS_EXPECT_EQUAL("Mat4x2 Sum(Basic)", Sum(mat), 36);
    KRYS_EXPECT_EQUAL("Mat4x2 Sum(WithFunc)", Sum(mat, Square), 204);
    KRYS_EXPECT_EQUAL("Mat4x2 MinOf", MinOf(mat), 1);
    KRYS_EXPECT_EQUAL("Mat4x2 MaxOf", MaxOf(mat), 8);
  }

  static void Test_Mat4x3_Algorithms()
  {
    using mat_t = mat4x3_t<int>;
    constexpr mat_t mat {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    constexpr int forEachSum = [&mat]()
    {
      int total = 0;
      ForEach(mat, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Mat4x3 ForEach", forEachSum, 78);
    KRYS_EXPECT_EQUAL("Mat4x3 MapEach", MapEach(mat, Square),
                      mat_t({1, 4, 9, 16}, {25, 36, 49, 64}, {81, 100, 121, 144}));
    KRYS_EXPECT_EQUAL("Mat4x3 Zip(Two)",
                      Zip(mat, mat_t {{2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}}, AddTwo),
                      mat_t({3, 5, 7, 9}, {11, 13, 15, 17}, {19, 21, 23, 25}));
    KRYS_EXPECT_EQUAL("Mat4x3 Zip(Three)",
                      Zip(mat, mat_t {{2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}},
                          mat_t {{2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}}, AddThree),
                      mat_t({5, 8, 11, 14}, {17, 20, 23, 26}, {29, 32, 35, 38}));
    KRYS_EXPECT_EQUAL("Mat4x3 Sum(Basic)", Sum(mat), 78);
    KRYS_EXPECT_EQUAL("Mat4x3 Sum(WithFunc)", Sum(mat, Square), 650);
    KRYS_EXPECT_EQUAL("Mat4x3 MinOf", MinOf(mat), 1);
    KRYS_EXPECT_EQUAL("Mat4x3 MaxOf", MaxOf(mat), 12);
  }

  static void Test_Mat4x4_Algorithms()
  {
    using mat_t = mat4x4_t<int>;
    constexpr mat_t mat {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

    constexpr int forEachSum = [&mat]()
    {
      int total = 0;
      ForEach(mat, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Mat4x4 ForEach", forEachSum, 136);
    KRYS_EXPECT_EQUAL("Mat4x4 MapEach", MapEach(mat, Square),
                      mat_t({1, 4, 9, 16}, {25, 36, 49, 64}, {81, 100, 121, 144}, {169, 196, 225, 256}));
    KRYS_EXPECT_EQUAL(
      "Mat4x4 Zip(Two)",
      Zip(mat, mat_t {{2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}, {14, 15, 16, 17}}, AddTwo),
      mat_t({3, 5, 7, 9}, {11, 13, 15, 17}, {19, 21, 23, 25}, {27, 29, 31, 33}));
    KRYS_EXPECT_EQUAL("Mat4x4 Zip(Three)",
                      Zip(mat, mat_t {{2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}, {14, 15, 16, 17}},
                          mat_t {{2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}, {14, 15, 16, 17}}, AddThree),
                      mat_t({5, 8, 11, 14}, {17, 20, 23, 26}, {29, 32, 35, 38}, {41, 44, 47, 50}));
    KRYS_EXPECT_EQUAL("Mat4x4 Sum(Basic)", Sum(mat), 136);
    KRYS_EXPECT_EQUAL("Mat4x4 Sum(WithFunc)", Sum(mat, Square), 1'496);
    KRYS_EXPECT_EQUAL("Mat4x4 MinOf", MinOf(mat), 1);
    KRYS_EXPECT_EQUAL("Mat4x4 MaxOf", MaxOf(mat), 16);
  }
}
