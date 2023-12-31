#pragma once

namespace Krys
{
  class TimeStep
  {
  private:
    float m_Time;
  public:
    TimeStep(float time = 0.0f) : m_Time(time) {}

    operator float() const { return m_Time; }

    float GetSeconds() const { return m_Time; }
    float GetMilliseconds() const { return m_Time * 1000.0f; }
  };
}