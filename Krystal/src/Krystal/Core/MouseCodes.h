#pragma once

namespace Krys
{
	enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	};

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define KRYS_MOUSE_BUTTON_0      ::Krys::MouseCode::Button0
#define KRYS_MOUSE_BUTTON_1      ::Krys::MouseCode::Button1
#define KRYS_MOUSE_BUTTON_2      ::Krys::MouseCode::Button2
#define KRYS_MOUSE_BUTTON_3      ::Krys::MouseCode::Button3
#define KRYS_MOUSE_BUTTON_4      ::Krys::MouseCode::Button4
#define KRYS_MOUSE_BUTTON_5      ::Krys::MouseCode::Button5
#define KRYS_MOUSE_BUTTON_6      ::Krys::MouseCode::Button6
#define KRYS_MOUSE_BUTTON_7      ::Krys::MouseCode::Button7
#define KRYS_MOUSE_BUTTON_LAST   ::Krys::MouseCode::ButtonLast
#define KRYS_MOUSE_BUTTON_LEFT   ::Krys::MouseCode::ButtonLeft
#define KRYS_MOUSE_BUTTON_RIGHT  ::Krys::MouseCode::ButtonRight
#define KRYS_MOUSE_BUTTON_MIDDLE ::Krys::MouseCode::ButtonMiddle