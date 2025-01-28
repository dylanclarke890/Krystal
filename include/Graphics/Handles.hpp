#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"

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

#pragma region Assignment

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

#pragma endregion Assignment

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

  struct ProgramHandle
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

  struct RenderEntityHandle
  {
  };

  struct LightHandle
  {
  };

  struct SceneHandle
  {
  };

  struct MaterialHandle
  {
  };
}

namespace Krys::Gfx
{
  template <typename Tag>
  using Handle = Krys::Impl::Handle<Tag>;
  using ProgramHandle = Handle<Impl::ProgramHandle>;
  using ShaderHandle = Handle<Impl::ShaderHandle>;
  using IndexBufferHandle = Handle<Impl::IndexBufferHandle>;
  using VertexLayoutHandle = Handle<Impl::VertexLayoutHandle>;
  using VertexBufferHandle = Handle<Impl::VertexBufferHandle>;
  using UniformHandle = Handle<Impl::UniformHandle>;
  using MeshHandle = Handle<Impl::MeshHandle>;
  using TextureHandle = Handle<Impl::TextureHandle>;
  using SamplerHandle = Handle<Impl::SamplerHandle>;
  using RenderEntityHandle = Handle<Impl::RenderEntityHandle>;
  using LightHandle = Handle<Impl::LightHandle>;
  using SceneHandle = Handle<Impl::SceneHandle>;
  using MaterialHandle = Handle<Impl::MaterialHandle>;

  template <typename THandle>
  class HandleManager
  {
    using handle_t = THandle;
    using tag_t = typename handle_t::tag_t;
    using value_t = typename THandle::handle_t;

  public:
    HandleManager() noexcept = default;
    ~HandleManager() noexcept = default;

    NO_DISCARD handle_t Next() noexcept
    {
      if (!recycled.empty())
      {
        auto handle = recycled.back();
        recycled.pop_back();
        return handle;
      }

      return handle_t(_nextId++);
    }

    void Recycle(handle_t handle) noexcept
    {
      KRYS_ASSERT(handle.IsValid(), "Tried to recycle an invalid handle.");
      if (handle.IsValid())
        recycled.push_back(handle);
    }

  private:
    List<handle_t> recycled;
    value_t _nextId {0};
  };
}