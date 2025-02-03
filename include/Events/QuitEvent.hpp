#pragma once

#include "Events/Event.hpp"

namespace Krys
{
  /// @brief Represents an attempt to close the application.
  ///
  /// A `QuitEvent` is raised automatically in response to common exit requests,
  /// such as pressing the close button or using keyboard shortcuts like ALT + F4 (on Windows).
  /// Typically, you do not need to create these yourself.
  class QuitEvent : public Event
  {
  public:
    KRYS_EVENT_CLASS_TYPE("quit-event")

    /// @brief Constructs a `QuitEvent`.
    QuitEvent() noexcept = default;
  };
}