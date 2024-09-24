#pragma once

#include <functional>
#include <optional>

namespace Krys
{
  /// @brief Thin wrapper class that allows for lazy initialization.
  /// @tparam T
  template <typename T>
  class Lazy
  {
  private:
    std::optional<T> _value;
    std::function<T()> _func;

  public:
    Lazy(std::function<T()> func) : _func(func) {}

    /// @brief Returns a const reference to the lazily initialized value.
    const T &val()
    {
      if (!_value) // Initialize if not already done
        _value = _func();

      return *_value;
    }
  };
}
