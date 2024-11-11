#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"

namespace Krys
{
  template <IsArithmeticT SampleType, int MaxSamples>
  class MovingAverage
  {
    Array<SampleType, MaxSamples> _samples;
    uint32 _currentSample;
    SampleType _sum;

  public:
    constexpr MovingAverage() noexcept : _sum(static_cast<SampleType>(0)), _currentSample(0), _sampleCount(0)
    {
    }

    constexpr void Add(SampleType sample) noexcept
    {
      if (_samples.size() == MaxSamples)
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

    constexpr NO_DISCARD SampleType GetAverage() const noexcept
    {
      if (_samples.size() != 0)
      {
        return _sum / static_cast<SampleType>(_samples.size());
      }
      return 0.0f;
    }
  };
}
