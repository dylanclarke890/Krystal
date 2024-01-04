#include "krys-pch.h"
#include "Krystal/Core/Input.h"

#ifdef KRYS_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Krys
{

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef KRYS_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		KRYS_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}