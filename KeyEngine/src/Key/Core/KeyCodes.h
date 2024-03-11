#pragma once

namespace Key
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

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
		Equal = 61, /* = */

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

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

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
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}
//form glfw3.h
/* The unknown key */
#define KEY_KEY_UNKNOWN            -1

// From glfw3.h
#define KEY_KEY_SPACE           ::Key::Key::Space
#define KEY_KEY_APOSTROPHE      ::Key::Key::Apostrophe    /* ' */
#define KEY_KEY_COMMA           ::Key::Key::Comma         /* , */
#define KEY_KEY_MINUS           ::Key::Key::Minus         /* - */
#define KEY_KEY_PERIOD          ::Key::Key::Period        /* . */
#define KEY_KEY_SLASH           ::Key::Key::Slash         /* / */
#define KEY_KEY_0               ::Key::Key::D0
#define KEY_KEY_1               ::Key::Key::D1
#define KEY_KEY_2               ::Key::Key::D2
#define KEY_KEY_3               ::Key::Key::D3
#define KEY_KEY_4               ::Key::Key::D4
#define KEY_KEY_5               ::Key::Key::D5
#define KEY_KEY_6               ::Key::Key::D6
#define KEY_KEY_7               ::Key::Key::D7
#define KEY_KEY_8               ::Key::Key::D8
#define KEY_KEY_9               ::Key::Key::D9
#define KEY_KEY_SEMICOLON       ::Key::Key::Semicolon     /* ; */
#define KEY_KEY_EQUAL           ::Key::Key::Equal         /* = */
#define KEY_KEY_A               ::Key::Key::A
#define KEY_KEY_B               ::Key::Key::B
#define KEY_KEY_C               ::Key::Key::C
#define KEY_KEY_D               ::Key::Key::D
#define KEY_KEY_E               ::Key::Key::E
#define KEY_KEY_F               ::Key::Key::F
#define KEY_KEY_G               ::Key::Key::G
#define KEY_KEY_H               ::Key::Key::H
#define KEY_KEY_I               ::Key::Key::I
#define KEY_KEY_J               ::Key::Key::J
#define KEY_KEY_K               ::Key::Key::K
#define KEY_KEY_L               ::Key::Key::L
#define KEY_KEY_M               ::Key::Key::M
#define KEY_KEY_N               ::Key::Key::N
#define KEY_KEY_O               ::Key::Key::O
#define KEY_KEY_P               ::Key::Key::P
#define KEY_KEY_Q               ::Key::Key::Q
#define KEY_KEY_R               ::Key::Key::R
#define KEY_KEY_S               ::Key::Key::S
#define KEY_KEY_T               ::Key::Key::T
#define KEY_KEY_U               ::Key::Key::U
#define KEY_KEY_V               ::Key::Key::V
#define KEY_KEY_W               ::Key::Key::W
#define KEY_KEY_X               ::Key::Key::X
#define KEY_KEY_Y               ::Key::Key::Y
#define KEY_KEY_Z               ::Key::Key::Z
#define KEY_KEY_LEFT_BRACKET    ::Key::Key::LeftBracket   /* [ */
#define KEY_KEY_BACKSLASH       ::Key::Key::Backslash     /* \ */
#define KEY_KEY_RIGHT_BRACKET   ::Key::Key::RightBracket  /* ] */
#define KEY_KEY_GRAVE_ACCENT    ::Key::Key::GraveAccent   /* ` */
#define KEY_KEY_WORLD_1         ::Key::Key::World1        /* non-US #1 */
#define KEY_KEY_WORLD_2         ::Key::Key::World2        /* non-US #2 */

/* Function keys */
#define KEY_KEY_ESCAPE          ::Key::Key::Escape
#define KEY_KEY_ENTER           ::Key::Key::Enter
#define KEY_KEY_TAB             ::Key::Key::Tab
#define KEY_KEY_BACKSPACE       ::Key::Key::Backspace
#define KEY_KEY_INSERT          ::Key::Key::Insert
#define KEY_KEY_DELETE          ::Key::Key::Delete
#define KEY_KEY_RIGHT           ::Key::Key::Right
#define KEY_KEY_LEFT            ::Key::Key::Left
#define KEY_KEY_DOWN            ::Key::Key::Down
#define KEY_KEY_UP              ::Key::Key::Up
#define KEY_KEY_PAGE_UP         ::Key::Key::PageUp
#define KEY_KEY_PAGE_DOWN       ::Key::Key::PageDown
#define KEY_KEY_HOME            ::Key::Key::Home
#define KEY_KEY_END             ::Key::Key::End
#define KEY_KEY_CAPS_LOCK       ::Key::Key::CapsLock
#define KEY_KEY_SCROLL_LOCK     ::Key::Key::ScrollLock
#define KEY_KEY_NUM_LOCK        ::Key::Key::NumLock
#define KEY_KEY_PRINT_SCREEN    ::Key::Key::PrintScreen
#define KEY_KEY_PAUSE           ::Key::Key::Pause
#define KEY_KEY_F1              ::Key::Key::F1
#define KEY_KEY_F2              ::Key::Key::F2
#define KEY_KEY_F3              ::Key::Key::F3
#define KEY_KEY_F4              ::Key::Key::F4
#define KEY_KEY_F5              ::Key::Key::F5
#define KEY_KEY_F6              ::Key::Key::F6
#define KEY_KEY_F7              ::Key::Key::F7
#define KEY_KEY_F8              ::Key::Key::F8
#define KEY_KEY_F9              ::Key::Key::F9
#define KEY_KEY_F10             ::Key::Key::F10
#define KEY_KEY_F11             ::Key::Key::F11
#define KEY_KEY_F12             ::Key::Key::F12
#define KEY_KEY_F13             ::Key::Key::F13
#define KEY_KEY_F14             ::Key::Key::F14
#define KEY_KEY_F15             ::Key::Key::F15
#define KEY_KEY_F16             ::Key::Key::F16
#define KEY_KEY_F17             ::Key::Key::F17
#define KEY_KEY_F18             ::Key::Key::F18
#define KEY_KEY_F19             ::Key::Key::F19
#define KEY_KEY_F20             ::Key::Key::F20
#define KEY_KEY_F21             ::Key::Key::F21
#define KEY_KEY_F22             ::Key::Key::F22
#define KEY_KEY_F23             ::Key::Key::F23
#define KEY_KEY_F24             ::Key::Key::F24
#define KEY_KEY_F25             ::Key::Key::F25

/* Keypad */
#define KEY_KEY_KP_0            ::Key::Key::KP0
#define KEY_KEY_KP_1            ::Key::Key::KP1
#define KEY_KEY_KP_2            ::Key::Key::KP2
#define KEY_KEY_KP_3            ::Key::Key::KP3
#define KEY_KEY_KP_4            ::Key::Key::KP4
#define KEY_KEY_KP_5            ::Key::Key::KP5
#define KEY_KEY_KP_6            ::Key::Key::KP6
#define KEY_KEY_KP_7            ::Key::Key::KP7
#define KEY_KEY_KP_8            ::Key::Key::KP8
#define KEY_KEY_KP_9            ::Key::Key::KP9
#define KEY_KEY_KP_DECIMAL      ::Key::Key::KPDecimal
#define KEY_KEY_KP_DIVIDE       ::Key::Key::KPDivide
#define KEY_KEY_KP_MULTIPLY     ::Key::Key::KPMultiply
#define KEY_KEY_KP_SUBTRACT     ::Key::Key::KPSubtract
#define KEY_KEY_KP_ADD          ::Key::Key::KPAdd
#define KEY_KEY_KP_ENTER        ::Key::Key::KPEnter
#define KEY_KEY_KP_EQUAL        ::Key::Key::KPEqual

#define KEY_KEY_LEFT_SHIFT      ::Key::Key::LeftShift
#define KEY_KEY_LEFT_CONTROL    ::Key::Key::LeftControl
#define KEY_KEY_LEFT_ALT        ::Key::Key::LeftAlt
#define KEY_KEY_LEFT_SUPER      ::Key::Key::LeftSuper
#define KEY_KEY_RIGHT_SHIFT     ::Key::Key::RightShift
#define KEY_KEY_RIGHT_CONTROL   ::Key::Key::RightControl
#define KEY_KEY_RIGHT_ALT       ::Key::Key::RightAlt
#define KEY_KEY_RIGHT_SUPER     ::Key::Key::RightSuper
#define KEY_KEY_MENU            ::Key::Key::Menu

// Mouse (TODO: move into separate file probably)
#define KEY_MOUSE_BUTTON_LEFT    0
#define KEY_MOUSE_BUTTON_RIGHT   1
#define KEY_MOUSE_BUTTON_MIDDLE  2