#pragma once

#include "Core.h"

#include "IO/IO.h"
#include "Maths/Maths.h"

namespace Krys::Assets
{
  enum class AssetImportStatus
  {
    Success = 0,
    InvalidFileFormat,
  };

  struct AssetScene
  {
    string Path;
    uint32 SceneIndex;
    bool ColumnMajor;
  };

  struct AssetMesh
  {
    List<Vec3> Positions;
    List<Vec3> Normals;
    List<Vec2> TextureCoords;
    List<uint32> Indices;
  };

  struct AssetImportResult
  {
    AssetImportStatus Status;
    string ErrorMessage{};
    AssetScene Scene{};

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

  class Importer
  {
  protected:
    stringview Path;
    AssetImportResult Result;

  public:
    Importer(const stringview &path) noexcept
     : Path(path), Result({}) { Result.Scene.Path = {path.data()}; }
    virtual ~Importer() = default;

    virtual void Parse() noexcept = 0;
  };
}
