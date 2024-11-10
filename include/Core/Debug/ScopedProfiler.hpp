#pragma once

#include "Base/Attributes.hpp"
#include "Base/Lazy.hpp"
#include "Base/Types.hpp"

namespace Krys::Debug
{
  class ScopedProfiler
  {
  public:
    ScopedProfiler(const string &name) noexcept;
    ~ScopedProfiler() noexcept;

  private:
    uint64 _start;
    string _name;
  };
}