#pragma once

namespace Krys
{
  class GraphicsContext
  {
  public:
    virtual ~GraphicsContext() = default;
    virtual void Init() = 0;
    virtual void Clear() = 0;
    virtual void SetClearColor(float x, float y, float z, float a) = 0;
    virtual void OnResize(int width, int height) = 0;

    // virtual Texture CreateTexture() = 0;
    // virtual Shader CreateShader() = 0;
  };
}