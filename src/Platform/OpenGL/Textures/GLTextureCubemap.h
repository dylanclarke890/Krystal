#pragma once

#include <vector>
#include <string>

#include "Graphics/Textures/TextureCubemap.h"
#include "Texture.h"

namespace Krys
{
  class GLTextureCubemap : public TextureCubemap
  {
  public:
    GLTextureCubemap(std::vector<std::string> faces);
    ~GLTextureCubemap() override;

    void Bind(uint32 slot = 0) const noexcept override;

    void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept override;
    void SetMagnifyMode(TextureMagnifyMode mode) noexcept override;
    void SetMinifyMode(TextureMinifyMode mode) noexcept override;

    void SetTextureWrapS(TextureWrapMode mode) noexcept override;
    void SetTextureWrapT(TextureWrapMode mode) noexcept override;
    void SetTextureWrapR(TextureWrapMode mode) noexcept override;
    void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t, TextureWrapMode r) noexcept override;

  private:
    void Load();
  };
}