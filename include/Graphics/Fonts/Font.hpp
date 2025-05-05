#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "MTL/Vectors/Vec2.hpp"

namespace Krys::Gfx
{
  struct Glyph
  {
    TextureHandle Texture;
    Vec2i Size;
    Vec2i Bearing;
    int32 Advance;
    float OffsetX;
    float OffsetY;

  };

  class FontManager;

  class Font
  {
    friend class FontManager;
  public:
    Font(const string &path, FontHandle handle) noexcept : _path(path), _handle(handle)
    {
    }

    virtual ~Font() noexcept = default;

    NO_DISCARD const string &GetPath() const noexcept
    {
      return _path;
    }

    NO_DISCARD FontHandle GetHandle() const noexcept
    {
      return _handle;
    }

  private:
    string _path;
    FontHandle _handle;
    Map<string, Glyph> _glyphs;
  };
}