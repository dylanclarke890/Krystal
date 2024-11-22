#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TSampleType, int MaxSamples>
  class MovingAverage
  {
    using sample_t = TSampleType;
    Array<sample_t, MaxSamples> _samples;
    uint32 _currentSample, _sampleCount;
    sample_t _sum;

  public:
    constexpr MovingAverage() noexcept
        : _sum(static_cast<sample_t>(0)), _samples({}), _currentSample(0), _sampleCount(0)
    {
    }

    constexpr void Add(sample_t sample) noexcept
    {
      if (_sampleCount == MaxSamples)
        _sum -= _samples[_currentSample];
      else
        _sampleCount++;

      _samples[_currentSample] = sample;
      _sum += sample;

      _currentSample = (_currentSample + 1) % MaxSamples;
    }

    constexpr NO_DISCARD sample_t GetAverage() const noexcept
    {
      if (_sampleCount == 0)
        return static_cast<sample_t>(0);
      return _sum / static_cast<sample_t>(_sampleCount);
    }
  };
}
