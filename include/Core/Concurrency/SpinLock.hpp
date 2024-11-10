#pragma once

#include <atomic>

namespace Krys::Concurrency
{
  class SpinLock
  {
  private:
    std::atomic_flag _stateFlag;

  public:
    SpinLock() noexcept;
    bool TryAcquire() noexcept;
    void Acquire() noexcept;
    void Release() noexcept;
  };
}
