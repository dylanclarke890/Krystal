#include "krys-pch.h"
#include "WindowsInput.h"
#include "Krystal/Application.h"

#include <GLFW/glfw3.h>

namespace Krys
{
  Input* Input::s_Instance = new WindowsInput();
  bool WindowsInput::IsKeyPressedImpl(int keycode)
  {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool WindowsInput::IsMouseButtonPressedImpl(int button)
  {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
  }

  std::pair<float, float> WindowsInput::GetMousePositionImpl()
  {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return std::make_pair(xpos, ypos);
  }

  float WindowsInput::GetMouseXImpl()
  {
    auto [x, _] = GetMousePositionImpl();
    return x;
  }
  
  float WindowsInput::GetMouseYImpl()
  {
    auto [_, y] = GetMousePositionImpl();
    return y;
  }
}