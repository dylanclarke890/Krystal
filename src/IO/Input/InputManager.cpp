#include "IO/Input/InputManager.hpp"
#include "Debug/Macros.hpp"
#include "Events/Input/KeyboardEvent.hpp"
#include "Events/Input/MouseButtonEvent.hpp"
#include "Events/Input/MouseMoveEvent.hpp"

namespace Krys
{
  InputManager::InputManager(Ptr<EventManager> eventManager) noexcept : _eventManager(eventManager)
  {
  }

  InputManager::~InputManager() noexcept
  {
    _customInputDevices.clear();
  }

  void InputManager::PollDevices() noexcept
  {
    ResetMouse();
    ResetKeyboard();

    while (!_events.empty())
    {
      auto &event = _events.front();
      switch (event->GetEventType())
      {
        case SID("mouse-move-event"):
        {
          auto mouseMoveEvent = static_cast<MouseMoveEvent *>(event.get());
          _mouse._deltaX += mouseMoveEvent->DeltaX();
          _mouse._deltaY += mouseMoveEvent->DeltaY();
          _mouse._clientX = mouseMoveEvent->GetClientX();
          _mouse._clientY = mouseMoveEvent->GetClientY();
        }
        break;

        case SID("mouse-button-event"):
        {
          auto mouseButtonEvent = static_cast<MouseButtonEvent *>(event.get());
          switch (mouseButtonEvent->GetState())
          {
            case MouseButtonState::Pressed:  _mouse._pressed |= mouseButtonEvent->GetButton(); break;
            case MouseButtonState::Released: _mouse._released |= mouseButtonEvent->GetButton(); break;
            default:                         KRYS_ASSERT(false, "Unknown mouse button state"); break;
          }
        }
        break;

        case SID("keyboard-event"):
        {
          auto keyboardEvent = static_cast<KeyboardEvent *>(event.get());
          switch (keyboardEvent->GetState())
          {
            case KeyState::Pressed:  _keyboard._pressed.emplace(keyboardEvent->GetKey()); break;
            case KeyState::Held:     _keyboard._held.emplace(keyboardEvent->GetKey()); break;
            case KeyState::Released: _keyboard._released.emplace(keyboardEvent->GetKey()); break;
            default:                 KRYS_ASSERT(false, "Unknown key state"); break;
          }
        }
        break;

        default: break;
      }

      _eventManager->Enqueue(std::move(event));
      _events.pop();
    }

    for (auto &[_, device] : _customInputDevices)
      device->PollDevice(_eventManager);
  }

  void InputManager::RegisterHID(const DeviceId id, Unique<HID> device) noexcept
  {
    KRYS_ASSERT(_customInputDevices.find(id) == _customInputDevices.end(), "Device already registered");
    _customInputDevices.emplace(id, std::move(device));
  }

  const Mouse &InputManager::GetMouse() const noexcept
  {
    return _mouse;
  }

  const Keyboard &InputManager::GetKeyboard() const noexcept
  {
    return _keyboard;
  }

  Ptr<HID> InputManager::GetDevice(const DeviceId id) const noexcept
  {
    auto result = _customInputDevices.find(id);
    if (result != _customInputDevices.end())
    {
      return result->second.get();
    }
    return nullptr;
  }

  void InputManager::ResetMouse() noexcept
  {
    _mouse._deltaX = 0.0f;
    _mouse._deltaY = 0.0f;
    _mouse._held |= _mouse._pressed;
    _mouse._held &= ~_mouse._released;
    _mouse._pressed = MouseButton::None;
    _mouse._released = MouseButton::None;
  }

  void InputManager::ResetKeyboard() noexcept
  {
    _keyboard._pressed.clear();
    _keyboard._held.clear();
    _keyboard._released.clear();
  }
}
