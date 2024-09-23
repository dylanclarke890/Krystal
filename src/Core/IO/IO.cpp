#include "IO.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <sstream>

namespace Krys::IO
{
  namespace fs = std::filesystem;

  std::vector<FileInfo> ListFiles(const stringview &directory, std::vector<stringview> extensions, bool recursive) noexcept
  {
    KRYS_PERFORMANCE_TIMER("ListFiles");
    KRYS_ASSERT(PathExists(directory), "Directory '%s' does not exist", directory.data());

    std::error_code error{};
    std::vector<FileInfo> entries{};

    const auto HasValidExtension = [&](stringview extension)
    {
      if (extensions.empty())
        return true;

      return std::any_of(extensions.begin(), extensions.end(), [&extension](stringview v)
                         { return v == extension; });
    };

    const auto ProcessEntry = [&](const fs::directory_entry &entry) -> void
    {
      stringview path{entry.path().string()};
      if (error)
      {
        KRYS_ASSERT(false, "Error iterating through directory '%s': %s", path.data(), error.message().c_str());
      }

      stringview extension{entry.path().extension().string()};
      if (entry.is_regular_file(error) && HasValidExtension(extension))
      {
        stringview name{entry.path().stem().string()};
        entries.push_back({name, extension, path});
        KRYS_LOG("N: %s, E: %s, P: %s", name.data(), extension.data(), path.data());
      }
    };

    if (recursive)
      std::ranges::for_each(fs::recursive_directory_iterator{directory, error}, ProcessEntry);
    else
      std::ranges::for_each(fs::directory_iterator{directory, error}, ProcessEntry);

    return entries;
  }

  FileInfo GetPathInfo(const stringview &filepath) noexcept
  {
    KRYS_ASSERT(PathExists(filepath), "Path '%s' does not exist", filepath.data());
    KRYS_PERFORMANCE_TIMER("GetPathInfo");

    auto fsPath = fs::path(filepath);
    stringview name{fsPath.stem().string()};
    stringview extension{fsPath.extension().string()};
    stringview path{fsPath.string()};

    FileInfo fileInfo{name, extension, path};
    fileInfo.IsDirectory = fs::directory_entry(fsPath).is_directory();

    return fileInfo;
  }

  bool PathExists(const stringview &path) noexcept
  {
    KRYS_PERFORMANCE_TIMER("PathExists");

    std::error_code error{};
    return fs::exists(path, error);
  }

  bool IsDirectory(const stringview &path) noexcept
  {
    KRYS_ASSERT(PathExists(path), "Directory '%s' does not exist", path.data());
    KRYS_PERFORMANCE_TIMER("IsDirectory");

    std::error_code error{};
    return fs::directory_entry(path, error).is_directory(error);
  }

  bool IsFile(const stringview &path) noexcept
  {
    KRYS_ASSERT(PathExists(path), "Directory '%s' does not exist", path.data());
    KRYS_PERFORMANCE_TIMER("IsFile");

    std::error_code error{};
    return fs::directory_entry(path, error).is_regular_file(error);
  }

  string ReadFileText(const stringview &path) noexcept
  {
    KRYS_ASSERT(PathExists(path), "File '%s' does not exist", path.data());
    KRYS_PERFORMANCE_TIMER("ReadFileText");

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
    KRYS_PERFORMANCE_TIMER("WriteFileText");

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