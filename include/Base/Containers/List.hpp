#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"

namespace Krys::STL
{
  template <typename T>
  class List
  {
  public:
    List() = default;
    List(const List &) = delete;
    List &operator=(const List &) = delete;
    ~List() = default;

    void Add(const T &item)
    {
      if (_size >= _capacity)
      {
        // Allocate more space
        size_t newCapacity = _capacity == 0 ? 1 : _capacity * 2;
        T *newBuffer = new T[newCapacity];
        for (size_t i = 0; i < _size; ++i)
        {
          newBuffer[i] = _buffer[i];
        }
        delete[] _buffer;
        _buffer = newBuffer;
        _capacity = newCapacity;
      }
      _buffer[_size++] = item;
    }

    void Remove(const T &item)
    {
      for (size_t i = 0; i < _size; ++i)
      {
        if (_buffer[i] == item)
        {
          // Shift elements to the left
          for (size_t j = i; j < _size - 1; ++j)
          {
            _buffer[j] = _buffer[j + 1];
          }
          --_size;
          return;
        }
      }
    }

    NO_DISCARD bool Contains(const T &item) const noexcept
    {
      for (size_t i = 0; i < _size; ++i)
      {
        if (_buffer[i] == item)
        {
          return true;
        }
      }

      return false;
    }

    NO_DISCARD size_t GetSize() const noexcept
    {
      return _size;
    }

    NO_DISCARD size_t GetCapacity() const noexcept
    {
      return _capacity;
    }

  private:
    T *_buffer {nullptr};
    size_t _capacity {0};
    size_t _size {0};
  };
}