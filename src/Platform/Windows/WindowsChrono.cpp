#include <windows.h>

#include "Misc/Chrono.h"

namespace Krys
{
  void Chrono::Sleep(uint32 ms)
  {
    ::Sleep(ms);
  }
}