#pragma once

#include "Base/Types.hpp"

#include <limits>

namespace Krys::Impl
{
  template <typename Tag>
  class Handle
  {
    using handle_t = uint16;
    using tag_t = Tag;

  public:
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

  struct DynamicIndexBufferHandle
  {
  };

  struct DynamicVertexBufferHandle
  {
  };

  struct FrameBufferHandle
  {
  };

  struct IndexBufferHandle
  {
  };

  struct IndirectBufferHandle
  {
  };

  struct OcclusionQueryHandle
  {
  };

  struct ProgramHandle
  {
  };

  struct ShaderHandle
  {
  };

  struct TextureHandle
  {
  };

  struct UniformHandle
  {
  };

  struct VertexBufferHandle
  {
  };

  struct VertexLayoutHandle
  {
  };
}

namespace Krys::Graphics
{
  template <typename Tag>
  using Handle = Krys::Impl::Handle<Tag>;

  using ProgramHandle = Handle<Impl::ProgramHandle>;
  using ShaderHandle = Handle<Impl::ShaderHandle>;
  using TextureHandle = Handle<Impl::TextureHandle>;
  using UniformHandle = Handle<Impl::UniformHandle>;
  using VertexLayoutHandle = Handle<Impl::VertexLayoutHandle>;
  using IndexBufferHandle = Handle<Impl::IndexBufferHandle>;
  using VertexBufferHandle = Handle<Impl::VertexBufferHandle>;
  using DynamicIndexBufferHandle = Handle<Impl::DynamicIndexBufferHandle>;
  using DynamicVertexBufferHandle = Handle<Impl::DynamicVertexBufferHandle>;
  using FrameBufferHandle = Handle<Impl::FrameBufferHandle>;
  using IndirectBufferHandle = Handle<Impl::IndirectBufferHandle>;
  using OcclusionQueryHandle = Handle<Impl::OcclusionQueryHandle>;
}