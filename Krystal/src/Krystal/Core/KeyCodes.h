#pragma once

namespace Krys
{
	enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39,	/* ' */
		Comma = 44,			  /* , */
		Minus = 45,       /* - */
		Period = 46,	    /* . */
		Slash = 47,				/* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61,			/* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,   /* [ */
		Backslash = 92,			/* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,   /* ` */

		World1 = 161,       /* non-US #1 */
		World2 = 162,				/* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define KRYS_KEY_SPACE           ::Krys::KeyCode::Space
#define KRYS_KEY_APOSTROPHE      ::Krys::KeyCode::Apostrophe    /* ' */
#define KRYS_KEY_COMMA           ::Krys::KeyCode::Comma         /* , */
#define KRYS_KEY_MINUS           ::Krys::KeyCode::Minus         /* - */
#define KRYS_KEY_PERIOD          ::Krys::KeyCode::Period        /* . */
#define KRYS_KEY_SLASH           ::Krys::KeyCode::Slash         /* / */
#define KRYS_KEY_0               ::Krys::KeyCode::D0
#define KRYS_KEY_1               ::Krys::KeyCode::D1
#define KRYS_KEY_2               ::Krys::KeyCode::D2
#define KRYS_KEY_3               ::Krys::KeyCode::D3
#define KRYS_KEY_4               ::Krys::KeyCode::D4
#define KRYS_KEY_5               ::Krys::KeyCode::D5
#define KRYS_KEY_6               ::Krys::KeyCode::D6
#define KRYS_KEY_7               ::Krys::KeyCode::D7
#define KRYS_KEY_8               ::Krys::KeyCode::D8
#define KRYS_KEY_9               ::Krys::KeyCode::D9
#define KRYS_KEY_SEMICOLON       ::Krys::KeyCode::Semicolon     /* ; */
#define KRYS_KEY_EQUAL           ::Krys::KeyCode::Equal         /* = */
#define KRYS_KEY_A               ::Krys::KeyCode::A
#define KRYS_KEY_B               ::Krys::KeyCode::B
#define KRYS_KEY_C               ::Krys::KeyCode::C
#define KRYS_KEY_D               ::Krys::KeyCode::D
#define KRYS_KEY_E               ::Krys::KeyCode::E
#define KRYS_KEY_F               ::Krys::KeyCode::F
#define KRYS_KEY_G               ::Krys::KeyCode::G
#define KRYS_KEY_H               ::Krys::KeyCode::H
#define KRYS_KEY_I               ::Krys::KeyCode::I
#define KRYS_KEY_J               ::Krys::KeyCode::J
#define KRYS_KEY_K               ::Krys::KeyCode::K
#define KRYS_KEY_L               ::Krys::KeyCode::L
#define KRYS_KEY_M               ::Krys::KeyCode::M
#define KRYS_KEY_N               ::Krys::KeyCode::N
#define KRYS_KEY_O               ::Krys::KeyCode::O
#define KRYS_KEY_P               ::Krys::KeyCode::P
#define KRYS_KEY_Q               ::Krys::KeyCode::Q
#define KRYS_KEY_R               ::Krys::KeyCode::R
#define KRYS_KEY_S               ::Krys::KeyCode::S
#define KRYS_KEY_T               ::Krys::KeyCode::T
#define KRYS_KEY_U               ::Krys::KeyCode::U
#define KRYS_KEY_V               ::Krys::KeyCode::V
#define KRYS_KEY_W               ::Krys::KeyCode::W
#define KRYS_KEY_X               ::Krys::KeyCode::X
#define KRYS_KEY_Y               ::Krys::KeyCode::Y
#define KRYS_KEY_Z               ::Krys::KeyCode::Z
#define KRYS_KEY_LEFT_BRACKET    ::Krys::KeyCode::LeftBracket   /* [ */
#define KRYS_KEY_BACKSLASH       ::Krys::KeyCode::Backslash     /* \ */
#define KRYS_KEY_RIGHT_BRACKET   ::Krys::KeyCode::RightBracket  /* ] */
#define KRYS_KEY_GRAVE_ACCENT    ::Krys::KeyCode::GraveAccent   /* ` */
#define KRYS_KEY_WORLD_1         ::Krys::KeyCode::World1        /* non-US #1 */
#define KRYS_KEY_WORLD_2         ::Krys::KeyCode::World2        /* non-US #2 */

/* Function keys */
#define KRYS_KEY_ESCAPE          ::Krys::KeyCode::Escape
#define KRYS_KEY_ENTER           ::Krys::KeyCode::Enter
#define KRYS_KEY_TAB             ::Krys::KeyCode::Tab
#define KRYS_KEY_BACKSPACE       ::Krys::KeyCode::Backspace
#define KRYS_KEY_INSERT          ::Krys::KeyCode::Insert
#define KRYS_KEY_DELETE          ::Krys::KeyCode::Delete
#define KRYS_KEY_RIGHT           ::Krys::KeyCode::Right
#define KRYS_KEY_LEFT            ::Krys::KeyCode::Left
#define KRYS_KEY_DOWN            ::Krys::KeyCode::Down
#define KRYS_KEY_UP              ::Krys::KeyCode::Up
#define KRYS_KEY_PAGE_UP         ::Krys::KeyCode::PageUp
#define KRYS_KEY_PAGE_DOWN       ::Krys::KeyCode::PageDown
#define KRYS_KEY_HOME            ::Krys::KeyCode::Home
#define KRYS_KEY_END             ::Krys::KeyCode::End
#define KRYS_KEY_CAPS_LOCK       ::Krys::KeyCode::CapsLock
#define KRYS_KEY_SCROLL_LOCK     ::Krys::KeyCode::ScrollLock
#define KRYS_KEY_NUM_LOCK        ::Krys::KeyCode::NumLock
#define KRYS_KEY_PRINT_SCREEN    ::Krys::KeyCode::PrintScreen
#define KRYS_KEY_PAUSE           ::Krys::KeyCode::Pause
#define KRYS_KEY_F1              ::Krys::KeyCode::F1
#define KRYS_KEY_F2              ::Krys::KeyCode::F2
#define KRYS_KEY_F3              ::Krys::KeyCode::F3
#define KRYS_KEY_F4              ::Krys::KeyCode::F4
#define KRYS_KEY_F5              ::Krys::KeyCode::F5
#define KRYS_KEY_F6              ::Krys::KeyCode::F6
#define KRYS_KEY_F7              ::Krys::KeyCode::F7
#define KRYS_KEY_F8              ::Krys::KeyCode::F8
#define KRYS_KEY_F9              ::Krys::KeyCode::F9
#define KRYS_KEY_F10             ::Krys::KeyCode::F10
#define KRYS_KEY_F11             ::Krys::KeyCode::F11
#define KRYS_KEY_F12             ::Krys::KeyCode::F12
#define KRYS_KEY_F13             ::Krys::KeyCode::F13
#define KRYS_KEY_F14             ::Krys::KeyCode::F14
#define KRYS_KEY_F15             ::Krys::KeyCode::F15
#define KRYS_KEY_F16             ::Krys::KeyCode::F16
#define KRYS_KEY_F17             ::Krys::KeyCode::F17
#define KRYS_KEY_F18             ::Krys::KeyCode::F18
#define KRYS_KEY_F19             ::Krys::KeyCode::F19
#define KRYS_KEY_F20             ::Krys::KeyCode::F20
#define KRYS_KEY_F21             ::Krys::KeyCode::F21
#define KRYS_KEY_F22             ::Krys::KeyCode::F22
#define KRYS_KEY_F23             ::Krys::KeyCode::F23
#define KRYS_KEY_F24             ::Krys::KeyCode::F24
#define KRYS_KEY_F25             ::Krys::KeyCode::F25

/* Keypad */
#define KRYS_KEY_KP_0            ::Krys::KeyCode::KP0
#define KRYS_KEY_KP_1            ::Krys::KeyCode::KP1
#define KRYS_KEY_KP_2            ::Krys::KeyCode::KP2
#define KRYS_KEY_KP_3            ::Krys::KeyCode::KP3
#define KRYS_KEY_KP_4            ::Krys::KeyCode::KP4
#define KRYS_KEY_KP_5            ::Krys::KeyCode::KP5
#define KRYS_KEY_KP_6            ::Krys::KeyCode::KP6
#define KRYS_KEY_KP_7            ::Krys::KeyCode::KP7
#define KRYS_KEY_KP_8            ::Krys::KeyCode::KP8
#define KRYS_KEY_KP_9            ::Krys::KeyCode::KP9
#define KRYS_KEY_KP_DECIMAL      ::Krys::KeyCode::KPDecimal
#define KRYS_KEY_KP_DIVIDE       ::Krys::KeyCode::KPDivide
#define KRYS_KEY_KP_MULTIPLY     ::Krys::KeyCode::KPMultiply
#define KRYS_KEY_KP_SUBTRACT     ::Krys::KeyCode::KPSubtract
#define KRYS_KEY_KP_ADD          ::Krys::KeyCode::KPAdd
#define KRYS_KEY_KP_ENTER        ::Krys::KeyCode::KPEnter
#define KRYS_KEY_KP_EQUAL        ::Krys::KeyCode::KPEqual

#define KRYS_KEY_LEFT_SHIFT      ::Krys::KeyCode::LeftShift
#define KRYS_KEY_LEFT_CONTROL    ::Krys::KeyCode::LeftControl
#define KRYS_KEY_LEFT_ALT        ::Krys::KeyCode::LeftAlt
#define KRYS_KEY_LEFT_SUPER      ::Krys::KeyCode::LeftSuper
#define KRYS_KEY_RIGHT_SHIFT     ::Krys::KeyCode::RightShift
#define KRYS_KEY_RIGHT_CONTROL   ::Krys::KeyCode::RightControl
#define KRYS_KEY_RIGHT_ALT       ::Krys::KeyCode::RightAlt
#define KRYS_KEY_RIGHT_SUPER     ::Krys::KeyCode::RightSuper
#define KRYS_KEY_MENU            ::Krys::KeyCode::Menu