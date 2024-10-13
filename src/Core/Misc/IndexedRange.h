#pragma once

namespace Krys
{
  template <typename T>
  class IndexedRange
  {
  private:
    const T &Container;

  public:
    struct Iterator
    {
      size_t index;
      typename T::const_iterator iter;

      bool operator!=(const Iterator &other) const { return iter != other.iter; }
      void operator++()
      {
        ++index;
        ++iter;
      }
      auto operator*() const { return std::make_pair(index, *iter); }
    };

    IndexedRange(const T &container) : Container(container) {}

    Iterator begin() const { return {0, Container.begin()}; }
    Iterator end() const { return {Container.size(), Container.end()}; }
  };
}
