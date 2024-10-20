#pragma once

#include <atomic>
#include "Types.h"

namespace Krys::Concurrency
{
  class ReadersWriterLock
  {
  private:
    static constexpr uint32 WRITER_LOCK = 0x80000000U;
    std::atomic<uint32> _state;

  public:
    ReadersWriterLock() noexcept;

    bool TryAcquire() noexcept;
    void Acquire() noexcept;
    void AcquireRead() noexcept;
    bool TryAcquireRead() noexcept;

    /// @brief Release the lock (both writer and readers can call this).
    void Release() noexcept;
  };
}