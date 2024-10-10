
#include "Renderer.h"

namespace Krys
{

#pragma region Static member initialisation

  Ref<Window> Renderer::MainWindow;
  Ref<GraphicsContext> Renderer::Context;
  Map<BatchKey, Batch, BatchKeyHasher> Renderer::Batches;
  Ref<VertexArray> Renderer::BatchVertexArray;
  Ref<VertexBuffer> Renderer::BatchVertexBuffer;
  Ref<IndexBuffer> Renderer::BatchIndexBuffer;
  Ref<UniformBuffer> Renderer::SharedUniformBuffer;
  Ref<Camera> Renderer::ActiveCamera;
  RendererDefaults Renderer::Defaults;
  LightingModelType Renderer::LightingModel;
  List<DirectionalLight> Renderer::DirectionalLights;
  List<Ref<Framebuffer>> Renderer::DirectionalLightShadowFramebuffers;
  Ref<Shader> Renderer::DirectionalDepthMapShader;
  bool Renderer::IsWireFrameDrawingEnabled;

#pragma endregion Static member initialisation

  void Renderer::Init(Ref<Window> window, Ref<GraphicsContext> context) noexcept
  {
    MainWindow = window;
    Context = context;
    Batches = {};
    BatchVertexBuffer = Context->CreateVertexBuffer(MAX_VERTICES_PER_BATCH * static_cast<uint32>(sizeof(Vertex)));
    BatchVertexBuffer->SetLayout(VERTEX_BUFFER_LAYOUT_BATCH);
    BatchIndexBuffer = Context->CreateIndexBuffer(MAX_INDICES_PER_BATCH);
    BatchVertexArray = Context->CreateVertexArray(BatchVertexBuffer, BatchIndexBuffer);
    SharedUniformBuffer = Context->CreateUniformBuffer(UNIFORM_BUFFER_BINDING_SHARED, UNIFORM_BUFFER_LAYOUT_SHARED);

    LightingModel = LightingModelType::BlinnPhong;
    DirectionalLights.reserve(LIGHTING_MAX_DIRECTIONAL_LIGHTS);
    DirectionalLightShadowFramebuffers.reserve(LIGHTING_MAX_DIRECTIONAL_LIGHTS);
    DirectionalDepthMapShader = Context->CreateShader("shaders/depth/directional-light.vert", "shaders/empty.frag");
  }

  void Renderer::Begin(Ref<Camera> camera) noexcept
  {
    ActiveCamera = camera;
    SharedUniformBuffer->SetData("u_ViewProjection", camera->GetViewProjection());
    SharedUniformBuffer->SetData("u_CameraPosition", camera->GetPosition());
  }

  void Renderer::Draw(Ref<SceneObject> object) noexcept
  {
    auto key = GenerateBatchKey(object);
    auto &batch = GetOrAddBatch(key);
    batch.Objects.push_back(object);
  }

  void Renderer::End() noexcept
  {
    FlushBatches();
  }

  BatchKey Renderer::GenerateBatchKey(Ref<SceneObject> object) noexcept
  {
    BatchKey key{};
    key.PrimitiveType = object->Mesh->PrimitiveType;
    key.ShaderId = object->Material->Shader->GetId();
    key.Indexed = object->Mesh->Indices.size();
    key.CastsShadows = object->CastsShadows;

    return key;
  }

  Batch &Renderer::GetOrAddBatch(const BatchKey &key) noexcept
  {
    auto it = Batches.find(key);
    if (it != Batches.end())
      return it->second;

    Batch batch{key};
    Batches.insert(std::make_pair(key, batch));

    return Batches[key];
  }

  void Renderer::FlushBatches() noexcept
  {
    ShadowPass();
    GeometryPass();

    for (auto &[key, batch] : Batches)
    {
      batch.Objects.clear();
    }
  }

  void Renderer::SetDrawState(const Batch &batch) noexcept
  {
    const auto material = batch.Objects[0]->Material;
    const auto shader = material->Shader;
    shader->Bind();

    uint32 availableTextures = material->GetAvailableTextures();
    const string prefix = "u_Material.";
    shader->TrySetUniform(prefix + "AmbientColor", material->AmbientColor);
    shader->TrySetUniform(prefix + "DiffuseColor", material->DiffuseColor);
    shader->TrySetUniform(prefix + "SpecularColor", material->SpecularColor);
    shader->TrySetUniform(prefix + "Tint", material->Tint);
    shader->TrySetUniform(prefix + "Shininess", material->Shininess);
    shader->TrySetUniform(prefix + "AvailableTextures", static_cast<int>(availableTextures));

    if (availableTextures & MATERIAL_DIFFUSE_MAP_SET)
    {
      material->DiffuseMap->Bind(0);
      shader->TrySetUniform(prefix + "DiffuseMap", 0);
    }

    if (availableTextures & MATERIAL_SPECULAR_MAP_SET)
    {
      material->SpecularMap->Bind(1);
      shader->TrySetUniform(prefix + "SpecularMap", 1);
    }

    if (availableTextures & MATERIAL_EMISSION_MAP_SET)
    {
      material->EmissionMap->Bind(2);
      shader->TrySetUniform(prefix + "EmissionMap", 2);
    }

    if (availableTextures & MATERIAL_NORMAL_MAP_SET)
    {
      material->NormalMap->Bind(3);
      shader->TrySetUniform(prefix + "NormalMap", 3);
    }

    if (availableTextures & MATERIAL_DISPLACEMENT_MAP_SET)
    {
      material->DisplacementMap->Bind(4);
      shader->TrySetUniform(prefix + "DisplacementMap", 4);
    }

    DirectionalLightShadowFramebuffers[0]->GetDepthAttachment()->Bind(5);
    shader->TrySetUniform("u_DirectionalLightShadowMap", 5);
  }

  void Renderer::ShadowPass() noexcept
  {
    DirectionalDepthMapShader->Bind();
    for (int i = 0; i < DirectionalLights.size(); i++)
    {
      auto &light = DirectionalLights[i];
      auto &fb = DirectionalLightShadowFramebuffers[i];

      if (!light.Enabled)
        continue;

      fb->Bind();
      Context->SetViewport(fb->GetWidth(), fb->GetHeight());
      Context->Clear(RenderBuffer::Depth);
      DirectionalDepthMapShader->SetUniform("u_CurrentLight", i);

      for (const auto &[key, batch] : Batches)
      {
        for (auto object : batch.Objects)
        {
          if (!object->Material->CastsShadows)
            continue;

          DirectionalDepthMapShader->SetUniform("u_Model", object->Transform->GetModelMatrix());

          auto vertices = object->Mesh->Vertices;
          BatchVertexBuffer->SetData(vertices.data(), static_cast<uint32>(vertices.size() * sizeof(Vertex)));

          if (key.Indexed)
          {
            auto indices = object->Mesh->Indices;
            BatchIndexBuffer->SetData(indices.data(), static_cast<uint32>(indices.size()));
            Context->DrawIndices(indices.size(), key.PrimitiveType);
          }
          else
          {
            Context->DrawVertices(vertices.size(), key.PrimitiveType);
          }
        }
      }
      fb->Unbind();
    }
  }

  void Renderer::GeometryPass() noexcept
  {
    Context->SetViewport(MainWindow->GetWidth(), MainWindow->GetHeight());
    for (const auto &[key, batch] : Batches)
    {
      KRYS_ASSERT(batch.Objects.size() > 0, "Batch did not have any objects.", 0);

      SetDrawState(batch);

      const auto shader = batch.Objects[0]->Material->Shader;
      for (const auto &object : batch.Objects)
      {
        shader->SetUniform("u_Model", object->Transform->GetModelMatrix());

        auto vertices = object->Mesh->Vertices;
        BatchVertexBuffer->SetData(vertices.data(), static_cast<uint32>(vertices.size() * sizeof(Vertex)));

        if (key.Indexed)
        {
          auto indices = object->Mesh->Indices;
          BatchIndexBuffer->SetData(indices.data(), static_cast<uint32>(indices.size()));
          Context->DrawIndices(indices.size(), key.PrimitiveType);
        }
        else
        {
          Context->DrawVertices(vertices.size(), key.PrimitiveType);
        }
      }
    }
  }

  void Renderer::AddDirectionalLight(DirectionalLight &light) noexcept
  {
    auto index = DirectionalLights.size();
    DirectionalLights.push_back(light);
    SharedUniformBuffer->SetData("u_DirectionalLightCount", static_cast<int>(DirectionalLights.size()));

    Vec3 direction = -light.Direction;
    Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
    // Check if the direction is parallel or anti-parallel to the up vector
    if (glm::abs(glm::dot(glm::normalize(direction), glm::normalize(up))) > 0.999f)
      up = Vec3(1.0f, 0.0f, 0.0f);

    auto &shadowSettings = light.ShadowSettings;
    Mat4 projection = glm::ortho(shadowSettings.Bounds.Left, shadowSettings.Bounds.Right, shadowSettings.Bounds.Bottom, shadowSettings.Bounds.Top, shadowSettings.NearFarPlane.x, shadowSettings.NearFarPlane.y);
    Mat4 view = glm::lookAt(direction * 10.0f, Vec3(0.0f), up);
    light.ShadowSettings.LightSpaceMatrix = projection * view;

    string prefix = "u_DirectionalLights[" + std::to_string(index) + "].";
    SharedUniformBuffer->SetData(prefix + "Color", light.Color);
    SharedUniformBuffer->SetData(prefix + "Ambient", light.Ambient);
    SharedUniformBuffer->SetData(prefix + "Diffuse", light.Diffuse);
    SharedUniformBuffer->SetData(prefix + "Specular", light.Specular);
    SharedUniformBuffer->SetData(prefix + "Intensity", light.Intensity);
    SharedUniformBuffer->SetData(prefix + "Enabled", light.Enabled);
    SharedUniformBuffer->SetData(prefix + "Direction", light.Direction);
    SharedUniformBuffer->SetData(prefix + "CastsShadows", light.CastsShadows);
    SharedUniformBuffer->SetData(prefix + "Bias", shadowSettings.Bias);
    SharedUniformBuffer->SetData(prefix + "NearFarPlane", shadowSettings.NearFarPlane);
    SharedUniformBuffer->SetData(prefix + "LightSpaceMatrix", light.ShadowSettings.LightSpaceMatrix);

    auto fb = Context->CreateFramebuffer(light.ShadowSettings.ShadowMapResolution, light.ShadowSettings.ShadowMapResolution);
    fb->AddDepthAttachment();
    fb->DisableReadBuffer();
    fb->DisableWriteBuffers();
    KRYS_ASSERT(fb->IsComplete(), "Direction shadow map framebuffer incomplete", 0);

    DirectionalLightShadowFramebuffers.push_back(fb);
  }
}
