#include "Core/Debug/ScopedProfiler.hpp"
#include "Core/Platform.hpp"
#include "IO/Logger.hpp"
#include "Utils/Lazy.hpp"

namespace Krys::Debug
{
  ScopedProfiler::ScopedProfiler(const string &name) noexcept : _start(0), _name(name)
  {
    _start = Platform::GetTicks();
  }

  ScopedProfiler::~ScopedProfiler() noexcept
  {
#ifdef KRYS_ENABLE_LOGGING
    const uint64 end = Platform::GetTicks();

    const uint64 difference = end - _start;
    const uint64 frequency = Platform::GetTickFrequency();
    const double elapsedMs = static_cast<double>(difference) / static_cast<double>(frequency) * 1000.0f;

    Logger::Info("{} took {:.3f} ms.", _name, elapsedMs);
#endif
  }
}