#pragma once

#include "Base/Types.hpp"
#include <atomic>

namespace Krys::Concurrency
{
  class ReadersWriterLock
  {
  private:
    static constexpr uint32 WRITER_LOCK = 0x80'00'00'00U;
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