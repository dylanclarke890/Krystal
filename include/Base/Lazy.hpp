#pragma once

#include "Base/Types.hpp"

namespace Krys
{
  /// @brief Thin wrapper class that allows for lazy initialization.
  /// @tparam T Any type. Usually one that has an expensive constructor that doesn't need to be invoked
  /// immediately.
  template <typename T>
  class Lazy
  {
  private:
    Nullable<T> _value;
    Func<T()> _func;

  public:
    Lazy(Func<T()> func) : _func(func)
    {
    }

    /// @brief Returns a const reference to the lazily initialized value.
    const T &val()
    {
      if (!_value)
        _value = _func();

      return *_value;
    }

    /// @brief Initialises the value if it hasn't been already.
    void Init() noexcept
    {
      if (!_value)
        _value = _func();
    }

    /// @brief Clears the value if it was set. Allows for `Init` to be called again.
    void Reset() noexcept
    {
      _value.reset();
    }
  };
}
