#include "Core/Application.hpp"
#include "Core/Events/EventManager.hpp"
#include "Core/Window.hpp"
#include "Core/WindowManager.hpp"

namespace Krys
{
  Application::Application(Unique<ApplicationContext> context, uint32 width, uint32 height) noexcept
      : _context(std::move(context))
  {
    _context->GetWindowManager()->Create(width, height);
  }

  void Application::Run() noexcept
  {
    while (true)
    {
      _context->GetWindowManager()->GetCurrentWindow()->Poll();
      _context->GetInputManager()->PollDevices();
      _context->GetEventManager()->ProcessEvents();

      Update(0.0f);
    }
  }
}