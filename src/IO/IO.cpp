#include "IO/IO.hpp"
#include "Core/Debug/Macros.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <sstream>

namespace Krys::IO
{
  namespace fs = std::filesystem;

  List<FileInfo> ListFiles(const stringview &directory, List<stringview> extensions, bool recursive) noexcept
  {
    KRYS_SCOPED_PROFILER("ListFiles");
    KRYS_ASSERT(PathExists(directory), "Directory '%s' does not exist", directory.data());

    std::error_code error {};
    List<FileInfo> entries {};

    const auto HasValidExtension = [&](stringview extension) -> bool
    {
      if (extensions.empty())
        return true;

      return std::any_of(extensions.begin(), extensions.end(),
                         [&extension](stringview v) { return v == extension; });
    };

    const auto ProcessEntry = [&](const fs::directory_entry &entry) -> void
    {
      string path {entry.path().string()};
      if (error)
      {
        KRYS_ASSERT(false, "Error iterating through directory '%s': %s", path.data(),
                    error.message().c_str());
      }

      string extension {entry.path().extension().string()};
      if (entry.is_regular_file(error) && HasValidExtension(extension))
      {
        string name {entry.path().stem().string()};
        entries.push_back({name, extension, path});
        KRYS_LOG("N: %s, E: %s, P: %s", name.data(), extension.data(), path.data());
      }
    };

    if (recursive)
      std::ranges::for_each(fs::recursive_directory_iterator {directory, error}, ProcessEntry);
    else
      std::ranges::for_each(fs::directory_iterator {directory, error}, ProcessEntry);

    return entries;
  }

  FileInfo GetPathInfo(const stringview &filepath) noexcept
  {
    KRYS_ASSERT(PathExists(filepath), "Path '%s' does not exist", filepath.data());
    KRYS_SCOPED_PROFILER("GetPathInfo");

    auto fsPath = fs::path(filepath);
    FileInfo fileInfo {fsPath.stem().string(), fsPath.extension().string(), fsPath.string()};
    fileInfo.IsDirectory = fs::directory_entry(fsPath).is_directory();

    return fileInfo;
  }

  const string GetExtension(const stringview &filepath) noexcept
  {
    KRYS_ASSERT(PathExists(filepath), "Path '%s' does not exist", filepath.data());
    return fs::path(filepath).extension().string();
  }

  bool PathExists(const stringview &path) noexcept
  {
    KRYS_SCOPED_PROFILER("PathExists");

    std::error_code error {};
    return fs::exists(path, error);
  }

  bool IsDirectory(const stringview &path) noexcept
  {
    KRYS_ASSERT(PathExists(path), "Directory '%s' does not exist", path.data());
    KRYS_SCOPED_PROFILER("IsDirectory");

    std::error_code error {};
    return fs::directory_entry(path, error).is_directory(error);
  }

  bool IsFile(const stringview &path) noexcept
  {
    KRYS_ASSERT(PathExists(path), "Directory '%s' does not exist", path.data());
    KRYS_SCOPED_PROFILER("IsFile");

    std::error_code error {};
    return fs::directory_entry(path, error).is_regular_file(error);
  }

  string ReadFileText(const stringview &path) noexcept
  {
    KRYS_ASSERT(PathExists(path), "File '%s' does not exist", path.data());
    KRYS_SCOPED_PROFILER("ReadFileText");

    std::ifstream fileStream(path.data());
    if (!fileStream.is_open())
    {
      KRYS_LOG("Unable to open %s. Are you in the right directory?", path.data());
      return "";
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    fileStream.close();

    return buffer.str();
  }

  bool WriteFileText(const stringview &path, const stringview &content) noexcept
  {
    KRYS_ASSERT(PathExists(path), "File '%s' does not exist", path.data());
    KRYS_SCOPED_PROFILER("WriteFileText");

    std::ofstream fileStream(path.data());
    if (!fileStream.is_open())
    {
      KRYS_LOG("Unable to open file: %s", path.data());
      return false;
    }

    fileStream << content;
    return true;
  }
}