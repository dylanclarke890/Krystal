#pragma once

#include "Core.h"

namespace Krys::Assets
{
  enum class AssetImportStatus
  {
    Success = 0,
    InvalidFileFormat,
    UnsupportedFormat
  };

  struct AssetImportResult
  {
    AssetImportStatus Status = AssetImportStatus::Success;
    string ErrorMessage{};

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
    stringview _path;
    AssetImportResult _result;

  public:
    Importer(const stringview &path) noexcept
        : _path(path), _result({}) {}

    virtual ~Importer() = default;
    virtual AssetImportResult &Parse() noexcept = 0;
    const AssetImportResult &GetResult() const noexcept { return _result; }
    const stringview &GetPath() const noexcept { return _path; }
  };
}
