#pragma once

#include <windows.h>

#include "Core.h"
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
    void SetClearColor(Vec4 &color) override;
    void SetClearColor(Vec4 color) override;
    void SetViewport(int width, int height) override;

    void SetFaceCulling(CullMode mode) override;
    void SetWindingOrder(WindingOrder mode) override;

    void SetDepthTestingEnabled(bool enable) override;
    void SetDepthTestFunc(DepthTestFunc func) override;
    // NOTE: This only has an effect if depth testing is enabled.
    void SetDepthBufferWritingEnabled(bool enable) override;
    void SetClearDepth(float value) override;
    void SetDepthRange(float dNear, float dFar) override;
    void SetDepthClampingEnabled(bool enable) override;

    void SetStencilTestFunc(StencilTestFunc func, uint8 ref, uint8 mask) override;
    void SetStencilOperation(StencilOperation fail, StencilOperation zFail, StencilOperation zPass) override;
    void SetStencilTestingEnabled(bool enable) override;
    // NOTE: This only has an effect if stencil testing is enabled.
    void SetStencilBufferWritingEnabled(bool enable) override;
    // Similar to `SetStencilBufferWritingEnabled`, but takes a custom mask to be
    // ANDed with the stencil value to be written
    void SetStencilBufferBitMask(uint8 mask) override;

    void SetWireframeModeEnabled(bool enable) override;

#pragma endregion State Settings

#pragma region Graphics Objects
    Ref<IndexBuffer> CreateIndexBuffer(uint32 count) override;
    Ref<IndexBuffer> CreateIndexBuffer(const uint32 *indices, uint32 count) override;

    Ref<VertexBuffer> CreateVertexBuffer(uint32 size) override;
    Ref<VertexBuffer> CreateVertexBuffer(float *vertices, uint32 size) override;

    Ref<VertexArray> CreateVertexArray() override;

    Ref<Shader> CreateShader() override;

    Ref<Texture2D> CreateTexture2D(const char *filepath) override;
    Ref<SubTexture2D> CreateSubTexture2D(Ref<Texture2D> texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize) override;
#pragma endregion Graphics Objects
  };
}