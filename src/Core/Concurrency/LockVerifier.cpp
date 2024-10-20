#include "Core/Concurrency/LockVerifier.h"

namespace Krys::Concurrency
{
  LockVerifier::LockVerifier() noexcept
      : _locked(false)
  {
  }

  void LockVerifier::Acquire() noexcept
  {
    // Assert that no one already has the lock
    KRYS_ASSERT(!_locked, "Expected thread to be free", 0);
    _locked = true; // Mark as locked to detect overlapping critical sections
  }

  void LockVerifier::Release() noexcept
  {
    // Assert correct usage (that Release() is only called after Acquire())
    KRYS_ASSERT(_locked, "Expected thread to be locked", 0);
    _locked = false;
  }
}