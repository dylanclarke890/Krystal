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
    }

    virtual ~Importer() = default;

    virtual void Parse() noexcept = 0;

    const AssetImportResult &GetResult() const noexcept { return Result; }
    const stringview &GetPath() const noexcept { return Path; }

  protected:
    void ProcessIntermediateMeshes() noexcept
    {
      Result.SceneObjects.reserve(IntermediateMeshes.size());
      for (const auto &intMesh : IntermediateMeshes)
      {
        Ref<SceneObject> sceneObject = CreateRef<SceneObject>();

        Ref<Mesh> mesh = CreateRef<Mesh>();
        mesh->PrimitiveType = intMesh.PrimitiveType;
        mesh->Indices = intMesh.Indices;
        mesh->Vertices.reserve(intMesh.Positions.size());

        for (int i = 0; i < intMesh.Positions.size(); i++)
        {
          Vertex vertex{};
          vertex.Position = std::move(intMesh.Positions[i]);
          vertex.Normal = std::move(intMesh.Normals[i]);

          if (intMesh.TextureCoords.size() > 0)
            vertex.TextureCoords = std::move(intMesh.TextureCoords[i]);
          if (intMesh.Colors.size() > 0)
            vertex.Color = std::move(intMesh.Colors[i]);

          mesh->Vertices.emplace_back(vertex);
        }

        sceneObject->Mesh = mesh;
        Result.SceneObjects.emplace_back(sceneObject);
      }
    }
  };
}
