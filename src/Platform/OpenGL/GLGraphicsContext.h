#pragma once

#include <windows.h>

#include "Krystal.h"
#include "GL.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{
  class GLGraphicsContext : public GraphicsContext
  {
  private:
    HWND hWnd;
    HINSTANCE instance;
    HDC dc;
    HGLRC openGLContext;

  public:
    GLGraphicsContext(HDC deviceContext, HWND window, HINSTANCE instance);
    ~GLGraphicsContext() override;

    void Init() override;
    void Clear(ClearFlags flags = ClearFlags::Color) override;

#pragma region State Settings
    void SetClearColor(float x, float y, float z, float a) override;
    void SetViewport(int width, int height) override;

    void SetFaceCulling(CullMode mode) override;
    void SetWindingOrder(WindingOrder mode) override;

    void SetDepthBufferEnabled(bool enable) override;
    void SetClearDepth(float value) override;
    void SetDepthTestingEnabled(bool enable) override;
    void SetDepthRange(float dNear, float dFar) override;
    void SetDepthClampingEnabled(bool enable) override;
    void SetDepthTestFunc(DepthTestFunc func) override;
#pragma endregion State Settings

#pragma region Graphics Objects
    Ref<IndexBuffer> CreateIndexBuffer(const uint32 *indices, uint32 count) override;
    Ref<IndexBuffer> CreateIndexBuffer(const ushort *indices, uint32 count) override;
    Ref<VertexBuffer> CreateVertexBuffer(uint32 size) override;
    Ref<VertexBuffer> CreateVertexBuffer(float *vertices, uint32 size) override;
    Ref<VertexArray> CreateVertexArray() override;
    Ref<Shader> CreateShader() override;
#pragma endregion Graphics Objects
  };
}