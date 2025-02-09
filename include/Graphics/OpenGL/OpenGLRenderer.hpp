#pragma once

#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Materials/PhongMaterial.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/RenderContext.hpp"
#include "Graphics/Renderer.hpp"
#include "IO/Logger.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  class OpenGLRenderer : public Renderer
  {
  public:
    OpenGLRenderer(RenderContext context) noexcept;

    ~OpenGLRenderer() noexcept override = default;
    NO_COPY_MOVE(OpenGLRenderer);

    void Init() noexcept override;

  protected:
    void BeforeRender() noexcept override;
    void Render(Node *node, const Transform &parentTransform, Camera &camera) noexcept override;

  private:
    ShaderStorageBufferHandle _phongMaterialBufferHandle {}, _textureTableHandle {}, _lightBufferHandle {};
    Ptr<ShaderStorageBuffer> _phongMaterialBuffer {nullptr}, _textureTable {nullptr}, _lightBuffer {nullptr};

    template <typename T>
    void SetUniform(GLuint program, const string &name, const T &value) noexcept
    {
      auto location = ::glGetUniformLocation(program, name.c_str());
      if (location == -1)
      {
        Logger::Error("Uniform '{}' not found in program.", name);
        return;
      }

      if constexpr (std::is_same_v<T, bool>)
        ::glProgramUniform1i(program, location, value);
      else if constexpr (std::is_same_v<T, int32>)
        ::glProgramUniform1i(program, location, value);
      else if constexpr (std::is_same_v<T, List<int32>>)
        ::glProgramUniform1iv(program, location, value.size(), value.data());
      else if constexpr (std::is_same_v<T, uint32>)
        ::glProgramUniform1ui(program, location, value);
      else if constexpr (std::is_same_v<T, List<uint32>>)
        ::glProgramUniform1uiv(program, location, value.size(), value.data());
      else if constexpr (std::is_same_v<T, uint64>)
        ::glProgramUniformHandleui64ARB(program, location, value);
      else if constexpr (std::is_same_v<T, float32>)
        ::glProgramUniform1f(program, location, value);
      else if constexpr (std::is_same_v<T, List<float32>>)
        ::glProgramUniform1fv(program, location, value.size(), value.data());
      else if constexpr (std::is_same_v<T, Vec2>)
        ::glProgramUniform2f(program, location, value.x, value.y);
      else if constexpr (std::is_same_v<T, List<Vec2>>)
        ::glProgramUniform2fv(program, location, value.size(), &value[0].x);
      else if constexpr (std::is_same_v<T, Vec3>)
        ::glProgramUniform3f(program, location, value.x, value.y, value.z);
      else if constexpr (std::is_same_v<T, List<Vec3>>)
        ::glProgramUniform3fv(program, location, value.size(), &value[0].x);
      else if constexpr (std::is_same_v<T, Vec4>)
        ::glProgramUniform4f(program, location, value.x, value.y, value.z, value.w);
      else if constexpr (std::is_same_v<T, List<Vec4>>)
        ::glProgramUniform4fv(program, location, value.size(), &value[0].x);
      else if constexpr (std::is_same_v<T, Mat2>)
        ::glProgramUniformMatrix2fv(program, location, 1, GL_FALSE, &value[0].x);
      else if constexpr (std::is_same_v<T, List<Mat2>>)
        ::glProgramUniformMatrix2fv(program, location, value.size(), GL_FALSE, &value[0][0].x);
      else if constexpr (std::is_same_v<T, Mat3>)
        ::glProgramUniformMatrix3fv(program, location, 1, GL_FALSE, &value[0].x);
      else if constexpr (std::is_same_v<T, List<Mat3>>)
        ::glProgramUniformMatrix3fv(program, location, value.size(), GL_FALSE, &value[0][0].x);
      else if constexpr (std::is_same_v<T, Mat4>)
        ::glProgramUniformMatrix4fv(program, location, 1, GL_FALSE, &value[0].x);
      else if constexpr (std::is_same_v<T, List<Mat4>>)
        ::glProgramUniformMatrix4fv(program, location, value.size(), GL_FALSE, &value[0][0].x);
      else
        KRYS_ASSERT(false, "Unsupported uniform type.");
    }

    void UpdateMaterialBuffers() noexcept;

    void UpdateTextureTable() noexcept;

    void UpdateLightBuffer() noexcept;

    PhongMaterialData GetBufferDataFromPhongMaterial(const PhongMaterial &mat) noexcept;
  };
}