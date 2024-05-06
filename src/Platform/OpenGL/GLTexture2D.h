#include "Graphics/Texture2D.h"
#include "GL.h"

namespace Krys
{
  class OpenGLTexture2D : public Texture2D
  {
  private:
    uint32_t m_RendererId;
    char *m_Path;
    uint32_t m_Width, m_Height;
    GLenum m_InternalFormat, m_DataFormat;

  public:
    OpenGLTexture2D(uint32 width, uint32 height);
    OpenGLTexture2D(char *path);
    virtual ~OpenGLTexture2D();

    virtual uint32_t GetWidth() const override { return m_Width; }
    virtual uint32_t GetHeight() const override { return m_Height; }

    virtual void Bind(uint32_t slot = 0) const override;

    virtual void SetData(void *data, uint32 size) override;
  };
}