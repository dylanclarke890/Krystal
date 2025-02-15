#include "Graphics/Models/Loader.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/Colours.hpp"
#include "IO/IO.hpp"
#include "IO/Logger.hpp"
#include "rapidobj.hpp"

namespace Krys::Gfx
{
  Expected<Model> LoadModel(const stringview &path, ModelLoaderFlags flags) noexcept
  {
    auto result = rapidobj::ParseFile(path);

    if (result.error)
    {
      return Unexpected<string>(std::format("Failed to parse OBJ file: code: {0}, line: {1}, line_num {2}",
                                            result.error.code.message(), result.error.line,
                                            result.error.line_num));
    }

    if ((flags & ModelLoaderFlags::Triangulate) == ModelLoaderFlags::Triangulate)
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

    const auto &attrs = result.attributes;
    for (const auto &shape : result.shapes)
    {
      for (const auto &[position_index, texcoord_index, normal_index] : shape.mesh.indices)
      {
        Vec3 position = {attrs.positions[3 * position_index + 0], attrs.positions[3 * position_index + 1],
                         attrs.positions[3 * position_index + 2]};

        Vec2 textureCoord = {0.0f, 0.0f};
        Vec3 normal = {0.0f, 0.0f, 0.0f};
        Colour colour = Colours::White;

        if (texcoord_index != -1)
        {
          if ((flags & ModelLoaderFlags::FlipUVs) == ModelLoaderFlags::FlipUVs)
            textureCoord = {attrs.texcoords[2 * texcoord_index + 0],
                            1.0f - attrs.texcoords[2 * texcoord_index + 1]};
          else
            textureCoord = {attrs.texcoords[2 * texcoord_index + 0], attrs.texcoords[2 * texcoord_index + 1]};
        }

        if (normal_index != -1)
          normal = {attrs.normals[3 * normal_index + 0], attrs.normals[3 * normal_index + 1],
                    attrs.normals[3 * normal_index + 2]};

        model.Vertices.emplace_back(
          VertexData {position, normal, colour, Vec3 {textureCoord.x, textureCoord.y, 0.0f}});
        model.Indices.push_back(static_cast<uint32>(model.Indices.size()));
      }
    }

    return Expected<Model>(std::move(model));
  }
}