#pragma once

#include "Core.h"
#include "Graphics/Graphics.h"
#include "Graphics/Colors.h"
#include "Graphics/Mesh.h"
#include "Graphics/Utils/TangentSpace.h"
#include "Maths/Vector.h"

namespace Krys::Graphics
{
  using namespace Krys::Maths;

  class MeshFactory
  {
  public:
    static Ref<Mesh> Create()
    {
      return CreateRef<Mesh>();
    }

    static Ref<Mesh> CreateTriangle(const Vec4 &color = Colors::White)
    {
      constexpr Vec3 TRIANGLE_POSITIONS[] = {{0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {0.0f, 0.5f, 0.0f}};
      constexpr Vec3 TRIANGLE_FLAT_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
      constexpr Vec2 TRIANGLE_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {0.5f, 1.0f}, {1.0f, 0.0f}};

      List<uint32> indices = {0, 1, 2};
      List<Vertex> vertices;
      vertices.reserve(3);
      for (int i = 0; i < 3; i++)
        vertices.push_back({TRIANGLE_POSITIONS[i], TRIANGLE_FLAT_NORMALS[i], color, TRIANGLE_TEXTURE_COORDS[i]});

      CalculateTangents(vertices, indices);

      auto mesh = CreateRef<Mesh>();
      mesh->Vertices = vertices;
      mesh->Indices = indices;

      return mesh;
    }

    static Ref<Mesh> CreateQuad(const Vec4 &color = Colors::White)
    {
      constexpr Vec3 QUAD_POSITIONS[] = {{-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};
      constexpr Vec3 QUAD_FLAT_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
      constexpr Vec2 QUAD_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

      List<uint32> indices = {0, 1, 2, 2, 3, 0};
      List<Vertex> vertices;
      vertices.reserve(4);
      for (int i = 0; i < 4; i++)
        vertices.push_back({QUAD_POSITIONS[i], QUAD_FLAT_NORMALS[i], color, QUAD_TEXTURE_COORDS[i]});

      CalculateTangents(vertices, indices);

      auto mesh = CreateRef<Mesh>();
      mesh->Vertices = vertices;
      mesh->Indices = indices;

      return mesh;
    }

    static Ref<Mesh> CreateCube(const Vec4 &color = Colors::White)
    {
      constexpr Vec3 CUBE_POSITIONS_VERTICES[] = {
          {-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f}, // Front face
          {-0.5f, -0.5f, -0.5f},
          {0.5f, -0.5f, -0.5f},
          {0.5f, 0.5f, -0.5f},
          {-0.5f, 0.5f, -0.5f}, // Back face
          {-0.5f, -0.5f, -0.5f},
          {-0.5f, -0.5f, 0.5f},
          {-0.5f, 0.5f, 0.5f},
          {-0.5f, 0.5f, -0.5f}, // Left face
          {0.5f, -0.5f, -0.5f},
          {0.5f, -0.5f, 0.5f},
          {0.5f, 0.5f, 0.5f},
          {0.5f, 0.5f, -0.5f}, // Right face
          {-0.5f, 0.5f, 0.5f},
          {0.5f, 0.5f, 0.5f},
          {0.5f, 0.5f, -0.5f},
          {-0.5f, 0.5f, -0.5f}, // Top face
          {-0.5f, -0.5f, 0.5f},
          {0.5f, -0.5f, 0.5f},
          {0.5f, -0.5f, -0.5f},
          {-0.5f, -0.5f, -0.5f} // Bottom face
      };
      constexpr Vec3 CUBE_FLAT_NORMALS[] = {
          {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, // Front face
          {0.0f, 0.0f, -1.0f},
          {0.0f, 0.0f, -1.0f},
          {0.0f, 0.0f, -1.0f},
          {0.0f, 0.0f, -1.0f}, // Back face
          {-1.0f, 0.0f, 0.0f},
          {-1.0f, 0.0f, 0.0f},
          {-1.0f, 0.0f, 0.0f},
          {-1.0f, 0.0f, 0.0f}, // Left face
          {1.0f, 0.0f, 0.0f},
          {1.0f, 0.0f, 0.0f},
          {1.0f, 0.0f, 0.0f},
          {1.0f, 0.0f, 0.0f}, // Right face
          {0.0f, 1.0f, 0.0f},
          {0.0f, 1.0f, 0.0f},
          {0.0f, 1.0f, 0.0f},
          {0.0f, 1.0f, 0.0f}, // Top face
          {0.0f, -1.0f, 0.0f},
          {0.0f, -1.0f, 0.0f},
          {0.0f, -1.0f, 0.0f},
          {0.0f, -1.0f, 0.0f} // Bottom face
      };
      constexpr Vec2 CUBE_TEXTURE_COORDS[] = {
          {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Front face
          {0.0f, 0.0f},
          {1.0f, 0.0f},
          {1.0f, 1.0f},
          {0.0f, 1.0f}, // Back face
          {0.0f, 0.0f},
          {1.0f, 0.0f},
          {1.0f, 1.0f},
          {0.0f, 1.0f}, // Left face
          {0.0f, 0.0f},
          {1.0f, 0.0f},
          {1.0f, 1.0f},
          {0.0f, 1.0f}, // Right face
          {0.0f, 0.0f},
          {1.0f, 0.0f},
          {1.0f, 1.0f},
          {0.0f, 1.0f}, // Top face
          {0.0f, 0.0f},
          {1.0f, 0.0f},
          {1.0f, 1.0f},
          {0.0f, 1.0f}, // Bottom face
      };

      List<uint32> indices = {
          // Front face
          0, 1, 2, 2, 3, 0,
          // Back face
          4, 5, 6, 6, 7, 4,
          // Left face
          8, 9, 10, 10, 11, 8,
          // Right face
          12, 13, 14, 14, 15, 12,
          // Top face
          16, 17, 18, 18, 19, 16,
          // Bottom face
          20, 21, 22, 22, 23, 20};

      List<Vertex> vertices;
      vertices.reserve(24);
      for (int i = 0; i < 24; i++)
      {
        vertices.push_back({CUBE_POSITIONS_VERTICES[i], CUBE_FLAT_NORMALS[i], color, CUBE_TEXTURE_COORDS[i]});
      }

      CalculateTangents(vertices, indices);

      auto mesh = CreateRef<Mesh>();
      mesh->Vertices = vertices;
      mesh->Indices = indices;

      return mesh;
    }
  };
}
