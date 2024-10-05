#pragma once

#include "Core.h"
#include "IO/IO.h"
#include "IO/BinaryFileReader.h"
#include "Assets/Importer.h"

#include <document.h>

namespace Krys::Assets
{
  typedef rapidjson::Document JsonDocument;
  typedef rapidjson::Value JsonElement;
  const Map<string, int> ComponentCount = {
      {"SCALAR", 1},
      {"VEC2", 2},
      {"VEC3", 3},
      {"VEC4", 4},
      {"MAT2", 4},
      {"MAT3", 9},
      {"MAT4", 16},
  };

  const uint32 GLTF_ASCII_TOKEN = Endian::ToSystemEndian(0x46546C67, Endian::Type::Little);
  const uint32 CHUNK_TYPE_JSON = Endian::ToSystemEndian(0x4E4F534A, Endian::Type::Little);
  const uint32 CHUNK_TYPE_BINARY = Endian::ToSystemEndian(0x004E4942, Endian::Type::Little);
  constexpr bool CONVERT_TO_SYSTEM_ENDIAN = !Endian::IsLittleEndian(); // If false, slightly optimises the call to `.Read<T>()`.

  enum class ComponentType
  {
    BYTE = 5120,
    U_BYTE = 5121,
    SHORT = 5122,
    U_SHORT = 5123,
    U_INT = 5125,
    FLOAT = 5126,
  };

  enum class BufferTarget
  {
    ARRAY_BUFFER = 34962,
    ELEMENT_ARRAY_BUFFER = 34963,
  };

  class BinaryGLTF : public Importer
  {
  private:
    IO::BinaryFileReader FileReader;
    JsonDocument Document;
    JsonElement Nodes, Meshes, Accessors, BufferViews;
    List<byte> BinaryChunk;

  public:
    BinaryGLTF(const stringview &path) noexcept
        : Importer(path), FileReader(path, Endian::Type::Little), BinaryChunk({})
    {
      Result.Scene.ColumnMajor = true;
    }

    void Parse() noexcept override
    {
#define RETURN_IF_ERROR() \
  if (!Result)            \
  {                       \
    return;               \
  }
      KRYS_PERFORMANCE_TIMER("Binary GLTF - Parse");
      FileReader.OpenStream();

      auto leftToProcess = ParseHeader();
      RETURN_IF_ERROR();
      leftToProcess = ParseJsonIntoDocument(leftToProcess);
      RETURN_IF_ERROR();
      leftToProcess = ParseBinaryBuffer(leftToProcess);
      RETURN_IF_ERROR();
      if (leftToProcess != 0)
      {
        Result.SetError(AssetImportStatus::InvalidFileFormat, "Expected end of file but there is still data to process.");
        return;
      }

      uint32 defaultSceneIndex = 0;
      if (Document.HasMember("scene"))
        defaultSceneIndex = Document["scene"].GetUint();
      const auto &scene = Document["scenes"][defaultSceneIndex];

      if (!scene.HasMember("nodes"))
        Result.SetError(AssetImportStatus::InvalidFileFormat, "No nodes to process for the scene.");
      RETURN_IF_ERROR();
      KRYS_LOG("Loading scene '%s'...", scene.HasMember("name") ? scene["name"].GetString() : "Unknown");

      for (auto &sceneNode : scene["nodes"].GetArray())
      {
        auto rootNodeIndex = sceneNode.GetInt();
        ProcessNode(Nodes[rootNodeIndex].GetObject());
      }
    }

  private:
#pragma region Parsing

    uint32 ParseHeader() noexcept
    {
      const uint32 HEADER_SIZE_IN_BYTES = 12;
      KRYS_LOG("Binary GLTF - Parsing header...");

      auto magic = FileReader.Read<uint32, CONVERT_TO_SYSTEM_ENDIAN>();
      if (magic != GLTF_ASCII_TOKEN)
      {
        Result.SetError(AssetImportStatus::InvalidFileFormat, "Missing GLTF ASCII Token at start of file.");
      }

      auto version = FileReader.Read<uint32, CONVERT_TO_SYSTEM_ENDIAN>();
      KRYS_LOG("Binary GLTF Version: %d", version);

      auto length = FileReader.Read<uint32, CONVERT_TO_SYSTEM_ENDIAN>();
      length -= HEADER_SIZE_IN_BYTES;

      KRYS_LOG("Binary GLTF - File size: %d", length);

      return length;
    }

    uint32 ParseJsonIntoDocument(uint32 length) noexcept
    {
      auto chunkLength = FileReader.Read<uint32, CONVERT_TO_SYSTEM_ENDIAN>();
      auto chunkType = FileReader.Read<uint32, CONVERT_TO_SYSTEM_ENDIAN>();
      length -= sizeof(uint32) * 2;
      length -= chunkLength;

      if (chunkType != CHUNK_TYPE_JSON)
      {
        Result.SetError(AssetImportStatus::InvalidFileFormat, "Expected JSON.");
        return length;
      }

      auto json = FileReader.ReadJson(chunkLength);

      Document.Parse(json.c_str());
      // TODO: we can use FindMember instead of HasMember to halve the lookups if needed.
      if (!Document.IsObject())
        Result.SetError(AssetImportStatus::InvalidFileFormat, "Malformed or invalid JSON.");
      else if (!Document.HasMember("scenes"))
        Result.SetError(AssetImportStatus::InvalidFileFormat, "No scenes.");
      else if (!Document.HasMember("nodes"))
        Result.SetError(AssetImportStatus::InvalidFileFormat, "No nodes.");
      else if (!Document.HasMember("meshes"))
        Result.SetError(AssetImportStatus::InvalidFileFormat, "No meshes.");
      else if (!Document.HasMember("accessors"))
        Result.SetError(AssetImportStatus::InvalidFileFormat, "No accessors.");
      else if (!Document.HasMember("buffers"))
        Result.SetError(AssetImportStatus::InvalidFileFormat, "No buffers.");
      else if (!Document.HasMember("bufferViews"))
        Result.SetError(AssetImportStatus::InvalidFileFormat, "No buffer views.");

      Meshes = Document["meshes"];
      Nodes = Document["nodes"];
      Accessors = Document["accessors"];
      BufferViews = Document["bufferViews"];

      return length;
    }

    uint32 ParseBinaryBuffer(uint32 length) noexcept
    {
      if (length == 0)
        return {};

      auto chunkLength = FileReader.Read<uint32, CONVERT_TO_SYSTEM_ENDIAN>();
      auto chunkType = FileReader.Read<uint32, CONVERT_TO_SYSTEM_ENDIAN>();
      length -= sizeof(uint32) * 2;
      length -= chunkLength;

      if (chunkType != CHUNK_TYPE_BINARY)
      {
        Result.SetError(AssetImportStatus::InvalidFileFormat, "Expected binary.");
        return length;
      }

      BinaryChunk = FileReader.ReadBytes(chunkLength);

      return length;
    }

#pragma endregion Parsing
    void ProcessNode(const JsonElement &node) noexcept
    {
      auto meshItr = node.FindMember("mesh");
      if (meshItr != node.MemberEnd())
      {
        int meshIndex = meshItr->value.GetInt();
        ProcessMesh(Meshes[meshIndex]);
      }

      auto childrenItr = node.FindMember("children");
      if (childrenItr != node.MemberEnd())
      {
        const auto &children = childrenItr->value.GetArray();
        for (const auto &childNodeIndex : children)
          ProcessNode(Nodes[childNodeIndex.GetInt()].GetObject());
      }
    }

    void ProcessMesh(const JsonElement &mesh) noexcept
    {
      if (!mesh.HasMember("primitives"))
      {
        Result.SetError(AssetImportStatus::InvalidFileFormat, "Mesh has no primitives.");
        return;
      }
      KRYS_LOG("Loading mesh '%s'...", mesh.HasMember("name") ? mesh["name"].GetString() : "Unknown");

      for (const auto &primitive : mesh["primitives"].GetArray())
      {
        if (!primitive.HasMember("attributes"))
        {
          Result.SetError(AssetImportStatus::InvalidFileFormat, "Primitive has no attributes.");
          return;
        }

        for (const auto &attribute : primitive["attributes"].GetObject())
        {
          string name = {attribute.name.GetString()};
          if (name == "POSITION")
          {
          }
        }
      }
    }
  };
}
