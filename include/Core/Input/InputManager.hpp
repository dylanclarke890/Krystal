#pragma once

#include "Core/Attributes.hpp"
#include "Core/Events/EventManager.hpp"
#include "Core/Input/HID.hpp"
#include "Core/Input/Keyboard.hpp"
#include "Core/Input/Mouse.hpp"
#include "Core/Pointers.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  /// @brief Provides basic device registration and input polling.
  class InputManager
  {
  public:
    NO_COPY_AND_ASSIGN(InputManager)

    /// @brief Constructs an `InputManager`.
    /// @param eventManager The `EventManager` to dispatch events to.
    InputManager(Ptr<EventManager> eventManager) noexcept;

    /// @brief Frees registered devices.
    virtual ~InputManager() noexcept;

    /// @brief Polls all registered devices for input.
    void PollDevices() noexcept;

    /// @brief Registers an input device.
    /// @param device The device to register.
    void RegisterHID(const DeviceId id, Unique<HID> device) noexcept;

    /// @brief Get the mouse.
    const Mouse &GetMouse() const noexcept;

    /// @brief Get the keyboard.
    const Keyboard &GetKeyboard() const noexcept;

    /// @brief Get a registered device by id.
    /// @param id The previously registered id of the device.
    /// @returns The device, or `nullptr` if it wasn't found.
    Ptr<HID> GetDevice(const DeviceId id) const noexcept;

  private:
    /// @brief Clear the mouse state. Needs to be called prior to processing this frame's events.
    void ResetMouse() noexcept;
    
    /// @brief Clear the keyboard state. Needs to be called prior to processing this frame's events.
    void ResetKeyboard() noexcept;

  protected:
    /// @brief The currently active mouse.
    Mouse _mouse;

    /// @brief The currently active keyboard.
    Keyboard _keyboard;

    /// @brief Additional devices registered for polling.
    Map<DeviceId, Unique<HID>, DeviceIdHasher> _customInputDevices;

    /// @brief The `EventManager` to dispatch events to.
    Ptr<EventManager> _eventManager;

    /// @brief Contains pending events for the current frame.
    Queue<Unique<Event>> _events;
  };
}