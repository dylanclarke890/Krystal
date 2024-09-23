#pragma once

#include <functional>

namespace Krys
{
  /// @brief Thin wrapper class that allows for lazy initialisation.
  /// @tparam T
  template <typename T>
  class Lazy
  {
  private:
    T _value;
    std::function<T()> _func;

  public:
    Lazy(std::function<T()> func) : _value(NULL), _func(func) {}

    T val()
    {
      if (!_value)
        _value = func();

      return _value;
    }
  };
}
