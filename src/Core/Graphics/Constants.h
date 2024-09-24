#pragma once

#include "Core.h"

#include "Maths/Maths.h"

namespace Krys
{
  // -------- BUFFER BINDINGS --------
  constexpr uint32 UNIFORM_BUFFER_BINDING_SHARED = 0;
  constexpr uint32 UNIFORM_BUFFER_BINDING_LIGHT = 1;
  // -------- BUFFER BINDINGS --------

  // --------- TEXTURE SLOTS ---------
  const int CUBEMAP_SLOTS = 2;

  /// @brief Reserved texture slots always take up the first slots for each sampler type.
  /// Get the actual texture unit index via `ActiveTextureUnit.GetReservedSlotIndex()`.
  const uint RESERVED_TEXTURE_SLOT_SHADOW_MAP_2D = 0;

  /// @brief Reserved texture slots always take up the first slots for each sampler type.
  /// Get the actual texture unit index via `ActiveTextureUnit.GetReservedSlotIndex()`.
  const uint RESERVED_TEXTURE_SLOT_SHADOW_CUBEMAP = 0;
  // --------- TEXTURE SLOTS ---------

  // ----------- LIGHTING ------------
  // TODO: we should be able to handle this dynamically.
  constexpr uint32 LIGHTING_MAX_DIRECTIONAL_LIGHTS = 5;
  constexpr uint32 LIGHTING_MAX_POINT_LIGHTS = 32;
  constexpr uint32 LIGHTING_MAX_SPOT_LIGHTS = 32;
  constexpr uint SHADOW_MAP_RESOLUTION = 1024;
  // ----------- LIGHTING ------------

  // ----------- RENDERER ------------
  constexpr uint RENDERER_MAX_TRIANGLES = 10000;
  constexpr uint RENDERER_MAX_QUADS = RENDERER_MAX_TRIANGLES / 2;
  constexpr uint RENDERER_MAX_VERTICES = RENDERER_MAX_QUADS * 4;
  constexpr uint RENDERER_MAX_INDICES = RENDERER_MAX_QUADS * 6;
  static Vec4 RENDERER_DEFAULT_OBJECT_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};
  // ----------- RENDERER ------------

  // ----------- DEFAULT VERTEX DATA  ------------
  /// @brief 4 floats per vertex, first 2 = position, last 2 = texture coords.
  static float SCREEN_QUAD_VERTICES[] = {
      -1.0f, 1.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      -1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f};

  constexpr Vec2 QUAD_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
  constexpr Vec3 QUAD_SURFACE_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
  constexpr Vec4 QUAD_LOCAL_SPACE_VERTICES[] = {{-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f}};

  constexpr Vec2 TRIANGLE_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {0.5f, 1.0f}, {1.0f, 0.0f}};
  constexpr Vec3 TRIANGLE_SURFACE_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
  constexpr Vec4 TRIANGLE_LOCAL_SPACE_VERTICES[] = {{0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}};

  // TODO: We don't have texture coords for cubes yet, we currently each face as if it were a 2d quad.
  constexpr Vec4 CUBE_LOCAL_SPACE_VERTICES[] = {
      // Front face
      {-0.5f, -0.5f, 0.5f, 1.0f}, // 0
      {0.5f, -0.5f, 0.5f, 1.0f},  // 1
      {0.5f, 0.5f, 0.5f, 1.0f},   // 2
      {-0.5f, 0.5f, 0.5f, 1.0f},  // 3

      // Back face
      {-0.5f, -0.5f, -0.5f, 1.0f}, // 4
      {0.5f, -0.5f, -0.5f, 1.0f},  // 5
      {0.5f, 0.5f, -0.5f, 1.0f},   // 6
      {-0.5f, 0.5f, -0.5f, 1.0f},  // 7

      // Left face
      {-0.5f, -0.5f, -0.5f, 1.0f}, // 8
      {-0.5f, -0.5f, 0.5f, 1.0f},  // 9
      {-0.5f, 0.5f, 0.5f, 1.0f},   // 10
      {-0.5f, 0.5f, -0.5f, 1.0f},  // 11

      // Right face
      {0.5f, -0.5f, -0.5f, 1.0f}, // 12
      {0.5f, -0.5f, 0.5f, 1.0f},  // 13
      {0.5f, 0.5f, 0.5f, 1.0f},   // 14
      {0.5f, 0.5f, -0.5f, 1.0f},  // 15

      // Top face
      {-0.5f, 0.5f, 0.5f, 1.0f},  // 16
      {0.5f, 0.5f, 0.5f, 1.0f},   // 17
      {0.5f, 0.5f, -0.5f, 1.0f},  // 18
      {-0.5f, 0.5f, -0.5f, 1.0f}, // 19

      // Bottom face
      {-0.5f, -0.5f, 0.5f, 1.0f}, // 20
      {0.5f, -0.5f, 0.5f, 1.0f},  // 21
      {0.5f, -0.5f, -0.5f, 1.0f}, // 22
      {-0.5f, -0.5f, -0.5f, 1.0f} // 23
  };
  constexpr Vec3 CUBE_SURFACE_NORMALS[] = {
      {0.0f, 0.0f, 1.0f}, // Front face
      {0.0f, 0.0f, 1.0f},
      {0.0f, 0.0f, 1.0f},
      {0.0f, 0.0f, 1.0f},

      {0.0f, 0.0f, -1.0f}, // Back face
      {0.0f, 0.0f, -1.0f},
      {0.0f, 0.0f, -1.0f},
      {0.0f, 0.0f, -1.0f},

      {-1.0f, 0.0f, 0.0f}, // Left face
      {-1.0f, 0.0f, 0.0f},
      {-1.0f, 0.0f, 0.0f},
      {-1.0f, 0.0f, 0.0f},

      {1.0f, 0.0f, 0.0f}, // Right face
      {1.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},

      {0.0f, 1.0f, 0.0f}, // Top face
      {0.0f, 1.0f, 0.0f},
      {0.0f, 1.0f, 0.0f},
      {0.0f, 1.0f, 0.0f},

      {0.0f, -1.0f, 0.0f}, // Bottom face
      {0.0f, -1.0f, 0.0f},
      {0.0f, -1.0f, 0.0f},
      {0.0f, -1.0f, 0.0f}};
  // ----------- DEFAULT VERTEX DATA  ------------
}