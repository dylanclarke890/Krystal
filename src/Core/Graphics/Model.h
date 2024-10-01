#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Krystal.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Mesh.h"

namespace Krys
{
  static Map<string, Ref<Texture2D>> LoadedTextures;

  class Model
  {
  private:
    List<Ref<Mesh>> Meshes;
    string directory;

  public:
    Model(const string &path)
    {
      Load(path);
    }

    void Draw(Ref<Shader> shader)
    {
      for (auto mesh : Meshes)
        mesh->Draw(shader);
    }

  private:
    void Load(const string &path)
    {
      KRYS_PERFORMANCE_TIMER("Loading Model");

      Assimp::Importer import;
      const aiScene *scene = import.ReadFile(path,
                                             aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

      if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
      {
        KRYS_ERROR("ASSIMP:: %s", import.GetErrorString());
        return;
      }

      directory = path.substr(0, path.find_last_of('/'));

      ProcessNode(scene->mRootNode, scene);
    }

    void ProcessNode(aiNode *node, const aiScene *scene)
    {
      // process all the node's meshes (if any)
      for (uint i = 0; i < node->mNumMeshes; i++)
      {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        Meshes.push_back(ProcessMesh(mesh, scene));
      }
      // then do the same for each of its children
      for (uint i = 0; i < node->mNumChildren; i++)
      {
        ProcessNode(node->mChildren[i], scene);
      }
    }

    Ref<Mesh> ProcessMesh(aiMesh *mesh, const aiScene *scene)
    {
      List<Vertex> vertices;
      List<uint32> indices;
      List<Ref<Texture2D>> textures;

      for (uint i = 0; i < mesh->mNumVertices; i++)
      {
        Vertex vertex;
        vertex.Position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex.Normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};

        // does the mesh contain texture coordinates?
        if (mesh->mTextureCoords[0])
          // TODO: assimp allows up to 8. Do we need more?
          vertex.TextureCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        else
          vertex.TextureCoords = {0.0f, 0.0f};

        vertices.push_back(vertex);
      }

      for (uint i = 0; i < mesh->mNumFaces; i++)
      {
        aiFace face = mesh->mFaces[i];
        for (uint j = 0; j < face.mNumIndices; j++)
          indices.push_back(static_cast<uint32>(face.mIndices[j]));
      }

      // process material
      if (mesh->mMaterialIndex >= 0)
      {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        auto diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        auto specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
      }

      return CreateMesh(vertices, indices, textures);
    }

    List<Ref<Texture2D>> LoadMaterialTextures(aiMaterial *material, aiTextureType assimpType, TextureType krysType)
    {
      List<Ref<Texture2D>> textures;
      for (uint i = 0; i < material->GetTextureCount(assimpType); i++)
      {
        // TODO: this is currently relative to the directory
        aiString path;
        material->GetTexture(assimpType, i, &path);
        string filepath = directory + "/" + path.C_Str();

        if (LoadedTextures.find(filepath) == LoadedTextures.end())
        {
          auto texture = CreateTexture(krysType, filepath.c_str());
          textures.push_back(texture);
        }
        else
        {
          textures.push_back(LoadedTextures.at(filepath));
        }
      }
      return textures;
    }

    // TODO: forward args
    // TODO: move to context somehow
    // TODO: handle normal maps
    static Ref<Mesh> CreateMesh(List<Vertex> &vertices, List<uint32> &indices, List<Ref<Texture2D>> &textures);
    static Ref<Texture2D> CreateTexture(TextureType type, const string &path);
  };
}