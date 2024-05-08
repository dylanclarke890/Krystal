#include "Graphics/Texture2D.h"
#include "GL.h"

namespace Krys
{
  class GLTexture2D : public Texture2D
  {
  private:
    GLRendererId m_RendererId;
    const char *m_Path;
    uint32 m_Width, m_Height;
    GLenum m_InternalFormat, m_DataFormat;

  public:
    GLTexture2D(Texture2DSettings settings);
    GLTexture2D(const char *filepath);
    ~GLTexture2D();

    uint32 GetWidth() const override { return m_Width; }
    uint32 GetHeight() const override { return m_Height; }
    uint32 GetRendererId() const override { return m_RendererId; }

    void Bind(uint32 slot = 0) const override;
    void SetData(void *data, uint32 size) override;

    void GenerateMipmaps() override;

  private:
    static GLenum ToGLDataFormat(Texture2DFormat format);
    static GLenum ToGLInternalDataFormat(Texture2DFormat format);
  };
}