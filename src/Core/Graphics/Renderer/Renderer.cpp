
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
    BatchIndexBuffer = Context->CreateIndexBuffer(MAX_INDICES_PER_BATCH);
    BatchVertexArray = Context->CreateVertexArray(BatchVertexBuffer, BatchIndexBuffer);
    SharedUniformBuffer = Context->CreateUniformBuffer(UNIFORM_BUFFER_BINDING_SHARED, UNIFORM_BUFFER_LAYOUT_SHARED);

    Defaults.Shader = Context->CreateShader("shaders/scene-object.vert", "shaders/scene-object.frag");
    Defaults.LightingFactor = Vec3(1.0f);
    LightingModel = LightingModelType::BlinnPhong;
  }

  void Renderer::Draw(Ref<SceneObject> object) noexcept
  {
    auto key = GenerateBatchKey(object);
    auto batch = GetOrAddBatch(key);
    batch.Objects.push_back(object);
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

  void Renderer::FlushBatch(const Batch &batch) noexcept
  {
    KRYS_ASSERT(batch.Objects.size() > 0, "Batch did not have any objects.", 0);

    SetDrawState(batch);

    const auto shader = batch.Objects[0]->Material->Shader;
    for (const auto object : batch.Objects)
    {
      shader->SetUniform("u_Model", object->Transform->GetModelMatrix());

      auto vertices = object->Mesh->Vertices;
      BatchVertexBuffer->SetData(vertices.data(), static_cast<uint32>(vertices.size() * sizeof(Vertex)));

      if (batch.Key.Indexed)
      {
        auto indices = object->Mesh->Indices;
        BatchIndexBuffer->SetData(indices.data(), static_cast<uint32>(indices.size()));
        Context->DrawIndices(indices.size(), batch.Key.PrimitiveType);
      }
      else
      {
        Context->DrawVertices(vertices.size(), batch.Key.PrimitiveType);
      }
    }
  }

  void Renderer::SetDrawState(const Batch &batch) noexcept
  {
    const auto material = batch.Objects[0]->Material;
    const auto shader = material->Shader;
    shader->Bind();

    const string prefix = "u_Material.";
    shader->SetUniform(prefix + "AmbientColor", material->AmbientColor);
    shader->SetUniform(prefix + "DiffuseColor", material->DiffuseColor);
    shader->SetUniform(prefix + "SpecularColor", material->SpecularColor);
    shader->SetUniform(prefix + "Tint", material->Tint);
    shader->SetUniform(prefix + "Shininess", material->Shininess);

    if (material->DiffuseMap)
    {
      material->DiffuseMap->Bind(0);
      shader->SetUniform(prefix + "DiffuseMap", 0);
    }

    if (material->SpecularMap)
    {
      material->DiffuseMap->Bind(1);
      shader->SetUniform(prefix + "SpecularMap", 1);
    }

    if (material->EmissionMap)
    {
      material->DiffuseMap->Bind(2);
      shader->SetUniform(prefix + "EmissionMap", 2);
    }

    if (material->NormalMap)
    {
      material->DiffuseMap->Bind(3);
      shader->SetUniform(prefix + "NormalMap", 3);
    }

    if (material->DisplacementMap)
    {
      material->DiffuseMap->Bind(4);
      shader->SetUniform(prefix + "DisplacementMap", 4);
    }
  }
}
