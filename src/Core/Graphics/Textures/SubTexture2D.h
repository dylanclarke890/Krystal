#pragma once

#include "Core.h"

#include "Maths/Maths.h"
#include "Graphics/Textures/Texture2D.h"

namespace Krys
{
  class SubTexture2D
  {
  private:
    Ref<Texture2D> m_Texture;
    Vec2 m_TextureCoords[4];

  public:
    SubTexture2D(Ref<Texture2D> &texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize)
        : m_Texture(texture)
    {
      float sheetWidth = (float)texture->GetWidth(), sheetHeight = (float)texture->GetHeight();
      Vec2 min = {(coords.x * cellSize.x) / sheetWidth,
                  (coords.y * cellSize.y) / sheetHeight};
      Vec2 max = {((coords.x + spriteSize.x) * cellSize.x) / sheetWidth,
                  ((coords.y + spriteSize.y) * cellSize.y) / sheetHeight};

      m_TextureCoords[0] = {min.x, min.y};
      m_TextureCoords[1] = {max.x, min.y};
      m_TextureCoords[2] = {max.x, max.y};
      m_TextureCoords[3] = {min.x, max.y};
    }

    const Ref<Texture2D> GetTexture() const { return m_Texture; }
    const Vec2 *GetTextureCoords() const { return m_TextureCoords; }
  };
}