
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

    Defaults.LightingFactor = Vec3(1.0f);
    LightingModel = LightingModelType::BlinnPhong;
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
    key.MaterialId = object->Material->Id;
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

    const string prefix = "u_Material.";
    shader->TrySetUniform(prefix + "AmbientColor", material->AmbientColor);
    shader->TrySetUniform(prefix + "DiffuseColor", material->DiffuseColor);
    shader->TrySetUniform(prefix + "SpecularColor", material->SpecularColor);
    shader->TrySetUniform(prefix + "Tint", material->Tint);
    shader->TrySetUniform(prefix + "Shininess", material->Shininess);

    if (material->DiffuseMap)
    {
      material->DiffuseMap->Bind(0);
      shader->TrySetUniform(prefix + "DiffuseMap", 0);
    }

    if (material->SpecularMap)
    {
      material->SpecularMap->Bind(1);
      shader->TrySetUniform(prefix + "SpecularMap", 1);
    }

    if (material->EmissionMap)
    {
      material->EmissionMap->Bind(2);
      shader->TrySetUniform(prefix + "EmissionMap", 2);
    }

    if (material->NormalMap)
    {
      material->NormalMap->Bind(3);
      shader->TrySetUniform(prefix + "NormalMap", 3);
    }

    if (material->DisplacementMap)
    {
      material->DisplacementMap->Bind(4);
      shader->TrySetUniform(prefix + "DisplacementMap", 4);
    }
  }
}
