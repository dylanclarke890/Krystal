#include "Platform/Win32/Input/Win32InputManager.hpp"
#include "Debug/Macros.hpp"
#include "Events/Input/KeyboardEvent.hpp"
#include "Events/Input/MouseButtonEvent.hpp"
#include "Events/Input/MouseMoveEvent.hpp"
#include "Events/Input/ScrollWheelEvent.hpp"

namespace Krys::Platform
{
  Win32InputManager::Win32InputManager(Ptr<EventManager> eventManager) noexcept
      : InputManager(std::move(eventManager))
  {
  }

  bool Win32InputManager::HandleWindowsMessage(UINT message, WPARAM wParam, LPARAM lParam,
                                               HWND windowHandle) noexcept
  {
    static Set<WPARAM> pressed {};

    switch (message)
    {
      case WM_KEYDOWN:
        _events.emplace(CreateUnique<KeyboardEvent>(
          KeyCodeToEngineKey(wParam), pressed.contains(wParam) ? KeyState::Held : KeyState::Pressed));
        pressed.emplace(wParam);
        break;
      case WM_KEYUP:
        _events.emplace(CreateUnique<KeyboardEvent>(KeyCodeToEngineKey(wParam), KeyState::Released));
        pressed.erase(wParam);
        break;

      case WM_LBUTTONDOWN:
        _events.emplace(CreateUnique<MouseButtonEvent>(MouseButton::LEFT, MouseButtonState::Pressed));
        break;
      case WM_LBUTTONUP:
        _events.emplace(CreateUnique<MouseButtonEvent>(MouseButton::LEFT, MouseButtonState::Released));
        break;

      case WM_RBUTTONDOWN:
        _events.emplace(CreateUnique<MouseButtonEvent>(MouseButton::RIGHT, MouseButtonState::Pressed));
        break;
      case WM_RBUTTONUP:
        _events.emplace(CreateUnique<MouseButtonEvent>(MouseButton::RIGHT, MouseButtonState::Released));
        break;

      case WM_MBUTTONDOWN:
        _events.emplace(CreateUnique<MouseButtonEvent>(MouseButton::MIDDLE, MouseButtonState::Pressed));
        break;
      case WM_MBUTTONUP:
        _events.emplace(CreateUnique<MouseButtonEvent>(MouseButton::MIDDLE, MouseButtonState::Released));
        break;

      case WM_XBUTTONDOWN:
      {
        const auto button =
          GET_XBUTTON_WPARAM(wParam) & XBUTTON1 ? MouseButton::THUMB_1 : MouseButton::THUMB_2;
        _events.emplace(CreateUnique<MouseButtonEvent>(button, MouseButtonState::Pressed));
        break;
      }
      case WM_XBUTTONUP:
      {
        const auto button =
          GET_XBUTTON_WPARAM(wParam) & XBUTTON1 ? MouseButton::THUMB_1 : MouseButton::THUMB_2;
        _events.emplace(CreateUnique<MouseButtonEvent>(button, MouseButtonState::Released));
        break;
      }
      case WM_MOUSEWHEEL:
        _events.emplace(
          CreateUnique<ScrollWheelEvent>(static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam)) / WHEEL_DELTA));
        break;

      case WM_INPUT:
      {
        UINT dwSize = sizeof(RAWINPUT);
        BYTE lpb[sizeof(RAWINPUT)];

        ::GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, lpb, &dwSize,
                          sizeof(RAWINPUTHEADER));

        RAWINPUT raw = {0};
        std::memcpy(&raw, lpb, sizeof(raw));

        if (raw.header.dwType == RIM_TYPEMOUSE)
        {
          // get mouse delta from raw input data
          float x = static_cast<float>(raw.data.mouse.lLastX);
          float y = static_cast<float>(raw.data.mouse.lLastY);
          float clientX = 0;
          float clientY = 0;

          // get mouse position in client space
          POINT point;
          if (GetCursorPos(&point))
          {
            ::ScreenToClient(windowHandle, &point);
            clientX = static_cast<float>(point.x);
            clientY = static_cast<float>(point.y);
          }

          _events.emplace(CreateUnique<MouseMoveEvent>(x, y, clientX, clientY));
        }
        else if ((raw.data.mouse.usButtonFlags & RI_MOUSE_WHEEL) == RI_MOUSE_WHEEL)
        {
          const auto delta = static_cast<float>(static_cast<uint16>(raw.data.mouse.usButtonData));
          _events.emplace(CreateUnique<ScrollWheelEvent>(delta));
        }
        break;
      }
      default: return false;
    }

    return true;
  }

  Key Win32InputManager::KeyCodeToEngineKey(const WPARAM keyCode) const noexcept
  {
    Key key;
    switch (keyCode)
    {
      case 0x30:           key = Key::NUM_0; break;
      case 0x31:           key = Key::NUM_1; break;
      case 0x32:           key = Key::NUM_2; break;
      case 0x33:           key = Key::NUM_3; break;
      case 0x34:           key = Key::NUM_4; break;
      case 0x35:           key = Key::NUM_5; break;
      case 0x36:           key = Key::NUM_6; break;
      case 0x37:           key = Key::NUM_7; break;
      case 0x38:           key = Key::NUM_8; break;
      case 0x39:           key = Key::NUM_9; break;
      case 0x41:           key = Key::A; break;
      case 0x42:           key = Key::B; break;
      case 0x43:           key = Key::C; break;
      case 0x44:           key = Key::D; break;
      case 0x45:           key = Key::E; break;
      case 0x46:           key = Key::F; break;
      case 0x47:           key = Key::G; break;
      case 0x48:           key = Key::H; break;
      case 0x49:           key = Key::I; break;
      case 0x4a:           key = Key::J; break;
      case 0x4b:           key = Key::K; break;
      case 0x4c:           key = Key::L; break;
      case 0x4d:           key = Key::M; break;
      case 0x4e:           key = Key::N; break;
      case 0x4f:           key = Key::O; break;
      case 0x50:           key = Key::P; break;
      case 0x51:           key = Key::Q; break;
      case 0x52:           key = Key::R; break;
      case 0x53:           key = Key::S; break;
      case 0x54:           key = Key::T; break;
      case 0x55:           key = Key::U; break;
      case 0x56:           key = Key::V; break;
      case 0x57:           key = Key::W; break;
      case 0x58:           key = Key::X; break;
      case 0x59:           key = Key::Y; break;
      case 0x5a:           key = Key::Z; break;
      case VK_TAB:         key = Key::TAB; break;
      case VK_SPACE:       key = Key::SPACE; break;
      case VK_ESCAPE:      key = Key::ESCAPE; break;
      case VK_LSHIFT:      key = Key::SHIFT; break;
      case VK_RSHIFT:      key = Key::RIGHT_SHIFT; break;
      case VK_F17:         key = Key::F17; break;
      case VK_DECIMAL:     key = Key::KEYPAD_DECIMAL; break;
      case VK_MULTIPLY:    key = Key::KEYPAD_MULTIPLY; break;
      case VK_OEM_PLUS:    key = Key::KEYPAD_PLUS; break;
      case VK_VOLUME_UP:   key = Key::VOLUME_UP; break;
      case VK_VOLUME_DOWN: key = Key::VOLUME_DOWN; break;
      case VK_VOLUME_MUTE: key = Key::MUTE; break;
      case VK_DIVIDE:      key = Key::KEYPAD_DIVIDE; break;
      case VK_OEM_MINUS:   key = Key::KEYPAD_MINUS; break;
      case VK_F18:         key = Key::F18; break;
      case VK_F19:         key = Key::F19; break;
      case VK_NUMPAD0:     key = Key::KEYPAD_0; break;
      case VK_NUMPAD1:     key = Key::KEYPAD_1; break;
      case VK_NUMPAD2:     key = Key::KEYPAD_2; break;
      case VK_NUMPAD3:     key = Key::KEYPAD_3; break;
      case VK_NUMPAD4:     key = Key::KEYPAD_4; break;
      case VK_NUMPAD5:     key = Key::KEYPAD_5; break;
      case VK_NUMPAD6:     key = Key::KEYPAD_6; break;
      case VK_NUMPAD7:     key = Key::KEYPAD_7; break;
      case VK_F20:         key = Key::F20; break;
      case VK_NUMPAD8:     key = Key::KEYPAD_8; break;
      case VK_NUMPAD9:     key = Key::KEYPAD_9; break;
      case VK_F5:          key = Key::F5; break;
      case VK_F6:          key = Key::F6; break;
      case VK_F7:          key = Key::F7; break;
      case VK_F3:          key = Key::F3; break;
      case VK_F8:          key = Key::F8; break;
      case VK_F9:          key = Key::F9; break;
      case VK_F11:         key = Key::F11; break;
      case VK_F13:         key = Key::F13; break;
      case VK_F16:         key = Key::F16; break;
      case VK_F14:         key = Key::F14; break;
      case VK_F10:         key = Key::F10; break;
      case VK_F12:         key = Key::F12; break;
      case VK_F15:         key = Key::F15; break;
      case VK_HELP:        key = Key::HELP; break;
      case VK_HOME:        key = Key::HOME; break;
      case VK_F4:          key = Key::F4; break;
      case VK_END:         key = Key::END; break;
      case VK_F2:          key = Key::F2; break;
      case VK_F1:          key = Key::F1; break;
      case VK_LEFT:        key = Key::LEFT_ARROW; break;
      case VK_RIGHT:       key = Key::RIGHT_ARROW; break;
      case VK_DOWN:        key = Key::DOWN_ARROW; break;
      case VK_UP:          key = Key::UP_ARROW; break;
      default:             key = Key::UNKNOWN; break;
    }

    return key;
  }
}
