#pragma once

#include "Core.h"
#include "Maths/Maths.h"
#include "Graphics/Graphics.h"

namespace Krys::Assets
{
  // NOTE: meshes usually have nested primitives but we unpack them into a flat array of meshes.
  // It's important to be aware that SOME meshes could've been grouped together.
  struct IntermediateMesh
  {
    List<uint32> Indices;
    List<Vec3> Positions;
    List<Vec3> Normals;
    List<Vec2> TextureCoords;
    List<Vec4> Colors;
    PrimitiveType PrimitiveType = PrimitiveType::Triangles;
  };

  enum class AssetImportStatus
  {
    Success = 0,
    InvalidFileFormat,
    UnsupportedFormat
  };

  struct AssetImportResult
  {
    AssetImportStatus Status;
    string ErrorMessage{};
    Ref<Model> ImportedModel{};

    explicit operator bool() const noexcept
    {
      return Status == AssetImportStatus::Success;
    }

    void SetError(AssetImportStatus status, const string &error) noexcept
    {
      Status = status;
      ErrorMessage = error;
    }
  };
}
