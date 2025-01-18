#pragma once

#include "Types.h"
#include "Core.h"
#include "IO/IO.h"

#include <sstream>
#include <regex>

namespace Krys::Gfx
{
  struct ShaderPreprocessorTemplateKeys
  {
    Nullable<int> SharedUniformBufferBinding,
     MaxDirectionalLights, MaxPointLights, MaxSpotLights;

    Map<string, string> ToMap() const noexcept
    {
      KRYS_ASSERT(SharedUniformBufferBinding, "SharedUniformBufferBinding is not set.", 0);
      KRYS_ASSERT(MaxDirectionalLights, "MaxDirectionalLights is not set.", 0);
      KRYS_ASSERT(MaxPointLights, "MaxPointLights is not set.", 0);
      KRYS_ASSERT(MaxSpotLights, "MaxSpotLights is not set.", 0);

      return {
          {"UNIFORM_BUFFER_BINDING_SHARED", std::to_string(*SharedUniformBufferBinding)},
          {"MAX_DIRECTIONAL_LIGHTS", std::to_string(*MaxDirectionalLights)},
          {"MAX_POINT_LIGHTS", std::to_string(*MaxPointLights)},
          {"MAX_SPOT_LIGHTS", std::to_string(*MaxSpotLights)},
      };
    }
  };

  const string SHADER_ROOT_DIR{"shaders/"};
  const string IMPORT_TOKEN{"#import"};

  ///@brief Resolves custom glsl tokens.
  class ShaderPreprocessor
  {
  private:
    static Nullable<Map<string, string>> TemplateKeys;

  public:
    static void SetTemplateKeys(const ShaderPreprocessorTemplateKeys &keys)
    {
      TemplateKeys = keys.ToMap();
    }

    /// @brief Resolves custom imports for shaders, including recursive imports.
    static string ResolveImports(const stringview &path, string &src)
    {
      KRYS_PERFORMANCE_TIMER("ResolveImports");
      KRYS_ASSERT(!src.empty(), "Source was empty", 0);
      KRYS_ASSERT(!path.empty(), "Path was empty", 0);

      Map<string, bool> imported;
      return ResolveImports(string(path), src, imported);
    }

    static string ResolveKeys(string &src)
    {
      KRYS_PERFORMANCE_TIMER("ResolveKeys");

      if (!TemplateKeys)
      {
        KRYS_INFO("No template keys set.");
        return src;
      }

      return FindAndReplaceKeys(src);
    }

  private:
    static string ResolveImports(const string &path, string &src, Map<string, bool> &imported)
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

    static string FindAndReplaceKeys(const string &src)
    {
      const std::regex pattern("\\$\\{([A-Za-z_0-9]+)\\}");
      std::string result;

      std::smatch match;
      std::string::const_iterator searchStart(src.cbegin());
      while (std::regex_search(searchStart, src.cend(), match, pattern))
      {
        result.append(searchStart, match.prefix().second);

        string fullMatch = match[0]; // The full match, e.g. "${TEMPLATE_KEY}"
        string key = match[1];       // The content inside the braces, e.g. "TEMPLATE_KEY"

        auto it = TemplateKeys->find(key);
        if (it == TemplateKeys->end()) // Append the original match if no replacement found, ensures an error is thrown.
        {
          KRYS_LOG("Unable to find a replacement for %s", key.c_str());
          result.append(fullMatch);
        }
        else
          result.append(it->second);

        searchStart = match.suffix().first;
      }

      return result.append(searchStart, src.cend());
    }
  };
}
