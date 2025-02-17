#include "Graphics/Models/ModelManager.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/Colours.hpp"
#include "IO/IO.hpp"
#include "IO/Logger.hpp"
#include "MTL/Vectors/Ext/Geometric.hpp"

#include "rapidobj.hpp"

namespace Krys::Gfx
{
  ModelManager::ModelManager(Ptr<MaterialManager> materialManager, Ptr<MeshManager> meshManager) noexcept
      : _materialManager(materialManager), _meshManager(meshManager)
  {
  }

  Expected<Model> ModelManager::LoadModel(const stringview &path, ModelLoaderFlags flags) noexcept
  {
    KRYS_SCOPED_PROFILER(std::format("ModelManager::LoadModel ({0})", path));

    auto result = rapidobj::ParseFile(path);

    if (result.error)
    {
      return Unexpected<string>(std::format("Failed to parse OBJ file: code: {0}, line: {1}, line_num {2}",
                                            result.error.code.message(), result.error.line,
                                            result.error.line_num));
    }

    if (!!(flags & ModelLoaderFlags::Triangulate))
    {
      rapidobj::Triangulate(result);
      if (result.error)
      {
        return Unexpected<string>(
          std::format("Failed to triangulate OBJ file: code: {0}, line: {1}, line_num {2}",
                      result.error.code.message(), result.error.line, result.error.line_num));
      }
    }

    Model model;
    model.Name = path;

    List<MaterialHandle> materials;
    for (const auto &mat : result.materials)
    {
      PhongMaterialDescriptor descriptor;
      descriptor.Ambient = Colour {mat.ambient[0], mat.ambient[1], mat.ambient[2]};
      descriptor.Diffuse = Colour {mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]};
      descriptor.Specular = Colour {mat.specular[0], mat.specular[1], mat.specular[2]};
      descriptor.Emissive = Colour {mat.emission[0], mat.emission[1], mat.emission[2]};
      // TODO: texture parameters
      descriptor.AmbientMap = mat.ambient_texname;
      descriptor.DiffuseMap = mat.diffuse_texname;
      descriptor.SpecularMap = mat.specular_texname;
      descriptor.EmissiveMap = mat.emissive_texname;
      descriptor.Shininess = mat.shininess;

      auto handle = _materialManager->CreatePhongMaterial(descriptor);
      materials.push_back(handle);
    }

    const auto &data = result.attributes;
    for (const auto &shape : result.shapes)
    {
      Map<int, List<rapidobj::Index>> indicesByMaterial;
      for (size_t i = 0; i < shape.mesh.indices.size(); i++)
      {
        const auto materialId = shape.mesh.material_ids[i / 3];
        indicesByMaterial[materialId].push_back(shape.mesh.indices[i]);
      }

      for (const auto &[materialId, modelIndices] : indicesByMaterial)
      {
        auto material =
          materialId != -1 ? materials[materialId] : _materialManager->GetDefaultPhongMaterial();

        List<VertexData> vertices;
        List<uint32> indices;

        for (const auto &[position_idx, texcoord_idx, normal_idx] : modelIndices)
        {
          Vec3 position = {data.positions[3 * position_idx + 0], data.positions[3 * position_idx + 1],
                           data.positions[3 * position_idx + 2]};

          Vec2 textureCoord = {0.0f, 0.0f};
          Vec3 normal = {0.0f, 0.0f, 0.0f};
          Colour colour = Colours::White;

          if (texcoord_idx != -1)
          {
            if (!!(flags & ModelLoaderFlags::FlipUVs))
              textureCoord = {data.texcoords[2 * texcoord_idx + 0],
                              1.0f - data.texcoords[2 * texcoord_idx + 1]};
            else
              textureCoord = {data.texcoords[2 * texcoord_idx + 0], data.texcoords[2 * texcoord_idx + 1]};
          }

          if (normal_idx != -1)
            normal = {data.normals[3 * normal_idx + 0], data.normals[3 * normal_idx + 1],
                      data.normals[3 * normal_idx + 2]};

          vertices.push_back(
            VertexData {position, normal, colour, Vec3 {textureCoord.x, textureCoord.y, 0.0f}});
          indices.push_back(static_cast<uint32>(vertices.size() - 1));
        }

        if (!!(flags & ModelLoaderFlags::DeduplicateVertices))
        {
          List<VertexData> uniqueVertices;
          List<uint32> newIndices;
          Map<VertexData, uint32> vertexToIndex;

          for (const auto &vertex : vertices)
          {
            auto it = vertexToIndex.find(vertex);
            if (it != vertexToIndex.end())
            {
              newIndices.push_back(it->second);
            }
            else
            {
              uint32 newIndex = static_cast<uint32>(uniqueVertices.size());
              uniqueVertices.push_back(vertex);
              vertexToIndex[vertex] = newIndex;
              newIndices.push_back(newIndex);
            }
          }

          vertices = std::move(uniqueVertices);
          indices = newIndices;
        }

        if (!!(flags & ModelLoaderFlags::GenerateFaceNormals))
        {
          for (size_t i = 0; i < indices.size(); i += 3)
          {
            auto &v0 = vertices[indices[i + 0]].Position;
            auto &v1 = vertices[indices[i + 1]].Position;
            auto &v2 = vertices[indices[i + 2]].Position;

            auto normal = GenerateNormal(v0, v1, v2);

            vertices[indices[i + 0]].Normal = normal;
            vertices[indices[i + 1]].Normal = normal;
            vertices[indices[i + 2]].Normal = normal;
          }
        }

        if (!!(flags & ModelLoaderFlags::GenerateVertexNormals))
        {
          // Initialize all normals to zero
          List<Vec3> normalSums(vertices.size(), Vec3(0.0f, 0.0f, 0.0f));

          // Accumulate face normals into vertex normals
          for (size_t i = 0; i < indices.size(); i += 3)
          {
            uint32_t i0 = indices[i + 0];
            uint32_t i1 = indices[i + 1];
            uint32_t i2 = indices[i + 2];

            Vec3 &v0 = vertices[i0].Position;
            Vec3 &v1 = vertices[i1].Position;
            Vec3 &v2 = vertices[i2].Position;

            Vec3 normal = GenerateNormal(v0, v1, v2);

            float area = Length(Cross(v1 - v0, v2 - v0)) * 0.5f; // Triangle area
            normal *= area;                                      // Weight by area

            normalSums[i0] += normal;
            normalSums[i1] += normal;
            normalSums[i2] += normal;
          }

          // Normalize the accumulated normals
          for (size_t i = 0; i < vertices.size(); ++i)
            vertices[i].Normal = MTL::Normalize(normalSums[i]);
        }

        auto mesh = _meshManager->CreateMesh(shape.name, vertices, indices);
        model.Renderables.push_back(Renderable {shape.name, mesh, material});
      }
    }

    return Expected<Model>(model);
  }

  Vec3 ModelManager::GenerateNormal(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2) const noexcept
  {
    return MTL::Normalize(MTL::Cross(v1 - v0, v2 - v0));
  }
}