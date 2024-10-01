#include "Graphics/Model.h"

#include "GLMesh.h"
#include "Textures/GLTexture2D.h"

namespace Krys
{
  Ref<Mesh> Model::CreateMesh(List<Vertex> &vertices, List<uint32> &indices, List<Ref<Texture2D>> &textures)
  {
    return CreateRef<GLMesh>(vertices, indices, textures);
  }

  Ref<Texture2D> Model::CreateTexture(TextureType type, const string &path)
  {
    return CreateRef<GLTexture2D>(path, type);
  }
}