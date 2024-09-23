#pragma once

#include "Core.h"
#include "IO/IO.h"
#include <unordered_map>
#include <sstream>

namespace Krys
{
  const string SHADER_ROOT_DIR{"shaders/"};
  const string IMPORT_TOKEN{"#import"};

  ///@brief Resolves custom glsl tokens.
  class ShaderPreprocessor
  {
  public:
    /// @brief Resolves custom imports for shaders, including recursive imports.
    static string ResolveImports(const stringview &path, string &src)
    {
      KRYS_PERFORMANCE_TIMER("ResolveImports");
      KRYS_ASSERT(!src.empty(), "Source was empty", 0);
      KRYS_ASSERT(!path.empty(), "Path was empty", 0);

      std::unordered_map<string, bool> imported;
      return ResolveImports(string(path), src, imported);
    }

  private:
    /// @brief Resolves imports recursively, ensuring that files are not imported multiple times.
    static string ResolveImports(const string &path, string &src, std::unordered_map<string, bool> &imported)
    {
      if (imported.find(path) != imported.end())
      {
        KRYS_LOG("File '%s' already imported, skipping.", path.data());
        return "";
      }

      imported[path] = true;

      auto importStart = src.find(IMPORT_TOKEN);
      while (importStart != src.npos)
      {
        auto importEnd = src.find(";", importStart);
        KRYS_ASSERT(importEnd != src.npos, "End of import statement was not found", 0);

        auto importStatement = src.substr(importStart, importEnd - importStart + 1); // Include the semicolon
        KRYS_LOG("Found import statement: %s", importStatement.c_str());

        auto pathStart = importStatement.find("\"");
        auto pathEnd = importStatement.find("\"", pathStart + 1);
        KRYS_ASSERT(pathStart != importStatement.npos && pathEnd != importStatement.npos, "Import path not found", 0);

        auto importPath = importStatement.substr(pathStart + 1, pathEnd - pathStart - 1);
        string fullImportPath = SHADER_ROOT_DIR + importPath;
        KRYS_LOG("Resolving import: %s", fullImportPath.c_str());

        string importSrc = IO::ReadFileText(fullImportPath);
        KRYS_ASSERT(!importSrc.empty(), "Failed to read imported file: %s", fullImportPath.c_str());

        importSrc = ResolveImports(importPath, importSrc, imported);
        src.replace(importStart, importEnd - importStart + 1, importSrc);

        importStart = src.find(IMPORT_TOKEN, importStart + importSrc.length());
      }

      return src;
    }
  };
}
