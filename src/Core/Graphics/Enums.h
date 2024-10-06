#pragma once

#include "Core.h"

namespace Krys
{
  enum class CullMode : ushort
  {
    None = 0,
    Front,
    Back,
    FrontAndBack
  };

  enum class WindingOrder : ushort
  {
    None = 0,
    Clockwise,
    CounterClockwise
  };

  enum class DepthTestFunc : ushort
  {
    None = 0,
    Never,
    Always,
    Less,
    EqualOrLess,
    EqualOrGreater,
    Greater
  };

  enum class StencilTestFunc : ushort
  {
    None = 0,
    Never,
    Always,
    Less,
    EqualOrLess,
    Equal,
    NotEqual,
    EqualOrGreater,
    Greater
  };

  enum class StencilOperation : ushort
  {
    None = 0,
    Keep,
    Zero,
    Replace,
    Increment,
    IncrementWithWrap,
    Decrement,
    DecrementWithWrap,
    Invert
  };

  enum class BlendFactor : ushort
  {
    None = 0,
    Zero,
    One,
    SourceColor,
    OneMinusSourceColor,
    DestinationColor,
    OneMinusDestinationColor,
    SourceAlpha,
    OneMinusSourceAlpha,
    DestinationAlpha,
    OneMinusDestinationAlpha,
    ConstantColor,
    OneMinusConstantColor,
    ConstantAlpha,
    OneMinusConstantAlpha
  };

  enum class BlendEquation : ushort
  {
    None = 0,
    Add,
    Subtract,
    ReverseSubtract,
    Min,
    Max
  };

  enum class RenderBuffer : ushort
  {
    None = 0,
    Color = 1,
    Depth = 2,
    Stencil = 4,
    All = Color | Depth | Stencil
  };

  inline constexpr RenderBuffer operator|(RenderBuffer a, RenderBuffer b)
  {
    return static_cast<RenderBuffer>(static_cast<ushort>(a) | static_cast<ushort>(b));
  }

  inline constexpr bool operator&(RenderBuffer a, RenderBuffer b)
  {
    return (static_cast<ushort>(a) & static_cast<ushort>(b));
  }

  enum class DrawMode : ushort
  {
    Points,
    Lines,
    LineLoop,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan
  };

  enum class FramebufferBindType
  {
    None = 0,
    Read,
    Draw,
    ReadAndDraw
  };

  enum class LightingModel
  {
    None = 0,
    Phong,
    BlinnPhong
  };
}