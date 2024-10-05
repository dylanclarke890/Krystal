#pragma once

#include "Core.h"

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
  NO_DISCARD List<FileInfo> ListFiles(const stringview &directory, List<stringview> extensions = {}, bool recursive = false) noexcept;

  /// @brief Get information about a path
  /// @param path The path to check.
  /// @return Info about the path, such as name, extension and whether it is a directory.
  NO_DISCARD FileInfo GetPathInfo(const stringview &path) noexcept;

  /// @brief Get the extension of a path.
  /// @param path The path to check.
  /// @return Extension of the path.
  NO_DISCARD const string GetExtension(const stringview &path) noexcept;

  /// @brief Check whether a path exists.
  /// @param path The path to check.
  /// @return True if the path exists.
  NO_DISCARD bool PathExists(const stringview &path) noexcept;

  /// @brief Check whether a path is a directory.
  /// @param path The path to check.
  /// @return True if the path is a directory.
  NO_DISCARD bool IsDirectory(const stringview &path) noexcept;

  /// @brief Check whether a path is a regular file.
  /// @param path The path to check.
  /// @return True if the path is a regular file.
  NO_DISCARD bool IsFile(const stringview &path) noexcept;

  /// @brief Get the contents of a file as text.
  /// @param path The path to the file to read.
  /// @return The contents of the file.
  NO_DISCARD string ReadFileText(const stringview &path) noexcept;

  /// @brief Write text to a file.
  /// @param path The path to check.
  /// @return True if the write was successful.
  bool WriteFileText(const stringview &path, const stringview &content) noexcept;
}