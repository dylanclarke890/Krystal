#pragma once

#include "Core.h"
#include "IO/IO.h"
#include "IO/BinaryFileReader.h"
#include "Graphics/Assets/Importer.h"
#include "DataProcessing/Normalization.h"

#include <document.h>

namespace Krys::Assets
{
  class BinaryGLTF : public Importer
  {
    typedef rapidjson::Document JsonDocument;
    typedef rapidjson::Value JsonElement;

    const uint32 GLTF_ASCII_TOKEN = Endian::ToSystemEndian<uint32, Endian::Type::Little>(0x46546C67);
    const uint32 CHUNK_TYPE_JSON = Endian::ToSystemEndian<uint32, Endian::Type::Little>(0x4E4F534A);
    const uint32 CHUNK_TYPE_BINARY = Endian::ToSystemEndian<uint32, Endian::Type::Little>(0x004E4942);

    enum class ComponentType
    {
      BYTE = 5120,
      UNSIGNED_BYTE = 5121,
      SHORT = 5122,
      UNSIGNED_SHORT = 5123,
      UNSIGNED_INT = 5125,
      FLOAT = 5126
    };

    const Map<ComponentType, int> ComponentTypeToSizeInBytes = {
        {ComponentType::BYTE, 1},
        {ComponentType::UNSIGNED_BYTE, 1},
        {ComponentType::SHORT, 2},
        {ComponentType::UNSIGNED_SHORT, 2},
        {ComponentType::UNSIGNED_INT, 4},
        {ComponentType::FLOAT, 4},
    };

    const Map<string, int> DataTypeToComponentCount = {
        {"SCALAR", 1},
        {"VEC2", 2},
        {"VEC3", 3},
        {"VEC4", 4},
        {"MAT2", 4},
        {"MAT3", 9},
        {"MAT4", 16},
    };

    struct AccessorResult
    {
      ComponentType ComponentType;
      int ComponentCount;
      string DataType;
      List<byte> RawBytes;
      bool Normalised;
    };

#define RETURN_IF_ERROR() \
  if (!Result)            \
  {                       \
    return;               \
  }

  private:
    IO::BinaryFileReader<Endian::Type::Little, Endian::Type::System> FileReader;
    JsonDocument Document;
    JsonElement Nodes, Meshes, Accessors, BufferViews;
    List<byte> BinaryChunk;

  public:
    BinaryGLTF(const stringview &path) noexcept
        : Importer(path), FileReader(path), BinaryChunk({})
    {
    }

    void Parse() noexcept override
    {
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

      auto sceneIndex = 0;
      if (Document.HasMember("scene"))
        sceneIndex = Document["scene"].GetUint();
      const auto &scene = Document["scenes"][sceneIndex];

      if (!scene.HasMember("nodes"))
        Result.SetError(AssetImportStatus::InvalidFileFormat, "No nodes to process for the scene.");
      RETURN_IF_ERROR();
      KRYS_LOG("Loading scene '%s'...", scene.HasMember("name") ? scene["name"].GetString() : "Unknown");

      for (auto &sceneNode : scene["nodes"].GetArray())
      {
        auto rootNodeIndex = sceneNode.GetInt();
        ProcessNode(Nodes[rootNodeIndex].GetObj());
      }

      ProcessIntermediateMeshes();
    }

  private:
#pragma region Parsing

    uint32 ParseHeader() noexcept
    {
      const uint32 HEADER_SIZE_IN_BYTES = 12;
      KRYS_LOG("Binary GLTF - Parsing header...");

      auto magic = FileReader.Read<uint32>();
      if (magic != GLTF_ASCII_TOKEN)
      {
        Result.SetError(AssetImportStatus::InvalidFileFormat, "Missing GLTF ASCII Token at start of file.");
      }

      auto version = FileReader.Read<uint32>();
      KRYS_LOG("Binary GLTF Version: %d", version);

      auto length = FileReader.Read<uint32>();
      length -= HEADER_SIZE_IN_BYTES;

      KRYS_LOG("Binary GLTF - File size: %d", length);

      return length;
    }

    uint32 ParseJsonIntoDocument(uint32 length) noexcept
    {
      auto chunkLength = FileReader.Read<uint32>();
      auto chunkType = FileReader.Read<uint32>();
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

      auto chunkLength = FileReader.Read<uint32>();
      auto chunkType = FileReader.Read<uint32>();
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

#pragma region Process JSON

    void ProcessNode(const JsonElement &node) noexcept
    {
      auto meshItr = node.FindMember("mesh");
      if (meshItr != node.MemberEnd())
      {
        int meshIndex = meshItr->value.GetInt();
        ProcessMesh(Meshes[meshIndex]);
      }
      RETURN_IF_ERROR();

      auto childrenItr = node.FindMember("children");
      if (childrenItr != node.MemberEnd())
      {
        const auto &children = childrenItr->value.GetArray();
        for (const auto &childNodeIndex : children)
        {
          ProcessNode(Nodes[childNodeIndex.GetInt()].GetObj());
          RETURN_IF_ERROR();
        }
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

        auto i = IntermediateMeshes.size();
        IntermediateMeshes.push_back({});

        if (primitive.HasMember("mode"))
          // NOTE: we can only do this because the order of modes in PrimitiveType matches GLTF's spec.
          IntermediateMeshes[i].PrimitiveType = static_cast<PrimitiveType>(primitive["mode"].GetInt());

        for (const auto &attribute : primitive["attributes"].GetObj())
        {
          RETURN_IF_ERROR();

          string name = {attribute.name.GetString()};
          int accessorIndex = attribute.value.GetInt();
          auto accessorResult = ProcessAccessor(Accessors[accessorIndex]);

          if (name == "POSITION")
          {
            ProcessPosition(accessorResult, IntermediateMeshes[i]);
            continue;
          }

          if (name == "NORMAL")
          {
            ProcessNormals(accessorResult, IntermediateMeshes[i]);
            continue;
          }

          if (name == "TEXCOORD_0")
          {
            ProcessTextureCoords(accessorResult, IntermediateMeshes[i]);
            continue;
          }

          if (name == "COLOR_0")
          {
            ProcessColors(accessorResult, IntermediateMeshes[i]);
            continue;
          }
        }

        if (primitive.HasMember("indices"))
        {
          int accessorIndex = primitive["indices"].GetInt();
          auto accessorResult = ProcessAccessor(Accessors[accessorIndex]);
          ProcessIndices(accessorResult, IntermediateMeshes[i]);
        }
      }
    }

    AccessorResult ProcessAccessor(const JsonElement &accessor) noexcept
    {
      string type = {accessor["type"].GetString()};
      int count = accessor["count"].GetInt();
      ComponentType componentType = static_cast<ComponentType>(accessor["componentType"].GetInt());
      int componentSize = ComponentTypeToSizeInBytes.find(componentType)->second;
      int componentCount = DataTypeToComponentCount.find(type)->second;
      int elementSizeInBytes = componentSize * componentCount;

      AccessorResult result;
      result.DataType = type;
      result.ComponentType = componentType;
      result.ComponentCount = componentCount;
      result.Normalised = accessor.HasMember("normalised") ? accessor["normalised"].GetBool() : false;

      if (accessor.HasMember("bufferView"))
      {
        int bufferViewIndex = accessor["bufferView"].GetInt();
        int offset = accessor.HasMember("byteOffset") ? accessor["byteOffset"].GetInt() : 0;
        result.RawBytes = RetrieveBytesFromBufferView(BufferViews[bufferViewIndex], offset, elementSizeInBytes, count);
      }
      else
      {
        // Zero initialise if we don't have a bufferView, as per the spec.
        result.RawBytes.resize(elementSizeInBytes * count, static_cast<byte>(0));
      }

      return result;
    }

    List<byte> RetrieveBytesFromBufferView(const JsonElement &bufferView, int accessorByteOffset, int elementSize, int count) noexcept
    {
      int totalBytes = elementSize * count;
      int byteOffset = bufferView.HasMember("byteOffset") ? bufferView["byteOffset"].GetInt() : 0;
      byteOffset += accessorByteOffset;

      if (!bufferView.HasMember("byteStride"))
        return List<byte>(BinaryChunk.begin() + byteOffset, BinaryChunk.begin() + byteOffset + totalBytes);

      List<byte> bytes;
      bytes.reserve(totalBytes);
      for (size_t i = 0; i < count; i++)
      {
        auto offset = BinaryChunk.begin() + byteOffset + (count * elementSize);
        bytes.insert(bytes.end(), offset, offset + elementSize);
      }

      return bytes;
    }

#pragma endregion Process JSON

#pragma region Process Attributes

    void ProcessPosition(AccessorResult &accessorResult, IntermediateMesh &intermediateMesh)
    {
      auto floats = Bytes::AsNumericArray<float, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);
      intermediateMesh.Positions.resize(floats.size() / 3);

      for (int i = 0; i < floats.size(); i += 3)
        intermediateMesh.Positions[i / 3] = {floats[i], floats[i + 1], floats[i + 2]};
    }

    void ProcessNormals(AccessorResult &accessorResult, IntermediateMesh &intermediateMesh)
    {
      List<float> floats = Bytes::AsNumericArray<float, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);
      intermediateMesh.Normals.resize(floats.size() / 3);

      for (int i = 0; i < floats.size(); i += 3)
        intermediateMesh.Normals[i / 3] = {floats[i], floats[i + 1], floats[i + 2]};
    }

    void ProcessTextureCoords(AccessorResult &accessorResult, IntermediateMesh &intermediateMesh)
    {
      switch (accessorResult.ComponentType)
      {
      case ComponentType::FLOAT:
      {
        List<float> floats = Bytes::AsNumericArray<float, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);
        intermediateMesh.TextureCoords.resize(floats.size() / 2);

        for (int i = 0; i < floats.size(); i += 2)
          intermediateMesh.TextureCoords[i / 2] = {floats[i], floats[i + 1]};
        break;
      }
      case ComponentType::UNSIGNED_BYTE:
      {
        List<uint8> unsignedBytes = Bytes::AsNumericArray<uint8, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);
        intermediateMesh.TextureCoords.resize(unsignedBytes.size() / 2);

        for (int i = 0; i < unsignedBytes.size(); i += 2)
          intermediateMesh.TextureCoords[i / 2] = {
              Normalization::FromUnsignedByteToFloat(unsignedBytes[i]),
              Normalization::FromUnsignedByteToFloat(unsignedBytes[i + 1]),
          };
        break;
      }
      case ComponentType::UNSIGNED_SHORT:
      {
        List<ushort> unsignedShorts = Bytes::AsNumericArray<ushort, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);
        intermediateMesh.TextureCoords.resize(unsignedShorts.size() / 2);

        for (int i = 0; i < unsignedShorts.size(); i += 2)
          intermediateMesh.TextureCoords[i / 2] = {
              Normalization::FromUnsignedShortToFloat(unsignedShorts[i]),
              Normalization::FromUnsignedShortToFloat(unsignedShorts[i + 1]),
          };
        break;
      }
      default:
      {
        Result.SetError(AssetImportStatus::UnsupportedFormat, "Unsupported component type for texture coord attribute.");
        break;
      }
      }
    }

    void ProcessColors(AccessorResult &accessorResult, IntermediateMesh &intermediateMesh)
    {
      List<float> floats;
      switch (accessorResult.ComponentType)
      {
      case ComponentType::FLOAT:
      {
        floats = Bytes::AsNumericArray<float, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);
        break;
      }
      case ComponentType::UNSIGNED_BYTE:
      {
        List<uint8> unsignedBytes = Bytes::AsNumericArray<uint8, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);
        floats.resize(unsignedBytes.size());

        for (int i = 0; i < unsignedBytes.size(); i++)
          floats[i] = Normalization::FromUnsignedByteToFloat(unsignedBytes[i]);
        break;
      }
      case ComponentType::UNSIGNED_SHORT:
      {
        List<ushort> unsignedShorts = Bytes::AsNumericArray<ushort, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);
        floats.resize(unsignedShorts.size());

        for (int i = 0; i < unsignedShorts.size(); i++)
          floats[i] = Normalization::FromUnsignedShortToFloat(unsignedShorts[i]);
        break;
      }
      default:
      {
        Result.SetError(AssetImportStatus::UnsupportedFormat, "Unsupported component type for color attribute.");
        break;
      }
      }

      if (accessorResult.DataType == "VEC3")
      {
        intermediateMesh.Colors.resize(floats.size() / 3);
        for (int i = 0; i < floats.size(); i += 3)
          intermediateMesh.Colors[i / 3] = {floats[i], floats[i + 1], floats[i + 2], 1.0};
        return;
      }

      if (accessorResult.DataType == "VEC4")
      {
        intermediateMesh.Colors.resize(floats.size() / 4);
        for (int i = 0; i < floats.size(); i += 4)
          intermediateMesh.Colors[i / 4] = {floats[i], floats[i + 1], floats[i + 2], floats[i + 3]};
        return;
      }

      Result.SetError(AssetImportStatus::UnsupportedFormat, "Unsupported data type for color attribute.");
    }

    void ProcessIndices(AccessorResult &accessorResult, IntermediateMesh &intermediateMesh)
    {
      switch (accessorResult.ComponentType)
      {
      case ComponentType::UNSIGNED_BYTE:
      {
        List<uint8> unsignedBytes = Bytes::AsNumericArray<uint8, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);

        intermediateMesh.Indices.reserve(unsignedBytes.size());
        for (auto value : unsignedBytes)
          intermediateMesh.Indices.push_back(static_cast<uint32>(value));
        break;
      }
      case ComponentType::UNSIGNED_SHORT:
      {
        List<ushort> unsignedShorts = Bytes::AsNumericArray<ushort, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);

        intermediateMesh.Indices.reserve(unsignedShorts.size());
        for (auto value : unsignedShorts)
          intermediateMesh.Indices.push_back(static_cast<uint32>(value));
        break;
      }
      case ComponentType::UNSIGNED_INT:
      {
        intermediateMesh.Indices = Bytes::AsNumericArray<uint32, Endian::Type::Little, Endian::Type::System>(accessorResult.RawBytes);
        break;
      }
      default:
      {
        Result.SetError(AssetImportStatus::UnsupportedFormat, "Unsupported component type for indices.");
        break;
      }
      }
    }

#pragma endregion Process Attributes
  };
}
