#include "IO.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <sstream>

namespace Krys::IO
{
  namespace fs = std::filesystem;

  std::vector<FileInfo> ListFiles(const string &directory, std::vector<string> extensions, bool recursive) noexcept
  {
    KRYS_PERFORMANCE_TIMER("ListFiles");
    KRYS_ASSERT(PathExists(directory), "Directory '%s' does not exist", directory.c_str());

    std::error_code error{};
    std::vector<FileInfo> entries{};

    const auto HasValidExtension = [&](string extension)
    {
      if (extensions.empty())
        return true;

      return std::any_of(extensions.begin(), extensions.end(), [&extension](string v)
                         { return v == extension; });
    };

    const auto ProcessEntry = [&](const fs::directory_entry &entry) -> void
    {
      string path{entry.path().string()};
      if (error)
      {
        KRYS_ASSERT(false, "Error iterating through directory '%s': %s", path.c_str(), error.message().c_str());
      }

      string extension = entry.path().extension().string();
      if (entry.is_regular_file(error) && HasValidExtension(extension))
      {
        string name{entry.path().stem().string()};
        entries.push_back({name, extension, path});
        KRYS_LOG("N: %s, E: %s, P: %s", name.c_str(), extension.c_str(), path.c_str());
      }
    };

    if (recursive)
      std::ranges::for_each(fs::recursive_directory_iterator{directory, error}, ProcessEntry);
    else
      std::ranges::for_each(fs::directory_iterator{directory, error}, ProcessEntry);

    return entries;
  }

  FileInfo GetPathInfo(const string &filepath) noexcept
  {
    KRYS_ASSERT(PathExists(filepath), "Path '%s' does not exist", filepath.c_str());

    auto fsPath = fs::path(filepath);
    string name{fsPath.stem().string()};
    string extension{fsPath.extension().string()};
    string path{fsPath.string()};

    FileInfo fileInfo{name, extension, path};
    fileInfo.IsDirectory = fs::directory_entry(fsPath).is_directory();

    return fileInfo;
  }

  bool PathExists(const string &path) noexcept
  {
    std::error_code error{};
    return fs::exists(path, error);
  }

  bool IsDirectory(const string &path) noexcept
  {
    KRYS_ASSERT(PathExists(path), "Directory '%s' does not exist", path.c_str());

    std::error_code error{};
    return fs::directory_entry(path, error).is_directory(error);
  }

  bool IsFile(const string &path) noexcept
  {
    KRYS_ASSERT(PathExists(path), "Directory '%s' does not exist", path.c_str());

    std::error_code error{};
    return fs::directory_entry(path, error).is_regular_file(error);
  }

  string ReadFileText(const string &path) noexcept
  {
    KRYS_ASSERT(PathExists(path), "File '%s' does not exist", path.c_str());

    std::ifstream fileStream(path);
    if (!fileStream.is_open())
    {
      KRYS_LOG("Unable to open %s. Are you in the right directory?", path.c_str());
      return "";
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    fileStream.close();

    return buffer.str();
  }

  bool WriteFileText(const string &path, const string &content) noexcept
  {
    KRYS_ASSERT(PathExists(path), "File '%s' does not exist", path.c_str());

    std::ofstream fileStream(path);
    if (!fileStream.is_open())
    {
      KRYS_LOG("Unable to open file: %s", path.c_str());
      return false;
    }

    fileStream << content;
    return true;
  }
}