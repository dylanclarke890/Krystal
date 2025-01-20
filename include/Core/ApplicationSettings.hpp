#pragma once

#include "Base/Types.hpp"

namespace Krys
{
  struct ApplicationSettings final
  {
    /// @brief The title of the application.
    string Title {"Krystal Application"};

    /// @brief The initial width of the window.
    uint32 Width {800};

    /// @brief The initial height of the window.
    uint32 Height {600};

    /// @brief The initial vsync state.
    bool VSync {true};

    /// @brief Whether the window is resizable. Cannot be changed without recreating the window.
    bool Resizable {false};

    /// @brief The framerate to render frames at.
    float RenderFrameRate {60.0f};

    /// @brief The framerate to update physics at.
    float PhysicsFrameRate {30.0f};
  };
}