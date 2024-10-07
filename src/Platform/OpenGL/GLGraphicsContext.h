#pragma once

#include "Core.h"
#include "GL.h"
#include "Graphics/GraphicsContext.h"
#include "Misc/Lazy.h"

#include <windows.h>

namespace Krys
{
  class GLGraphicsContext : public GraphicsContext
  {
  private:
    HWND _window;
    HINSTANCE _instance;
    HDC _deviceContext;
    HGLRC _context;
    Lazy<GraphicsCapabilities> _capabilities;

  public:
    GLGraphicsContext(HDC deviceContext, HWND window, HINSTANCE instance);
    ~GLGraphicsContext() override;

    void Init() noexcept override;

    const GraphicsCapabilities &QueryCapabilities() noexcept override;

#pragma region State Settings
    void BindScreenFramebuffer(FramebufferBindType bindType) noexcept override;

    void SetClearColor(const Vec4 &color) noexcept override;
    void Clear(RenderBuffer flags) noexcept override;
    void SetViewport(int width, int height) noexcept override;

    void SetMultisamplingEnabled(bool enable) noexcept override;
    void SetGammaCorrectionEnabled(bool enable) noexcept override;

    void SetFaceCullingEnabled(bool enable) noexcept override;
    void SetFaceCulling(CullMode mode) noexcept override;
    void SetWindingOrder(WindingOrder mode) noexcept override;

    void SetDepthTestingEnabled(bool enable) noexcept override;
    void SetDepthTestFunc(DepthTestFunc func) noexcept override;
    // NOTE: This only has an effect if depth testing is enabled.
    void SetDepthBufferWritingEnabled(bool enable) noexcept override;
    void SetClearDepth(float value) noexcept override;
    void SetDepthRange(float dNear, float dFar) noexcept override;
    void SetDepthClampingEnabled(bool enable) noexcept override;

    void SetStencilTestFunc(StencilTestFunc func, uint8 ref, uint8 mask) noexcept override;
    void SetStencilOperation(StencilOperation fail, StencilOperation zFail, StencilOperation zPass) noexcept override;
    void SetStencilTestingEnabled(bool enable) noexcept override;
    // NOTE: This only has an effect if stencil testing is enabled.
    void SetStencilBufferWritingEnabled(bool enable) noexcept override;
    // Similar to `SetStencilBufferWritingEnabled`, but takes a custom mask to be
    // ANDed with the stencil value to be written
    void SetStencilBufferBitMask(uint8 mask) noexcept override;

    void SetBlendingEnabled(bool enable) noexcept override;
    void SetBlendFunc(BlendFactor srcFactor, BlendFactor dstFactor) noexcept override;
    void SetBlendFunc(BlendFactor rgbSrcFactor, BlendFactor rgbDstFactor, BlendFactor alphaSrcFactor, BlendFactor alphaDstFactor) noexcept override;
    void SetBlendEquation(BlendEquation equation) noexcept override;
    void SetBlendColor(Vec4 color) noexcept override;

    void SetWireframeModeEnabled(bool enable) noexcept override;
#pragma endregion State Settings

#pragma region Graphics Objects
    Ref<IndexBuffer> CreateIndexBuffer(uint32 count) noexcept override;
    Ref<IndexBuffer> CreateIndexBuffer(const uint32 *indices, uint32 count) noexcept override;

    Ref<VertexBuffer> CreateVertexBuffer(uint32 size) noexcept override;
    Ref<VertexBuffer> CreateVertexBuffer(float *vertices, uint32 size) noexcept override;

    Ref<InstanceArrayBuffer> CreateInstanceArrayBuffer(uint32 size) noexcept override;
    Ref<InstanceArrayBuffer> CreateInstanceArrayBuffer(void *vertices, uint32 size) noexcept override;

    Ref<UniformBuffer> CreateUniformBuffer(uint32 size, uint32 binding) noexcept override;
    Ref<UniformBuffer> CreateUniformBuffer(uint32 binding, UniformBufferLayout layout) noexcept override;

    Ref<VertexArray> CreateVertexArray() noexcept override;

    Ref<Shader> CreateShader() noexcept override;
    Ref<Shader> CreateShader(const stringview &vertexFilepath, const stringview &fragmentFilepath) override;
    Ref<Shader> CreateShader(const stringview &vertexFilepath, const stringview &fragmentFilepath, const stringview &geoFilepath) override;

    Ref<Texture2D> CreateTexture2D(const string &filepath) noexcept override;
    Ref<SubTexture2D> CreateSubTexture2D(Ref<Texture2D> texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize) noexcept override;
    Ref<TextureCubemap> CreateTextureCubemap(std::array<string, 6> paths) noexcept override;
    Ref<TextureCubemap> CreateTextureCubemap(uint width, uint height, TextureInternalFormat format) noexcept override;

    Ref<Framebuffer> CreateFramebuffer(uint32 width, uint32 height, uint32 samples) noexcept override;
#pragma endregion Graphics Objects

#pragma region Primitive Drawing
    void DrawVertices(size_t count, PrimitiveType mode = PrimitiveType::Triangles) noexcept override;
    void DrawVerticesInstanced(size_t instanceCount, size_t vertexCount, PrimitiveType mode = PrimitiveType::Triangles) noexcept override;

    void DrawIndices(size_t count, PrimitiveType mode = PrimitiveType::Triangles) noexcept override;
    void DrawIndicesInstanced(size_t instanceCount, size_t indexCount, PrimitiveType mode = PrimitiveType::Triangles) noexcept override;
#pragma endregion Primitive Drawing

  private:
    GraphicsCapabilities LoadGraphicsCapabilities() noexcept;
  };
}