#pragma once

#include "Application.h"
#include "Core.h"

namespace Krys
{
  class Time
  {
    friend class Application;

  private:
    inline static float _timeElapsedMs;
    inline static float _lastFrameMs;

  public:
    static const float GetElapsedMs() noexcept
    {
      return _timeElapsedMs;
    }

    static const float GetElapsedSecs() noexcept
    {
      return _timeElapsedMs / 1000.0f;
    }

    static const float GetDeltaMs() noexcept
    {
      return _lastFrameMs;
    }

    static const float GetDeltaSecs() noexcept
    {
      return _lastFrameMs / 1000.0f;
    }

    static void Increment(float ms) noexcept
    {
      _lastFrameMs = ms;
      _timeElapsedMs += ms;
    }
  };
}