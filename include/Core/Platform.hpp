#pragma once

#include "Base/Types.hpp"

namespace Krys::Platform
{
  /// @brief Initializes the platform.
  void Initialize() noexcept;

  /// @brief Sleeps the current thread for the specified number of milliseconds.
  /// @param milliseconds The number of milliseconds to sleep.
  void Sleep(uint32 milliseconds) noexcept;

  /// @brief Gets the current number of ticks.
  int64 GetTicks() noexcept;

  /// @brief Gets the frequency of the ticks.
  int64 GetTickFrequency() noexcept;

  /// @brief Gets the number of CPU cycles. This is a low-level function and should be used with caution.
  uint64 GetCpuCycles() noexcept;

  /// @brief Converts ticks to milliseconds.
  float TicksToMilliseconds(int64 ticks) noexcept;

  /// @brief Gets the time in seconds since the application started running.
  float GetTime() noexcept;
}