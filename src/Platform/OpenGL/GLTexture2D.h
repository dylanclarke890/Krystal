#include "Graphics/Texture2D.h"
#include "GL.h"

namespace Krys
{
  class GLTexture2D : public Texture2D
  {
  private:
    GLenum InternalFormat, DataFormat;

  public:
    GLTexture2D(const char *filepath);
    GLTexture2D(TextureType type, const char *filepath);
    ~GLTexture2D();

    void Bind(uint32 slot = 0) const noexcept override;
    void SetData(void *data, uint32 size) noexcept override;

    void SetFilterModes(TextureMinifyMode min, TextureMagnifyMode mag) noexcept override;
    void SetMagnifyMode(TextureMagnifyMode mode) noexcept override;
    void SetMinifyMode(TextureMinifyMode mode) noexcept override;

    void SetTextureWrapS(TextureWrapMode mode) noexcept override;
    void SetTextureWrapT(TextureWrapMode mode) noexcept override;
    void SetTextureWrapModes(TextureWrapMode s, TextureWrapMode t) noexcept override;

    void GenerateMipmaps(TextureMinifyMode mode) noexcept override;

  private:
    void Load();
    static GLenum ToGLDataFormat(Texture2DFormat format);
    static GLenum ToGLInternalDataFormat(Texture2DFormat format);
  };
}