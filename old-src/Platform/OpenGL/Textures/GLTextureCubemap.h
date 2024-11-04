#pragma once

#include "Graphics/Textures/TextureCubemap.h"
#include "Maths/Vector.h"
#include "OpenGL/Textures/Texture.h"

#include <array>
#include <string>

namespace Krys::OpenGL
{
  using namespace Krys::Graphics;

  class GLTextureCubemap : public TextureCubemap
  {
  public:
    GLTextureCubemap(std::array<string, 6> faces, TextureInternalFormat internalFormat = TextureInternalFormat::Auto);
    GLTextureCubemap(uint width, uint height, TextureInternalFormat internalFormat);
    ~GLTextureCubemap() override;

    void Bind(uint32 slot = 0) const noexcept override;
    void Unbind() const noexcept override;

    void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept override;
    void SetMagnifyMode(TextureMagnifyMode mode) noexcept override;
    void SetMinifyMode(TextureMinifyMode mode) noexcept override;

    void SetTextureWrapS(TextureWrapMode mode) noexcept override;
    void SetTextureWrapT(TextureWrapMode mode) noexcept override;
    void SetTextureWrapR(TextureWrapMode mode) noexcept override;
    void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t, TextureWrapMode r) noexcept override;

    void SetBorderColor(const Maths::Vec4 &color) noexcept override;

  private:
    void Load();
  };
}