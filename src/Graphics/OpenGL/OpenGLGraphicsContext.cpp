#include "OpenGLGraphicsContext.h"
#pragma warning(push)
#pragma warning(disable : 4005)
#include <glad.h>
#include <stdio.h>
#pragma warning(pop)

namespace Krys
{
  OpenGLGraphicsContext::~OpenGLGraphicsContext()
  {
    wglDeleteContext(openGLContext);
  }

  void OpenGLGraphicsContext::Init()
  {
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
        PFD_TYPE_RGBA,                                              // The kind of framebuffer. RGBA or palette.
        32,                                                         // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24, // Number of bits for the depthbuffer
        8,  // Number of bits for the stencilbuffer
        0,  // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0};

    // TODO: static BAD!
    KRYS_ASSERT(dc, "Device context was not valid");

    int pixelFormat = ChoosePixelFormat(dc, &pfd);
    KRYS_ASSERT(pixelFormat != 0, "Failed to choose a pixel format");

    BOOL setPixelFormatSuccess = SetPixelFormat(dc, pixelFormat, &pfd);
    KRYS_ASSERT(setPixelFormatSuccess, "Failed to set the pixel format");

    openGLContext = wglCreateContext(dc);
    KRYS_ASSERT(openGLContext, "Failed to create OpenGL context");

    BOOL makeCurrentSuccess = wglMakeCurrent(dc, openGLContext);
    KRYS_ASSERT(makeCurrentSuccess, "Failed to make OpenGL context current");

    if (!gladLoadGL())
    {
      KRYS_ASSERT(false, "Failed to initialize OpenGL context");
      // TODO: exit early
    }

    KRYS_INFO("OPENGL - initialised:");

    int minorVersion, majorVersion;
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    KRYS_INFO("- Version: %d.%d", majorVersion, minorVersion);

    KRYS_INFO("- Vendor: %s", glGetString(GL_VENDOR));
    KRYS_INFO("- Renderer: %s", glGetString(GL_RENDERER));
    KRYS_INFO("- Primary GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
  }

  void OpenGLGraphicsContext::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  // TODO: pass a vector of floats instead
  void OpenGLGraphicsContext::SetClearColor(float x, float y, float z, float a)
  {
    glClearColor(x, y, z, a);
  }

  void OpenGLGraphicsContext::OnResize(int width, int height)
  {
    glViewport(0, 0, width, height);
  }

#if 0
  uint OpenGLGraphicsContext::CreateTextureFromBMP(const char *imagePath)
  {
    FILE *file;
    int fileResult = fopen_s(&file, imagePath, "rb");

    // TODO: assert or return early?
    KRYS_ASSERT(!fileResult, "Image could not be opened: %d.", fileResult);

    uchar header[54]; // Each BMP file begins by a 54-bytes header
    size_t headerBytesRead = fread(header, 1, 54, file);

    // TODO: assert or return early?
    KRYS_ASSERT(headerBytesRead == 54, "Not a valid BMP file.");
    KRYS_ASSERT(header[0] == 'B' && header[1] == 'M', "Not a valid BMP file.");

    uint dataPos = *(int *)&(header[0x0A]);
    uint imageSize = *(int *)&(header[0x22]);
    uint width = *(int *)&(header[0x12]);
    uint height = *(int *)&(header[0x16]);

    // Guess missing info for incorrect formats
    if (imageSize == 0)
      imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)
      dataPos = 54;

    // Actual RGB data
    uchar *data = new uchar[imageSize];

    fread(data, 1, imageSize, file);
    fclose(file);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
  }
#endif
}