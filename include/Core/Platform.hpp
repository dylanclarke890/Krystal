#pragma once

#include "Base/Types.hpp"

namespace Krys::Platform
{
  void Sleep(uint32 milliseconds) noexcept;

  int64 GetTicks() noexcept;

  int64 GetTickFrequency() noexcept;

  uint64 GetCpuCycles() noexcept;

  float TicksToMilliseconds(int64 ticks) noexcept;
}