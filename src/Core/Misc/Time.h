#pragma once

#include "Krystal.h"
#include "Application.h"

namespace Krys
{
  class Time
  {
    friend class Application;

  private:
    static float m_TimeElapsedMs;
    static float m_LastFrameMs;

  public:
    static const float GetElapsedMs() noexcept
    {
      return m_TimeElapsedMs;
    }

    static const float GetElapsedSecs() noexcept
    {
      return m_TimeElapsedMs / 1000.0f;
    }

    static const float GetDeltaMs() noexcept
    {
      return m_LastFrameMs;
    }

    static const float GetDeltaSecs() noexcept
    {
      return m_LastFrameMs / 1000.0f;
    }

  private:
    static void Increment(float ms) noexcept
    {
      m_LastFrameMs = ms;
      m_TimeElapsedMs += ms;
    }
  };
}