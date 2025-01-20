#pragma once

#include "Base/Types.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Gfx
{
  /// @brief A colour class with red, green, blue and alpha components.
  class Colour
  {
  public:
    /// @brief Default constructor, creates a black colour.
    constexpr Colour() : Colour(0.0f, 0.0f, 0.0f, 1.0f)
    {
    }

    /// @brief Create a new colour with the specified components.
    /// @param r Red component.
    /// @param g Green component.
    /// @param b Blue component.
    /// @param a Alpha component.
    explicit constexpr Colour(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a)
    {
    }

    /// @brief Create a new colour from another colour with a different alpha component.
    /// @param rgb Colour to copy the red, green and blue components from.
    /// @param a Alpha component.
    explicit constexpr Colour(const Colour &rgb, float a) : r(rgb.r), g(rgb.g), b(rgb.b), a(a)
    {
    }

    /// @brief Create a new colour with integer components.
    /// @param r Red.
    /// @param g Green.
    /// @param b Blue.
    /// @param a Alpha.
    explicit constexpr Colour(uint32 r, uint32 g, uint32 b, uint32 a = 255)
        : Colour(static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f,
                 static_cast<float>(b) / 255.0f, static_cast<float>(a) / 255.0f)
    {
    }

    /// @brief Create a new colour from a Vec3.
    /// @param vec Vec3 to copy the red, green and blue components from.
    /// @param a Alpha component.
    explicit constexpr Colour(const Vec3 &vec, float a = 1.0f) : Colour(vec.x, vec.y, vec.z, a)
    {
    }

    /// @brief Create a new colour from a Vec4.
    /// @param vec Vec4 to copy the red, green, blue and alpha components from.
    explicit constexpr Colour(const Vec4 &vec) : Colour(vec.x, vec.y, vec.z, vec.w)
    {
    }

    /// @brief Multiply each component of this colour by a scalar value.
    /// @param scale Scalar value.
    constexpr Colour &operator*=(float scale)
    {
      r *= scale;
      g *= scale;
      b *= scale;
      a *= scale;

      return *this;
    }

    /// @brief Create a new colour which is this colour multiplied by a scalar value.
    /// @param scale Scalar value.
    constexpr Colour operator*(float scale) const
    {
      return Colour(*this) *= scale;
    }

    /// @brief Add a colour to this colour.
    /// @param colour Colour to add.
    constexpr Colour &operator+=(const Colour &colour)
    {
      r += colour.r;
      g += colour.g;
      b += colour.b;
      a += colour.a;

      return *this;
    }

    /// @brief Create a new colour which is this colour added to another colour.
    /// @param colour Colour to add.
    constexpr Colour operator+(const Colour &colour) const
    {
      return Colour(*this) += colour;
    }

    /// @brief Subtract a colour from this colour.
    /// @param colour Colour to subtract.
    constexpr Colour &operator-=(const Colour &colour)
    {
      r -= colour.r;
      g -= colour.g;
      b -= colour.b;
      a -= colour.a;

      return *this;
    }

    /// @brief Create a new colour which is this colour subtracted from another colour.
    /// @param colour Colour to subtract.
    constexpr Colour operator-(const Colour &colour) const
    {
      return Colour(*this) -= colour;
    }

    /// @brief Multiply each component of this colour by the corresponding component of another colour.
    /// @param colour Colour to multiply with.
    constexpr Colour &operator*=(const Colour &colour)
    {
      r *= colour.r;
      g *= colour.g;
      b *= colour.b;
      a *= colour.a;

      return *this;
    }

    /// @brief Create a new colour which is this colour multiplied by another colour.
    /// @param colour Colour to multiply with.
    constexpr Colour operator*(const Colour &colour) const
    {
      return Colour {*this} *= colour;
    }

    /// @brief Divide each component of this colour by the corresponding component of another colour.
    /// @param colour Colour to divide by.
    bool operator==(const Colour &other) const
    {
      return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    /// @brief Check if this colour is not equal to another colour.
    /// @param other Colour to compare with.
    bool operator!=(const Colour &other) const
    {
      return !(other == *this);
    }

    /// @brief Linear interpolate between this and another colour.
    /// @param other Colour to interpolate to.
    /// @param amount Interpolation amount, must be in range [0.0, 1.0].
    constexpr void Lerp(const Colour &other, float amount)
    {
      *this *= (1.0f - amount);
      *this += (other * amount);
    }

    /// @brief Linear interpolate between two colours.
    /// @param start Colour to start from.
    /// @param end Colour to lerp towards.
    /// @param amount Interpolation amount, must be in range [0.0, 1.0].
    constexpr static Colour Lerp(const Colour &start, const Colour &end, float amount)
    {
      auto tmp = start;
      tmp.Lerp(end, amount);
      return tmp;
    }

    /// @brief Red component.
    float r;

    /// @brief Green component.
    float g;

    /// @brief Blue component.
    float b;

    /// @brief Alpha component.
    float a;
  };
}