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

    void Bind(uint32 slot = 0) const override;
    void SetData(void *data, uint32 size) override;
    void GenerateMipmaps() override;

  private:
    void Load();
    static GLenum ToGLDataFormat(Texture2DFormat format);
    static GLenum ToGLInternalDataFormat(Texture2DFormat format);
  };
}