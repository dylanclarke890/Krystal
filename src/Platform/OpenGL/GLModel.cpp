#include "Graphics/Model.h"

#include "GLMesh.h"
#include "GLTexture2D.h"

namespace Krys
{
  Ref<Mesh> Model::CreateMesh(std::vector<Vertex> &vertices, std::vector<uint32> &indices, std::vector<Ref<Texture2D>> &textures)
  {
    return CreateRef<GLMesh>(vertices, indices, textures);
  }

  Ref<Texture2D> Model::CreateTexture(TextureType type, const char *path)
  {
    return CreateRef<GLTexture2D>(type, path);
  }
}