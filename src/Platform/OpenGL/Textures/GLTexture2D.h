#pragma once

#include "Graphics/Textures/Texture2D.h"
#include "Texture.h"

namespace Krys
{
  class GLTexture2D : public Texture2D
  {
  public:
    GLTexture2D(const string &filepath);
    GLTexture2D(const string &filepath, TextureType type, TextureInternalFormat internalFormat = TextureInternalFormat::Auto);
    GLTexture2D(int width, int height, int samples, TextureInternalFormat internalFormat = TextureInternalFormat::RGBA);
    ~GLTexture2D();

    void Bind(uint32 slot = 0) const noexcept override;

    void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept override;
    void SetMagnifyMode(TextureMagnifyMode mode) noexcept override;
    void SetMinifyMode(TextureMinifyMode mode) noexcept override;

    void SetTextureWrapS(TextureWrapMode mode) noexcept override;
    void SetTextureWrapT(TextureWrapMode mode) noexcept override;
    void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t) noexcept override;

    void SetBorderColor(const Vec4 &color) noexcept override;


    void GenerateMipmaps(TextureMinifyMode mode) noexcept override;

  private:
    void Load();
  };
}