#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/StringId.hpp"

namespace Krys
{
  typedef StringId DeviceId;
  typedef StringIdHasher DeviceIdHasher;

  class EventManager;

  /// @brief Represents a human input device that can be polled for input.
  class HID
  {
  public:
    NO_COPY_AND_ASSIGN(HID)

    virtual ~HID() noexcept = default;

    /// @brief Polls the device for input. Any input received since the last frame should be raised as an
    /// event with the provided `EventManager`.
    /// @param eventManager The event manager to send events to.
    virtual void PollDevice(Ptr<EventManager> eventManager) noexcept = 0;

  protected:
    /// @brief Constructs a `HID`.
    HID() noexcept = default;
  };
}