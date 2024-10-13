#pragma once

#include "Types.h"
#include "Maths/Vector.h"
#include "Graphics/Textures/Texture2D.h"

namespace Krys::Graphics
{
  using namespace Krys::Maths;

  class SubTexture2D
  {
  private:
    Ref<Texture2D> _texture;
    Vec2 _textureCoords[4];

  public:
    SubTexture2D(Ref<Texture2D> &texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize)
        : _texture(texture)
    {
      float sheetWidth = static_cast<float>(texture->GetWidth()), sheetHeight = static_cast<float>(texture->GetHeight());
      Vec2 min = {(coords.x * cellSize.x) / sheetWidth,
                  (coords.y * cellSize.y) / sheetHeight};
      Vec2 max = {((coords.x + spriteSize.x) * cellSize.x) / sheetWidth,
                  ((coords.y + spriteSize.y) * cellSize.y) / sheetHeight};

      _textureCoords[0] = {min.x, min.y};
      _textureCoords[1] = {max.x, min.y};
      _textureCoords[2] = {max.x, max.y};
      _textureCoords[3] = {min.x, max.y};
    }

    const Ref<Texture2D> GetTexture() const { return _texture; }
    const Vec2 *GetTextureCoords() const { return _textureCoords; }
  };
}