#pragma once

#include "Core.h"

#include "IO/IO.h"
#include "Assets/Importers/BinaryGLTF.h"

namespace Krys::Assets
{
  class Factory
  {
  public:
    /// @brief Get an importer instance, based on the file extension of the path provided.
    /// @param path Path to a resource.
    /// @return An importer instance that can parse the file.
    static Unique<Importer> CreateImporter(const stringview &path) noexcept
    {
      const string extension = IO::GetExtension(path);

      if (extension == ".glb")
        return CreateUnique<BinaryGLTF>(path);

      KRYS_ASSERT(false, "Unsupported extension! %s", extension.c_str());
      return nullptr;
    }
  };
}
