#pragma once

#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/Buffer.hpp"
#include "Graphics/Colour.hpp"
#include "Graphics/DeviceCapabilities.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"
#include "Graphics/Program.hpp"
#include "Graphics/Shader.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys
{
  class Window;
}

namespace Krys::Gfx
{
  enum class ClearBuffer : uint8
  {
    Colour = 1 << 0,
    Depth = 1 << 1,
    Stencil = 1 << 2
  };

  ENUM_CLASS_BITWISE_OPERATORS(ClearBuffer, uint8);

  class GraphicsContext
  {
  public:
    virtual ~GraphicsContext() noexcept;

    virtual void Init() noexcept = 0;

#pragma region Shaders

    /// @brief Create a new shader.
    /// @param stage The stage of the shader.
    /// @param source The source code of the shader.
    /// @return A handle to the shader.
    ShaderHandle CreateShader(ShaderStage stage, const string &source) noexcept;

    /// @brief Get a shader from a handle.
    /// @param handle The handle of the shader.
    /// @return The shader if found, nullptr otherwise.
    Shader *GetShader(ShaderHandle handle) noexcept;

    /// @brief Destroy a shader.
    /// @param handle The handle of the shader to destroy.
    /// @return True if the shader was found, false otherwise.
    bool DestroyShader(ShaderHandle handle) noexcept;

#pragma endregion Shaders

#pragma region Programs

    /// @brief Create a new program.
    /// @param vertexShader The vertex shader to use.
    /// @param fragmentHandle The fragment shader to use.
    /// @return A handle to the program.
    /// @note The program will be empty, you will need to add and link shaders to it.
    ProgramHandle CreateProgram(ShaderHandle vertexShader, ShaderHandle fragmentHandle) noexcept;

    /// @brief Get a program from a handle.
    /// @param handle The handle of the program.
    /// @return The program if found, nullptr otherwise.
    Program *GetProgram(ProgramHandle handle) noexcept;

    /// @brief Destroys a program.
    /// @param handle The handle of the program to destroy.
    /// @return True if the program was found, false otherwise.
    bool DestroyProgram(ProgramHandle handle) noexcept;

#pragma endregion Programs

#pragma region Vertex Buffers

    /// @brief Create a new vertex buffer.
    /// @param size The size of the buffer.
    /// @return A handle to the buffer.
    VertexBufferHandle CreateVertexBuffer(uint32 size) noexcept;

    /// @brief Get a vertex buffer from a handle.
    /// @param handle The handle of the buffer.
    /// @return The buffer if found, nullptr otherwise.
    VertexBuffer *GetVertexBuffer(VertexBufferHandle handle) noexcept;

    /// @brief Destroy a vertex buffer.
    /// @param handle The handle of the buffer to destroy.
    /// @return True if the buffer was found, false otherwise.
    bool DestroyVertexBuffer(VertexBufferHandle handle) noexcept;

#pragma endregion Vertex Buffers

#pragma region Index Buffers

    /// @brief Create a new index buffer.
    /// @param size The size of the buffer.
    /// @return A handle to the buffer.
    IndexBufferHandle CreateIndexBuffer(uint32 size) noexcept;

    /// @brief Get an index buffer from a handle.
    /// @param handle The handle of the buffer.
    /// @return The buffer if found, nullptr otherwise.
    IndexBuffer *GetIndexBuffer(IndexBufferHandle handle) noexcept;

    /// @brief Destroy an index buffer.
    /// @param handle The handle of the buffer to destroy.
    /// @return True if the buffer was found, false otherwise.
    bool DestroyIndexBuffer(IndexBufferHandle handle) noexcept;

#pragma endregion Index Buffers

#pragma region Uniform Buffers

    /// @brief Create a new uniform buffer.
    /// @param size The size of the buffer.
    /// @return A handle to the buffer.
    UniformBufferHandle CreateUniformBuffer(uint32 size) noexcept;

    /// @brief Get a uniform buffer from a handle.
    /// @param handle The handle of the buffer.
    /// @return The created uniform buffer.
    UniformBuffer *GetUniformBuffer(UniformBufferHandle handle) noexcept;

    /// @brief Destroy a uniform buffer.
    /// @param handle The handle of the buffer to destroy.
    /// @return True if the buffer was found, false otherwise.
    bool DestroyUniformBuffer(UniformBufferHandle handle) noexcept;

#pragma endregion Uniform Buffers

#pragma region Shader Storage Buffers

    /// @brief Create a new shader storage buffer.
    /// @param size The size of the buffer.
    /// @return A handle to the buffer.
    ShaderStorageBufferHandle CreateShaderStorageBuffer(uint32 size) noexcept;

    /// @brief Get a shader storage buffer from a handle.
    /// @param handle The handle of the buffer.
    /// @return The buffer if found, nullptr otherwise.
    ShaderStorageBuffer *GetShaderStorageBuffer(ShaderStorageBufferHandle handle) noexcept;

    /// @brief Destroy a shader storage buffer.
    /// @param handle The handle of the buffer to destroy.
    /// @return True if the buffer was found, false otherwise.
    bool DestroyShaderStorageBuffer(ShaderStorageBufferHandle handle) noexcept;

#pragma endregion Shader Storage Buffers

#pragma region Viewport

    /// @brief Set the viewport of the graphics context.
    /// @param width Width of the viewport.
    /// @param height Height of the viewport.
    void SetViewport(uint32 width, uint32 height) noexcept;

    /// @brief Set the viewport of the graphics context.
    /// @param x X position of the viewport.
    /// @param y Y position of the viewport.
    /// @param width Width of the viewport.
    /// @param height Height of the viewport.
    void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) noexcept;

    /// @brief Set the viewport of the graphics context.
    /// @param window The window to set the viewport to.
    void SetViewport(const Window &window) noexcept;

    /// @brief Set the viewport of the graphics context.
    /// @param viewport The viewport to set.
    virtual void SetViewport(const Vec4ui &viewport) noexcept = 0;

#pragma endregion Viewport

    /// @brief Draw the currently bound vertex buffer.
    /// @param type The type of primitive to draw.
    /// @param count The number of vertices to draw.
    virtual void DrawArrays(PrimitiveType type, uint32 count) noexcept = 0;

    /// @brief Draw the currently bound index buffer.
    /// @param type The type of primitive to draw.
    /// @param count The number of indices to draw.
    virtual void DrawElements(PrimitiveType type, uint32 count) noexcept = 0;

    /// @brief Set the clear colour of the graphics context.
    /// @param colour The colour to set the clear colour to.
    virtual void SetClearColour(const Colour &colour) noexcept = 0;

    /// @brief Clear the currently bound framebuffer.
    /// @param flags The buffers to clear.
    virtual void Clear(ClearBuffer flags) noexcept = 0;

    /// @brief Get the device capabilities.
    NO_DISCARD const DeviceCapabilities &GetDeviceCapabilities() const noexcept;

  protected:
    /// @brief Implementation-specific shader creation.
    /// @param handle The handle of the shader.
    /// @param stage The stage of the shader.
    /// @param source The source code of the shader.
    /// @return The created shader.
    virtual Unique<Shader> CreateShaderImpl(ShaderHandle handle, ShaderStage stage,
                                            const string &source) noexcept = 0;

    /// @brief Implementation-specific program creation.
    /// @param handle The handle of the program.
    /// @param vertexShader The vertex shader to use.
    /// @param fragmentShader The fragment shader to use.
    /// @return The created program.
    virtual Unique<Program> CreateProgramImpl(ProgramHandle handle, ShaderHandle vertexShader,
                                              ShaderHandle fragmentShader) noexcept = 0;

    /// @brief Implementation-specific vertex buffer creation.
    /// @param handle The handle of the buffer.
    /// @param size The size of the buffer.
    /// @return The created vertex buffer.
    virtual Unique<VertexBuffer> CreateVertexBufferImpl(VertexBufferHandle handle, uint32 size) noexcept = 0;

    /// @brief Implementation-specific index buffer creation.
    /// @param handle The handle of the buffer.
    /// @param size The size of the buffer.
    /// @return The created index buffer.
    virtual Unique<IndexBuffer> CreateIndexBufferImpl(IndexBufferHandle handle, uint32 size) noexcept = 0;

    /// @brief Implementation-specific uniform buffer creation.
    /// @param handle The handle of the buffer.
    /// @param size The size of the buffer.
    /// @return The created uniform buffer.
    virtual Unique<UniformBuffer> CreateUniformBufferImpl(UniformBufferHandle handle,
                                                          uint32 size) noexcept = 0;

    /// @brief Implementation-specific shader storage buffer creation.
    /// @param handle The handle of the buffer.
    /// @param size The size of the buffer.
    /// @return The created shader storage buffer.
    virtual Unique<ShaderStorageBuffer> CreateShaderStorageBufferImpl(ShaderStorageBufferHandle handle,
                                                                      uint32 size) noexcept = 0;

  protected:
    ShaderHandleMap<Unique<Shader>> _shaders {};
    ShaderHandleManager _shaderHandles {};

    ProgramHandleMap<Unique<Program>> _programs {};
    ProgramHandleManager _programHandles {};

    VertexBufferHandleMap<Unique<VertexBuffer>> _vertexBuffers {};
    VertexBufferHandleManager _vertexBufferHandles {};

    IndexBufferHandleMap<Unique<IndexBuffer>> _indexBuffers {};
    IndexBufferHandleManager _indexBufferHandles {};

    UniformBufferHandleMap<Unique<UniformBuffer>> _uniformBuffers {};
    UniformBufferHandleManager _uniformBufferHandles {};

    ShaderStorageBufferHandleMap<Unique<ShaderStorageBuffer>> _shaderStorageBuffers {};
    ShaderStorageBufferHandleManager _shaderStorageBufferHandles {};

    DeviceCapabilities _deviceCapabilities {};
    Colour _clearColour {0.0f, 0.0f, 0.0f, 1.0f};
  };
}