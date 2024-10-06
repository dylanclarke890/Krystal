#pragma once

#include "Core.h"
#include "Assets.h"
#include "Maths/Maths.h"

namespace Krys::Assets
{
  class Importer
  {
  protected:
    stringview Path;
    AssetImportResult Result;
    List<IntermediateMesh> IntermediateMeshes;

  public:
    Importer(const stringview &path) noexcept
        : Path(path), Result({}), IntermediateMeshes({})
    {
      Result.ImportedModel = CreateRef<Model>();
      Result.ImportedModel->Path = string{path.data()};
    }

    virtual ~Importer() = default;

    virtual void Parse() noexcept = 0;

    const AssetImportResult &GetResult() const noexcept { return Result; }
    const stringview &GetPath() const noexcept { return Path; }

  protected:
    void ProcessIntermediateMeshes() noexcept
    {
      Result.ImportedModel->Meshes.reserve(IntermediateMeshes.size());
      for (const auto &intMesh : IntermediateMeshes)
      {
        Ref<Mesh> mesh = CreateRef<Mesh>();
        Result.ImportedModel->Meshes.push_back(mesh);
        mesh->PrimitiveType = intMesh.PrimitiveType;
        mesh->Indices = intMesh.Indices;
        mesh->Vertices.reserve(intMesh.Positions.size());

        for (int i = 0; i < intMesh.Positions.size(); i++)
        {
          VertexData vertex{};
          vertex.Position = Vec4(std::move(intMesh.Positions[i]), 1.0f);
          vertex.Normal = std::move(intMesh.Normals[i]);

          if (intMesh.TextureCoords.size() > 0)
            vertex.TextureCoords = std::move(intMesh.TextureCoords[i]);
          if (intMesh.Colors.size() > 0)
            vertex.Color = std::move(intMesh.Colors[i]);

          mesh->Vertices.emplace_back(vertex);
        }
      }
    }
  };
}
