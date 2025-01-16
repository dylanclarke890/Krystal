#pragma once

#include "Base/Types.hpp"

namespace Krys
{
  struct ApplicationSettings final
  {
    string Title {"Krystal Application"};
    uint32 Width {800};
    uint32 Height {600};
    bool Resizable {false};
    bool VSync {true};
    float RenderFrameRate {60.0f};
    float PhysicsFrameRate {60.0f};
  };
}