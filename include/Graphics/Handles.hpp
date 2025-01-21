#pragma once

#include "Base/Types.hpp"

#include <limits>

namespace Krys::Impl
{
  template <typename Tag>
  class Handle
  {
  public:
    using handle_t = uint16;
    using tag_t = Tag;

    constexpr static handle_t InvalidHandle = std::numeric_limits<handle_t>::max();

    struct Hash
    {
      size_t operator()(const Handle &handle) const noexcept
      {
        return std::hash<handle_t>()(handle._id);
      }
    };

#pragma region Constructors

    Handle() noexcept : _id(InvalidHandle)
    {
    }

    explicit Handle(const handle_t &id) noexcept : _id(id)
    {
    }

    explicit Handle(handle_t &&id) noexcept : _id(std::move(id))
    {
    }

    Handle(const Handle &other) noexcept : _id(other._id)
    {
    }

    Handle(Handle &&other) noexcept : _id(std::move(other._id))
    {
    }

#pragma endregion Constructors

    Handle &operator=(const Handle &other) noexcept
    {
      _id = other._id;
      return *this;
    }

    Handle &operator=(const handle_t &id) noexcept
    {
      _id = id;
      return *this;
    }

    Handle &operator=(Handle &&other) noexcept
    {
      _id = std::move(other._id);
      return *this;
    }

    bool operator==(const Handle &other) const noexcept
    {
      return _id == other._id;
    }

    bool operator!=(const Handle &other) const noexcept
    {
      return !(_id == other._id);
    }

    const handle_t &Id() const noexcept
    {
      return _id;
    }

    bool IsValid() const noexcept
    {
      return _id != InvalidHandle;
    }

  private:
    handle_t _id;
  };

  struct VertexBufferHandle
  {
  };

  struct IndexBufferHandle
  {
  };

  struct VertexLayoutHandle
  {
  };

  struct PipelineHandle
  {
  };

  struct ShaderHandle
  {
  };

  struct UniformHandle
  {
  };

  struct MeshHandle
  {
  };

  struct TextureHandle
  {
  };

  struct SamplerHandle
  {
  };
}

namespace Krys::Gfx
{
  template <typename Tag>
  using Handle = Krys::Impl::Handle<Tag>;

  using PipelineHandle = Handle<Impl::PipelineHandle>;
  using ShaderHandle = Handle<Impl::ShaderHandle>;
  using IndexBufferHandle = Handle<Impl::IndexBufferHandle>;
  using VertexLayoutHandle = Handle<Impl::VertexLayoutHandle>;
  using VertexBufferHandle = Handle<Impl::VertexBufferHandle>;
  using UniformHandle = Handle<Impl::UniformHandle>;
  using MeshHandle = Handle<Impl::MeshHandle>;
  using TextureHandle = Handle<Impl::TextureHandle>;
  using SamplerHandle = Handle<Impl::SamplerHandle>;
}