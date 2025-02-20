#pragma once 

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

#include <limits>

namespace Krys::MTL
{
  /// @tparam TNumber An arithmetic type.
  /// @returns 0.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Zero() noexcept
  {
    return TNumber(0);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 1.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber One() noexcept
  {
    return TNumber(1);
  }

  /// @tparam TNumber A floating point type.
  /// @returns The epsilon constant.
  template <IsFloatingPointT TNumber>
  NO_DISCARD constexpr TNumber Epsilon() noexcept
  {
    return std::numeric_limits<TNumber>::epsilon();
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns pi.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Pi() noexcept
  {
    return TNumber(3.14159265358979323846264338327950288);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns pi * 2.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber TwoPi() noexcept
  {
    return TNumber(6.28318530717958647692528676655900576);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns sqrt(pi).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber RootPi() noexcept
  {
    return TNumber(1.772453850905516027);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns pi / 2.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber HalfPi() noexcept
  {
    return TNumber(1.57079632679489661923132169163975144);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 3/2 * pi.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber ThreeOverTwoPi() noexcept
  {
    return TNumber(4.71238898038468985769396507491925432);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 1/4 * pi.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber QuarterPi() noexcept
  {
    return TNumber(0.785398163397448309615660845819875721);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 1 / pi.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber OneOverPi() noexcept
  {
    return TNumber(0.318309886183790671537767526745028724);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 1 / (2 * pi).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber OneOverTwoPi() noexcept
  {
    return TNumber(0.159154943091895335768883763372514362);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 2 / pi.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber TwoOverPi() noexcept
  {
    return TNumber(0.636619772367581343075535053490057448);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 4 / pi.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber FourOverPi() noexcept
  {
    return TNumber(1.273239544735162686151070106980114898);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 2 / sqrt(pi).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber TwoOverRootPi() noexcept
  {
    return TNumber(1.12837916709551257389615890312154517);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 1 / sqrt(2).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber OneOverRootTwo() noexcept
  {
    return TNumber(0.707106781186547524400844362104849039);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns sqrt(1/2 * pi).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber RootHalfPi() noexcept
  {
    return TNumber(1.253314137315500251);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns sqrt(2 * pi).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber RootTwoPi() noexcept
  {
    return TNumber(2.506628274631000502);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns sqrt(ln(4)).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber RootLnFour() noexcept
  {
    return TNumber(1.17741002251547469);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns e constant.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber e() noexcept
  {
    return TNumber(2.71828182845904523536);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns log10(e), the base-10 logarithm of e.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Log10E() noexcept
  {
    return TNumber(0.434294481903251827651128918916605082);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns sqrt(e), the square root of e.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber RootE() noexcept
  {
    return TNumber(1.64872127070012814684865078781416357);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns Euler's constant.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber Euler() noexcept
  {
    return TNumber(0.577215664901532860606);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns sqrt(2).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber RootTwo() noexcept
  {
    return TNumber(1.41421356237309504880168872420969808);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns sqrt(3).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber RootThree() noexcept
  {
    return TNumber(1.73205080756887729352744634150587236);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns sqrt(5).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber RootFive() noexcept
  {
    return TNumber(2.23606797749978969640917366873127623);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns ln(2).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber LnTwo() noexcept
  {
    return TNumber(0.693147180559945309417232121458176568);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns ln(10).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber LnTen() noexcept
  {
    return TNumber(2.30258509299404568401799145468436421);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns ln(ln(2)).
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber LnLnTwo() noexcept
  {
    return TNumber(-0.3665129205816643);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 1/3.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber OneThird() noexcept
  {
    return TNumber(0.3333333333333333333333333333333333333333);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns 2/3.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber TwoThirds() noexcept
  {
    return TNumber(0.666666666666666666666666666666666666667);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns The golden ratio constant.
  template <IsArithmeticT TNumber>
  NO_DISCARD constexpr TNumber GoldenRatio() noexcept
  {
    return TNumber(1.61803398874989484820458683436563811);
  }

  /// @tparam TNumber An arithmetic type.
  /// @returns cos(1 / 2).
  template <typename TNumber>
  NO_DISCARD constexpr TNumber CosOneHalf()
  {
    return TNumber(0.877582561890372716130286068203503191);
  }
}
