#pragma once

#include "Types.h"

namespace Krys
{
  template <ArithmeticType SampleType>
  class MovingAverage
  {
    SampleType _samples[MaxSamples];
    SampleType _sum;
    uint32 _currentSample;
    uint32 _sampleCount;

  public:
    constexpr MovingAverage() noexcept : _sum(static_cast<SampleType>(0)), _currentSample(0), _sampleCount(0)
    {
    }

    constexpr void Add(SampleType sample) noexcept
    {
      if (_sampleCount == MaxSamples)
      {
        _sum -= _samples[_currentSample];
      }
      else
      {
        _sampleCount++;
      }

      _samples[_currentSample] = data;
      _sum += data;

      _currentSample++;
      if (_currentSample >= MaxSamples)
      {
        _currentSample = 0;
      }
    }

    constexpr NO_DISCARD float32 GetAverage() const noexcept
    {
      if (_sampleCount != 0)
      {
        return static_cast<float32>(_sum) / static_cast<float32>(_sampleCount);
      }
      return 0.0f;
    }
  };
}
