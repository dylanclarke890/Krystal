#include "Graphics/Models/ModelManager.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/Colours.hpp"
#include "IO/IO.hpp"
#include "IO/Logger.hpp"
#include "MTL/Vectors/Ext/Geometric.hpp"
#include "Utils/Hash.hpp"

#include "rapidobj.hpp"

namespace Krys::Gfx
{
  struct SizeTUint32Hash
  {
    size_t operator()(const std::pair<size_t, uint32> &pair) const
    {
      return HashCombine(pair.first, pair.second);
    }
  };

  ModelManager::ModelManager(Ptr<MaterialManager> materialManager, Ptr<MeshManager> meshManager,
                             Ptr<TextureManager> textureManager) noexcept
      : _materialManager(materialManager), _meshManager(meshManager), _textureManager(textureManager)
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
      if (!mat.ambient_texname.empty())
        descriptor.AmbientMap = _textureManager->LoadTexture(mat.ambient_texname);

      if (!mat.diffuse_texname.empty())
        descriptor.DiffuseMap = _textureManager->LoadTexture(mat.diffuse_texname);

      if (!mat.specular_texname.empty())
        descriptor.SpecularMap = _textureManager->LoadTexture(mat.specular_texname);

      if (!mat.emissive_texname.empty())
        descriptor.EmissiveMap = _textureManager->LoadTexture(mat.emissive_texname);
      descriptor.Shininess = mat.shininess;

      auto handle = _materialManager->CreatePhongMaterial(descriptor);
      materials.push_back(handle);
    }

    const auto &data = result.attributes;
    for (const auto &shape : result.shapes)
    {
      Map<int, List<rapidobj::Index>> indicesByMaterial;
      indicesByMaterial.reserve(materials.size());

      for (size_t i = 0; i < shape.mesh.indices.size(); i++)
      {
        const auto materialId = shape.mesh.material_ids[i / 3];
        indicesByMaterial[materialId].push_back(shape.mesh.indices[i]);
      }

      for (const auto &[materialId, modelIndices] : indicesByMaterial)
      {
        auto material =
          materialId != -1 ? materials[materialId] : _materialManager->GetDefaultPhongMaterial();

        struct VertexRawInfo
        {
          rapidobj::Index index;
          int smoothingGroup;
        };

        List<VertexData> vertices;
        vertices.reserve(modelIndices.size());

        List<uint32> indices;
        indices.reserve(modelIndices.size());

        List<VertexRawInfo> vertexInfos;
        vertexInfos.reserve(modelIndices.size());

        // Build the raw vertex list. Note that we iterate by index so that we can compute
        // the face index (i/3) and thus the smoothing group for that vertex.
        for (size_t i = 0; i < modelIndices.size(); ++i)
        {
          const auto &idx = modelIndices[i];
          int faceIndex = static_cast<int>(i / 3);
          // Determine the smoothing group for this face (or -1 if none)
          int smoothingGroup =
            shape.mesh.smoothing_group_ids.empty() ? -1 : shape.mesh.smoothing_group_ids[faceIndex];

          Vec3 position = {data.positions[3 * idx.position_index + 0],
                           data.positions[3 * idx.position_index + 1],
                           data.positions[3 * idx.position_index + 2]};

          Vec2 textureCoord = {0.0f, 0.0f};
          if (idx.texcoord_index != -1)
          {
            if (!!(flags & ModelLoaderFlags::FlipUVs))
              textureCoord = {data.texcoords[2 * idx.texcoord_index + 0],
                              1.0f - data.texcoords[2 * idx.texcoord_index + 1]};
            else
              textureCoord = {data.texcoords[2 * idx.texcoord_index + 0],
                              data.texcoords[2 * idx.texcoord_index + 1]};
          }

          Vec3 normal = idx.normal_index != -1 ? Vec3 {data.normals[3 * idx.normal_index + 0],
                                                       data.normals[3 * idx.normal_index + 1],
                                                       data.normals[3 * idx.normal_index + 2]}
                                               : Vec3 {0.0f, 0.0f, 0.0f};

          Colour colour = Colours::White;

          vertices.push_back(
            VertexData {position, normal, colour, Vec3 {textureCoord.x, textureCoord.y, 0.0f}});
          indices.push_back(static_cast<uint32>(vertices.size() - 1));
          vertexInfos.push_back(VertexRawInfo {idx, smoothingGroup});
        }

        // Now compute and assign averaged normals on the raw vertex list.
        if (!!(flags & ModelLoaderFlags::GenerateNormals))
        {
          if (!data.normals.empty())
          {
            Logger::Warn("Generating normals for a model that already has normals.");
          }

          // We want to average contributions for vertices that represent the same
          // “logical vertex”. We key on the original OBJ indices (position and texcoord)
          // plus the smoothing group.
          struct VertexKey
          {
            int positionIdx;
            int texcoordIdx;
            int smoothingGroup;
            bool operator==(const VertexKey &other) const
            {
              return positionIdx == other.positionIdx && texcoordIdx == other.texcoordIdx
                     && smoothingGroup == other.smoothingGroup;
            }
          };
          struct VertexKeyHash
          {
            size_t operator()(const VertexKey &key) const
            {
              size_t h1 = std::hash<int>()(key.positionIdx);
              size_t h2 = std::hash<int>()(key.texcoordIdx);
              size_t h3 = std::hash<int>()(key.smoothingGroup);
              return HashCombine(h1, h2, h3);
            }
          };

          Map<VertexKey, Vec3, VertexKeyHash> normalSums;
          normalSums.reserve(vertices.size());
          Map<VertexKey, uint32, VertexKeyHash> normalCounts;
          normalCounts.reserve(vertices.size());

          // Process each face (every three consecutive indices form a triangle)
          for (size_t i = 0; i < indices.size(); i += 3)
          {
            uint32 i0 = indices[i + 0];
            uint32 i1 = indices[i + 1];
            uint32 i2 = indices[i + 2];

            const Vec3 &p0 = vertices[i0].Position;
            const Vec3 &p1 = vertices[i1].Position;
            const Vec3 &p2 = vertices[i2].Position;

            // Compute face normal (optionally weighted by area)
            Vec3 faceNormal = GenerateNormal(p0, p1, p2);
            float area = Length(Cross(p1 - p0, p2 - p0)) * 0.5f;
            faceNormal *= area;

            // Build keys for each vertex based on its original indices and smoothing group
            VertexKey key0 {vertexInfos[i0].index.position_index, vertexInfos[i0].index.texcoord_index,
                            vertexInfos[i0].smoothingGroup};
            VertexKey key1 {vertexInfos[i1].index.position_index, vertexInfos[i1].index.texcoord_index,
                            vertexInfos[i1].smoothingGroup};
            VertexKey key2 {vertexInfos[i2].index.position_index, vertexInfos[i2].index.texcoord_index,
                            vertexInfos[i2].smoothingGroup};

            // Accumulate the weighted face normal for each vertex key
            normalSums[key0] = normalSums[key0] + faceNormal;
            normalSums[key1] = normalSums[key1] + faceNormal;
            normalSums[key2] = normalSums[key2] + faceNormal;

            normalCounts[key0] = normalCounts[key0] + 1;
            normalCounts[key1] = normalCounts[key1] + 1;
            normalCounts[key2] = normalCounts[key2] + 1;
          }

          // Now assign each raw vertex the averaged normal (normalized).
          for (size_t i = 0; i < vertices.size(); ++i)
          {
            VertexKey key {vertexInfos[i].index.position_index, vertexInfos[i].index.texcoord_index,
                           vertexInfos[i].smoothingGroup};
            if (normalCounts[key] > 0)
            {
              vertices[i].Normal = MTL::Normalize(normalSums[key] / static_cast<float>(normalCounts[key]));
            }
          }
        }

        // Now deduplicate vertices using your existing logic.
        if (!!(flags & ModelLoaderFlags::RemoveDuplicateVertices))
        {
          List<VertexData> uniqueVertices;
          // Reserve roughly half the size of the vertices list as a guess.
          uniqueVertices.reserve(vertices.size() / 2);
          List<uint32> newIndices;
          newIndices.reserve(indices.size());

          Map<VertexData, uint32> vertexToIndex;
          vertexToIndex.reserve(vertices.size());

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

        if (!!(flags & ModelLoaderFlags::GenerateTangents))
        {
          Logger::Warn("Generating tangents is not yet implemented.");
        }

        if (!!(flags & ModelLoaderFlags::GenerateBitangents))
        {
          Logger::Warn("Generating bitangents is not yet implemented.");
        }

        if (!!(flags & ModelLoaderFlags::FlipWindingOrder))
        {
          for (size_t i = 0; i < indices.size(); i += 3)
          {
            std::swap(indices[i], indices[i + 2]);
          }
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
