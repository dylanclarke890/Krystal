#pragma once

#include "Base/Types.hpp"
#include <atomic>

namespace Krys::Concurrency
{
  class ReentrantLock
  {
    std::atomic<size_t> _state;
    int32 _refCount;

  public:
    ReentrantLock() noexcept;

    bool TryAcquire() noexcept;
    void Acquire() noexcept;
    void Release() noexcept;
  };
}