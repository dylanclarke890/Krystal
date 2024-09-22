#pragma once

#include "Core.h"
#include <vector>

namespace Krys::IO
{
  struct FileInfo
  {
    string Name;
    string Extension;
    string Path;
    bool IsDirectory = false;
  };

  /// @brief Get the list of regular files for a directory.
  /// @param directory The directory to search.
  /// @param recursive If true will also search subdirectories.
  /// @param extensions Optional list of extensions to filter by.
  /// @return The list of regular files that match the search criteria.
  std::vector<FileInfo> ListFiles(const string &directory, std::vector<string> extensions = {}, bool recursive = false);

  FileInfo GetFileInfo(const string &path);

  bool Exists(const string &path);

  string ReadFileText(const string &path);

  bool WriteFileText(const string &path, const string &content);
}