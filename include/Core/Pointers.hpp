#pragma once

#include <memory>
#include <type_traits>

namespace Krys
{
  template <typename T>
  using Unique = std::unique_ptr<T>;

  template <typename T>
  using Ref = std::shared_ptr<T>;

  template <typename T>
  using WeakRef = std::weak_ptr<T>;

  template <typename T, typename... Args>
  constexpr Unique<T> CreateUnique(Args &&...args)
  {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  template <typename T, typename... Args>
  constexpr Ref<T> CreateRef(Args &&...args)
  {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }

  template <typename T>
  concept IsPointer = std::is_pointer_v<T>;
}