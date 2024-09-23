#pragma once

#include "Core.h"

#include "IO/IO.h"

namespace Krys
{
  /// @brief Resolves custom imports for shaders.
  class ShaderPreprocessor
  {
  private:
    stringview _path;
    string _src;

  public:
    ShaderPreprocessor(const stringview &path)
        : _path(path), _src(IO::ReadFileText(_path))
    {
      KRYS_LOG("ShaderPreprocessor created for path %s", _path.data());
    }

    stringview ResolveImports()
    {
      KRYS_ASSERT(!_src.empty(), "Source was empty", 0);
      KRYS_PERFORMANCE_TIMER("ResolveImports");

      auto importStart = _src.find("#import");
      if (importStart == _src.npos)
        return _src;

      while (importStart != _src.npos)
      {
        auto importEnd = _src.find(";", importStart);
        KRYS_ASSERT(importEnd != _src.npos, "End of import statement was not found or was in an unexpected place.", 0);

        auto importStatement = _src.substr(importStart, importEnd - importStart + 1); // Include the semicolon
        KRYS_LOG("Found import statement: %s", importStatement.data());

        auto pathStart = importStatement.find("\"");
        auto pathEnd = importStatement.find("\"", pathStart + 1);
        KRYS_ASSERT(pathStart != importStatement.npos && pathEnd != importStatement.npos, "Import path not found", 0);

        auto importPath = importStatement.substr(pathStart + 1, pathEnd - pathStart - 1); // Extract the file path
        KRYS_LOG("Resolving import: %s", importPath.data());

        const string SHADER_ROOT_DIR{"shaders/"};
        string importSrc = IO::ReadFileText(SHADER_ROOT_DIR + importPath);
        _src.replace(importStart, importEnd - importStart + 1, importSrc);

        importStart = _src.find("#import", importEnd);
      }

      return _src;
    }
  };
}