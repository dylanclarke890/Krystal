#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Debug/Macros.hpp"

#include <limits>

namespace Krys::Impl
{
  template <typename Tag>
  class Handle
  {
  public:
    using handle_t = uint32;
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

    constexpr Handle() noexcept : _id(InvalidHandle)
    {
    }

    explicit constexpr Handle(const handle_t &id) noexcept : _id(id)
    {
    }

    explicit constexpr Handle(handle_t &&id) noexcept : _id(std::move(id))
    {
    }

    constexpr Handle(const Handle &other) noexcept : _id(other._id)
    {
    }

    constexpr Handle(Handle &&other) noexcept : _id(std::move(other._id))
    {
    }

#pragma endregion Constructors

#pragma region Assignment

    constexpr Handle &operator=(const Handle &other) noexcept
    {
      _id = other._id;
      return *this;
    }

    constexpr Handle &operator=(const handle_t &id) noexcept
    {
      _id = id;
      return *this;
    }

    constexpr Handle &operator=(Handle &&other) noexcept
    {
      _id = std::move(other._id);
      return *this;
    }

    constexpr bool operator==(const Handle &other) const noexcept
    {
      return _id == other._id;
    }

    constexpr bool operator!=(const Handle &other) const noexcept
    {
      return !(_id == other._id);
    }

#pragma endregion Assignment

    constexpr const handle_t &Id() const noexcept
    {
      return _id;
    }

    constexpr bool IsValid() const noexcept
    {
      return _id != InvalidHandle;
    }

  private:
    handle_t _id;
  };

#define HANDLE_IMPL(Tag)                                                                                     \
  struct Tag##Handle                                                                                         \
  {                                                                                                          \
  }

  HANDLE_IMPL(VertexBuffer);
  HANDLE_IMPL(IndexBuffer);
  HANDLE_IMPL(UniformBuffer);
  HANDLE_IMPL(ShaderStorageBuffer);
  HANDLE_IMPL(Program);
  HANDLE_IMPL(Shader);
  HANDLE_IMPL(Mesh);
  HANDLE_IMPL(Texture);
  HANDLE_IMPL(Sampler);
  HANDLE_IMPL(Light);
  HANDLE_IMPL(SceneGraph);
  HANDLE_IMPL(Material);
  HANDLE_IMPL(RenderTarget);
  HANDLE_IMPL(Font);

#undef HANDLE_IMPL
}

namespace Krys::Gfx
{

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

      auto next = _nextId;
      _nextId++;
      return handle_t(next);
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

#define DECLARE_HANDLE(Tag)                                                                                  \
  using Tag##Handle = Impl::Handle<Impl::Tag##Handle>;                                                       \
  template <typename T>                                                                                      \
  using Tag##HandleMap = Map<Tag##Handle, T, Tag##Handle::Hash>;                                             \
  using Tag##HandleManager = HandleManager<Tag##Handle>

  DECLARE_HANDLE(Program);
  DECLARE_HANDLE(Shader);
  DECLARE_HANDLE(IndexBuffer);
  DECLARE_HANDLE(VertexBuffer);
  DECLARE_HANDLE(UniformBuffer);
  DECLARE_HANDLE(ShaderStorageBuffer);
  DECLARE_HANDLE(Mesh);
  DECLARE_HANDLE(Texture);
  DECLARE_HANDLE(Sampler);
  DECLARE_HANDLE(Light);
  DECLARE_HANDLE(SceneGraph);
  DECLARE_HANDLE(Material);
  DECLARE_HANDLE(RenderTarget);
  DECLARE_HANDLE(Font);

#undef DECLARE_HANDLE
}