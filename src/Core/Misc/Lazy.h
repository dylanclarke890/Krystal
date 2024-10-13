#pragma once

#include "Core.h"

#include <functional>

namespace Krys
{
  /// @brief Thin wrapper class that allows for lazy initialization.
  /// @tparam T Any type. Usually one that has an expensive constructor that doesn't need to be invoked immediately.
  template <typename T>
  class Lazy
  {
  private:
    Nullable<T> Value;
    std::function<T()> Func;

  public:
    Lazy(std::function<T()> func) : Func(func) {}

    /// @brief Returns a const reference to the lazily initialized value.
    const T &val()
    {
      if (!Value) // Initialize if not already done
        Value = Func();

      return *Value;
    }
  };
}
