#pragma once

#include "Base/Types.hpp"

#include <chrono>

namespace Krys
{
  class Stopwatch
  {
  public:
    Stopwatch() noexcept
    {
      Reset();
    }

    ~Stopwatch() noexcept = default;

    void Start() noexcept
    {
      _start = std::chrono::high_resolution_clock::now();
    }

    void Stop() noexcept
    {
      _end = std::chrono::high_resolution_clock::now();
    }

    void Reset() noexcept
    {
      _start = _end = std::chrono::time_point<std::chrono::high_resolution_clock>();
    }

    double GetElapsedSeconds() const noexcept
    {
      return GetElapsedMilliseconds() / 1000.0f;
    }

    double GetElapsedMilliseconds() const noexcept
    {
      return GetElapsedMicroseconds() / 1000.0f;
    }

    double GetElapsedMicroseconds() const noexcept
    {
      return GetElapsedNanoseconds() / 1000.0f;
    }

    double GetElapsedNanoseconds() const noexcept
    {
      return std::chrono::duration<double, std::nano>(_end - _start).count();
    }

    double GetElapsedTicks() const noexcept
    {
      // TODO: is this correct?
      return std::chrono::duration<double, std::ratio<1, 1>>(_end - _start).count();
    }

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
    std::chrono::time_point<std::chrono::high_resolution_clock> _end;
  };
}