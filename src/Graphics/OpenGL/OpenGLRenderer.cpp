#include "Graphics/OpenGL/OpenGLRenderer.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/BufferWriter.hpp"
#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/Lights/LightData.hpp"
#include "Graphics/Materials/PhongMaterial.hpp"
#include "Graphics/OpenGL/OpenGLBuffer.hpp"
#include "Graphics/OpenGL/OpenGLFramebuffer.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLMesh.hpp"
#include "Graphics/OpenGL/OpenGLMeshManager.hpp"
#include "Graphics/OpenGL/OpenGLProgram.hpp"
#include "Graphics/OpenGL/OpenGLTexture.hpp"
#include "Graphics/OpenGL/OpenGLTextureManager.hpp"
#include "Graphics/RenderTargets/RenderTargetManager.hpp"
#include "Graphics/Scene/MaterialNode.hpp"
#include "Graphics/Scene/MeshNode.hpp"
#include "Graphics/Scene/Node.hpp"
#include "Graphics/Scene/SceneGraphManager.hpp"
#include "MTL/Matrices/Ext/Inverse.hpp"
#include "MTL/Matrices/Ext/Transpose.hpp"
#include "MTL/Matrices/Mat3x3.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLRenderer::OpenGLRenderer(const RenderContext &context) noexcept : Renderer(context)
  {
  }

  void OpenGLRenderer::Init() noexcept
  {
    auto max_ssbo_size = _ctx.GraphicsContext->GetDeviceCapabilities().MaxShaderStorageBlockSize;

    _phongMaterialBufferHandle = _ctx.GraphicsContext->CreateShaderStorageBuffer(max_ssbo_size);
    _textureTableHandle = _ctx.GraphicsContext->CreateShaderStorageBuffer(max_ssbo_size);
    _lightBufferHandle = _ctx.GraphicsContext->CreateShaderStorageBuffer(max_ssbo_size);

    _phongMaterialBuffer = _ctx.GraphicsContext->GetShaderStorageBuffer(_phongMaterialBufferHandle);
    _textureTable = _ctx.GraphicsContext->GetShaderStorageBuffer(_textureTableHandle);
    _lightBuffer = _ctx.GraphicsContext->GetShaderStorageBuffer(_lightBufferHandle);
  }

  static OpenGLTexture *_cyanTexture;
  static OpenGLTexture *_orangeTexture;
  static GLuint _cyanVAO;
  static GLuint _orangeVAO;
  static OpenGLProgram *_program;

  void OpenGLRenderer::SetupTest() noexcept
  {
    {
      auto handle = _ctx.TextureManager->CreateFlatColourTexture(Colours::Cyan);
      _cyanTexture = static_cast<OpenGLTexture *>(_ctx.TextureManager->GetTexture(handle));
      glObjectLabel(GL_TEXTURE, _cyanTexture->GetNativeHandle(), -1, "Cyan Texture");
    }

    {
      auto handle = _ctx.TextureManager->CreateFlatColourTexture(Colours::Orange);
      _orangeTexture = static_cast<OpenGLTexture *>(_ctx.TextureManager->GetTexture(handle));
      glObjectLabel(GL_TEXTURE, _orangeTexture->GetNativeHandle(), -1, "Orange Texture");
    }

    // Create a vertexBuffer for the cyan quad that covers the left half of the screen
    auto cyanVertices = std::array<float, 16> {
      -1.0f, -1.0f, 0.0f, 0.0f, // Bottom left
      0.0f,  -1.0f, 1.0f, 0.0f, // Bottom right (at center)
      -1.0f, 1.0f,  0.0f, 1.0f, // Top left
      0.0f,  1.0f,  1.0f, 1.0f  // Top right (at center)
    };

    // Create a vertexBuffer for the orange quad that covers the right half of the screen
    auto orangeVertices = std::array<float, 16> {
      0.0f, -1.0f, 0.0f, 0.0f, // Bottom left (at center)
      1.0f, -1.0f, 1.0f, 0.0f, // Bottom right
      0.0f, 1.0f,  0.0f, 1.0f, // Top left (at center)
      1.0f, 1.0f,  1.0f, 1.0f  // Top right
    };

    auto CreateVAO = [&](GLuint &vao, const Array<float, 16> &vertices) noexcept
    {
      glCreateVertexArrays(1, &vao);
      glBindVertexArray(vao);

      VertexBufferHandle vBufferHandle =
        _ctx.GraphicsContext->CreateVertexBuffer((uint32)(vertices.size() * sizeof(float)));
      {
        auto *buffer =
          static_cast<OpenGLVertexBuffer *>(_ctx.GraphicsContext->GetVertexBuffer(vBufferHandle));
        BufferWriter<VertexBuffer> writer(*buffer);
        writer.Write(vertices);
      }

      auto indices = std::array<uint32, 6> {0, 1, 2, 1, 3, 2};
      IndexBufferHandle iBufferHandle =
        _ctx.GraphicsContext->CreateIndexBuffer((uint32)(indices.size() * sizeof(uint32)));

      {
        auto *buffer = static_cast<OpenGLIndexBuffer *>(_ctx.GraphicsContext->GetIndexBuffer(iBufferHandle));
        BufferWriter<IndexBuffer> writer(*buffer);
        writer.Write(indices);
      }

      VertexLayout layout({VertexAttributeType::FLOAT_2, VertexAttributeType::FLOAT_2});
      static_cast<OpenGLGraphicsContext *>(_ctx.GraphicsContext)
        ->SetupVertexArray(vBufferHandle, iBufferHandle, layout);
    };

    CreateVAO(_cyanVAO, cyanVertices);
    glObjectLabel(GL_VERTEX_ARRAY, _cyanVAO, -1, "Cyan VAO");
    CreateVAO(_orangeVAO, orangeVertices);
    glObjectLabel(GL_VERTEX_ARRAY, _orangeVAO, -1, "Orange VAO");

    {
      auto fragmentShader =
        _ctx.GraphicsContext->CreateShader(ShaderStage::Fragment, IO::ReadFileText("shaders/basic.frag"));
      auto vertexShader =
        _ctx.GraphicsContext->CreateShader(ShaderStage::Vertex, IO::ReadFileText("shaders/basic.vert"));
      auto programHandle = _ctx.GraphicsContext->CreateProgram(fragmentShader, vertexShader);

      _program = static_cast<OpenGLProgram *>(_ctx.GraphicsContext->GetProgram(programHandle));
      _program->Bind();
      glObjectLabel(GL_PROGRAM, _program->GetNativeHandle(), -1, "Test Program");
    }
  }

  void OpenGLRenderer::OnRenderPipelineChange() noexcept
  {
    _framebuffers.clear();

    auto GetTexture = [&](const auto &attachment) -> GLuint
    {
      auto *renderTarget = _ctx.RenderTargetManager->GetRenderTarget(attachment.Target);
      auto *texture = _ctx.TextureManager->GetTexture(renderTarget->GetTexture());
      return static_cast<OpenGLTexture *>(texture)->GetNativeHandle();
    };

    auto &passes = _pipeline.GetPasses();

    for (size_t i = 0; i < passes.size(); i++)
    {
      auto &pass = passes[i];

      if (pass.HasNoAttachments())
        continue;

      if (pass.Name.empty())
        pass.Name = "Pass" + std::to_string(i);

      OpenGLFramebufferDescriptor descriptor;
      descriptor.ColourAttachments.resize(pass.ColourAttachments.size());
      std::transform(pass.ColourAttachments.begin(), pass.ColourAttachments.end(),
                     descriptor.ColourAttachments.begin(), GetTexture);

      if (pass.DepthAttachment.Target.IsValid())
        descriptor.DepthAttachment = GetTexture(pass.DepthAttachment);
      if (pass.StencilAttachment.Target.IsValid())
        descriptor.StencilAttachment = GetTexture(pass.StencilAttachment);

      _framebuffers.emplace(pass.Name, CreateUnique<OpenGLFramebuffer>(descriptor));
    }

    UpdateTextureTable();
    UpdateMaterialBuffers();
    UpdateLightBuffer();

    static_cast<OpenGLShaderStorageBuffer &>(*_phongMaterialBuffer).Bind(0);
    static_cast<OpenGLShaderStorageBuffer &>(*_textureTable).Bind(1);
    static_cast<OpenGLShaderStorageBuffer &>(*_lightBuffer).Bind(2);
  }

  void OpenGLRenderer::BeforeRenderPass(const RenderPass &pass) noexcept
  {
    ::glClearColor(pass.ClearValues.Color.x, pass.ClearValues.Color.y, pass.ClearValues.Color.z,
                   pass.ClearValues.Color.w);
    ::glClearDepth(pass.ClearValues.Depth);
    ::glClearStencil(pass.ClearValues.Stencil);

    if (pass.HasNoAttachments())
    {
      auto *window = _ctx.WindowManager->GetCurrentWindow();

      ::glBindFramebuffer(GL_FRAMEBUFFER, 0);
      ::glViewport(0, 0, window->GetWidth(), window->GetHeight());

      ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      return;
    }

    auto *framebuffer = _framebuffers.at(pass.Name).get();
    framebuffer->Bind();
    ::glViewport(0, 0, framebuffer->GetDescriptor().Width, framebuffer->GetDescriptor().Height);

    GLenum clearFlags = 0;
    // TODO: not really sure what to do if there are multiple colour attachments with different clear
    // operations.
    if (!pass.ColourAttachments.empty() && pass.ColourAttachments[0].LoadOperation == AttachmentLoadOp::Clear)
      clearFlags |= GL_COLOR_BUFFER_BIT;

    if (pass.DepthAttachment.Target.IsValid()
        && pass.DepthAttachment.LoadOperation == AttachmentLoadOp::Clear)
      clearFlags |= GL_DEPTH_BUFFER_BIT;

    if (pass.StencilAttachment.Target.IsValid()
        && pass.StencilAttachment.LoadOperation == AttachmentLoadOp::Clear)
      clearFlags |= GL_STENCIL_BUFFER_BIT;

    ::glClear(clearFlags);
  }

  void OpenGLRenderer::AfterRenderPass(const RenderPass &) noexcept
  {
  }

  void OpenGLRenderer::RenderTest() noexcept
  {
    ::glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "OpenGLRenderer::RenderTest");

    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    ::glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ::glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "RenderTest::Cyan");
    if (_cyanTexture->IsBindless())
    {
      SetUniform(_program->GetNativeHandle(), "u_Texture", _cyanTexture->GetNativeBindlessHandle());
    }
    else
    {
      SetUniform(_program->GetNativeHandle(), "u_Texture", 0);
      _cyanTexture->Bind(0);
    }
    ::glBindVertexArray(_cyanVAO);
    ::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    ::glPopDebugGroup();

    ::glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "RenderTest::Orange");
    if (_orangeTexture->IsBindless())
    {
      SetUniform(_program->GetNativeHandle(), "u_Texture", _orangeTexture->GetNativeBindlessHandle());
    }
    else
    {
      SetUniform(_program->GetNativeHandle(), "u_Texture", 0);
      _orangeTexture->Bind(0);
    }
    ::glBindVertexArray(_orangeVAO);
    ::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    ::glPopDebugGroup();

    ::glPopDebugGroup();
  }

  void OpenGLRenderer::Render() noexcept
  {
    BeforeRender();

    for (auto &pass : _pipeline.GetPasses())
    {
      BeforeRenderPass(pass);

      auto *sceneGraph = _ctx.SceneGraphManager->GetScene(pass.SceneGraph);
      Render(sceneGraph->GetRoot(), Transform {}, *pass.Camera);

      AfterRenderPass(pass);
    }

    AfterRender();
  }

  void OpenGLRenderer::Render(Node *node, const Transform &parentTransform, Camera &camera) noexcept
  {
    if (!node->IsLeaf())
    {
      for (auto &child : node->GetChildren())
        Render(child.get(), parentTransform * node->GetLocalTransform(), camera);
    }

    static MaterialHandle activeMaterial = _ctx.MaterialManager->GetDefaultPhongMaterial();

    switch (node->GetNodeType())
    {
      case SID("material"):
      {
        activeMaterial = static_cast<MaterialNode *>(node)->GetMaterial();
        break;
      }
      case SID("mesh"):
      {
        auto &meshNode = *static_cast<MeshNode *>(node);
        auto &mesh = *_ctx.MeshManager->GetMesh(meshNode.GetMesh());
        auto &material = *static_cast<PhongMaterial *>(_ctx.MaterialManager->GetMaterial(activeMaterial));

        // Resetting it back for the next mesh.
        activeMaterial = _ctx.MaterialManager->GetDefaultPhongMaterial();

        auto &program =
          static_cast<OpenGLProgram &>(*_ctx.GraphicsContext->GetProgram(material.GetProgram()));
        program.Bind();

        // TODO: we need to get the index differently once we add PBR materials.
        SetUniform<int>(program.GetNativeHandle(), "u_MaterialIndex", material.GetHandle().Id());

        auto transform = parentTransform * node->GetLocalTransform();
        auto modelMatrix = transform.GetMatrix();
        auto normalMatrix = MTL::Transpose(MTL::Inverse(Mat3(modelMatrix)));

        SetUniform(program.GetNativeHandle(), "u_Model", modelMatrix);
        SetUniform(program.GetNativeHandle(), "u_Normal", normalMatrix);

        SetUniform(program.GetNativeHandle(), "u_View", camera.GetView());
        SetUniform(program.GetNativeHandle(), "u_Projection", camera.GetProjection());
        SetUniform(program.GetNativeHandle(), "u_CameraPosition", camera.GetPosition());
        SetUniform(program.GetNativeHandle(), "u_LightCount", (int)_ctx.LightManager->GetLights().size());

        mesh.Bind();
        if (mesh.IsIndexed())
          _ctx.GraphicsContext->DrawElements(mesh.GetPrimitiveType(), static_cast<uint32>(mesh.GetCount()));
        else
          _ctx.GraphicsContext->DrawArrays(mesh.GetPrimitiveType(), static_cast<uint32>(mesh.GetCount()));
      }
      default: break;
    }
  }

  void OpenGLRenderer::UpdateMaterialBuffers() noexcept
  {
    BufferWriter phongBufferWriter(*_phongMaterialBuffer);

    for (auto &[handle, material] : _ctx.MaterialManager->GetMaterials())
    {
      if (!material->IsDirty())
        continue;

      if (material->GetType() == MaterialType::Phong)
      {
        // TODO: we need to get the index differently once we add PBR materials.
        auto index = handle.Id();
        auto &phong = static_cast<PhongMaterial &>(*material);

        phongBufferWriter.Seek(index * sizeof(PhongMaterialData));
        PhongMaterialData data;
        memset(reinterpret_cast<void *>(&data), 0, sizeof(PhongMaterialData));

        KRYS_ASSERT(phong.GetAmbientMap().IsValid(), "Ambient map is invalid.");
        KRYS_ASSERT(phong.GetDiffuseMap().IsValid(), "Diffuse map is invalid.");
        KRYS_ASSERT(phong.GetSpecularMap().IsValid(), "Specular map is invalid.");
        KRYS_ASSERT(phong.GetEmissionMap().IsValid(), "Emission map is invalid.");

        data.Ambient = Colour::ToVec3(phong.GetAmbient());
        data.Diffuse = Colour::ToVec3(phong.GetDiffuse());
        data.Specular = Colour::ToVec3(phong.GetSpecular());
        data.Emission = Colour::ToVec3(phong.GetEmission());
        data.AmbientTexture = _textureIndexes[phong.GetAmbientMap()];
        data.DiffuseTexture = _textureIndexes[phong.GetDiffuseMap()];
        data.SpecularTexture = _textureIndexes[phong.GetSpecularMap()];
        data.EmissionTexture = _textureIndexes[phong.GetEmissionMap()];
        data.Shininess = phong.GetShininess();

        phongBufferWriter.Write(data);
      }

      material->ClearIsDirtyFlag();
    }
  }

  void OpenGLRenderer::UpdateTextureTable() noexcept
  {
    BufferWriter textureTableWriter(*_textureTable);

    uint32 index = 0;
    _textureIndexes.clear();
    for (const auto &[handle, texture] : _ctx.TextureManager->GetTextures())
    {
      Logger::Debug("Texture: {} - {}", handle.Id(), texture->GetName());
      {
        _textureIndexes[handle] = index;
        textureTableWriter.Seek(index * sizeof(GLuint64));
        textureTableWriter.Write(static_cast<OpenGLTexture *>(texture)->GetNativeBindlessHandle());
        index++;
      }
    }
  }

  void OpenGLRenderer::UpdateLightBuffer() noexcept
  {
    BufferWriter lightBufferWriter(*_lightBuffer);

    for (const auto &[handle, light] : _ctx.LightManager->GetLights())
    {
      if (!light->IsDirty())
        continue;

      auto index = handle.Id();
      lightBufferWriter.Seek(index * sizeof(LightData));

      const auto lightData = light.get()->GetData();
      lightBufferWriter.Write(lightData);

      light->ClearIsDirtyFlag();
    }
  }
}