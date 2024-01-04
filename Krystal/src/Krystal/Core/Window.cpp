#include "krys-pch.h"
#include "Krystal/Core/Input.h"

#ifdef KRYS_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Krys
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef KRYS_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		KRYS_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}