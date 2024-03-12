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
	} Keys;

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
#define KEY_KEY_SPACE           ::Key::Keys::Space
#define KEY_KEY_APOSTROPHE      ::Key::Keys::Apostrophe    /* ' */
#define KEY_KEY_COMMA           ::Key::Keys::Comma         /* , */
#define KEY_KEY_MINUS           ::Key::Keys::Minus         /* - */
#define KEY_KEY_PERIOD          ::Key::Keys::Period        /* . */
#define KEY_KEY_SLASH           ::Key::Keys::Slash         /* / */
#define KEY_KEY_0               ::Key::Keys::D0
#define KEY_KEY_1               ::Key::Keys::D1
#define KEY_KEY_2               ::Key::Keys::D2
#define KEY_KEY_3               ::Key::Keys::D3
#define KEY_KEY_4               ::Key::Keys::D4
#define KEY_KEY_5               ::Key::Keys::D5
#define KEY_KEY_6               ::Key::Keys::D6
#define KEY_KEY_7               ::Key::Keys::D7
#define KEY_KEY_8               ::Key::Keys::D8
#define KEY_KEY_9               ::Key::Keys::D9
#define KEY_KEY_SEMICOLON       ::Key::Keys::Semicolon     /* ; */
#define KEY_KEY_EQUAL           ::Key::Keys::Equal         /* = */
#define KEY_KEY_A               ::Key::Keys::A
#define KEY_KEY_B               ::Key::Keys::B
#define KEY_KEY_C               ::Key::Keys::C
#define KEY_KEY_D               ::Key::Keys::D
#define KEY_KEY_E               ::Key::Keys::E
#define KEY_KEY_F               ::Key::Keys::F
#define KEY_KEY_G               ::Key::Keys::G
#define KEY_KEY_H               ::Key::Keys::H
#define KEY_KEY_I               ::Key::Keys::I
#define KEY_KEY_J               ::Key::Keys::J
#define KEY_KEY_K               ::Key::Keys::K
#define KEY_KEY_L               ::Key::Keys::L
#define KEY_KEY_M               ::Key::Keys::M
#define KEY_KEY_N               ::Key::Keys::N
#define KEY_KEY_O               ::Key::Keys::O
#define KEY_KEY_P               ::Key::Keys::P
#define KEY_KEY_Q               ::Key::Keys::Q
#define KEY_KEY_R               ::Key::Keys::R
#define KEY_KEY_S               ::Key::Keys::S
#define KEY_KEY_T               ::Key::Keys::T
#define KEY_KEY_U               ::Key::Keys::U
#define KEY_KEY_V               ::Key::Keys::V
#define KEY_KEY_W               ::Key::Keys::W
#define KEY_KEY_X               ::Key::Keys::X
#define KEY_KEY_Y               ::Key::Keys::Y
#define KEY_KEY_Z               ::Key::Keys::Z
#define KEY_KEY_LEFT_BRACKET    ::Key::Keys::LeftBracket   /* [ */
#define KEY_KEY_BACKSLASH       ::Key::Keys::Backslash     /* \ */
#define KEY_KEY_RIGHT_BRACKET   ::Key::Keys::RightBracket  /* ] */
#define KEY_KEY_GRAVE_ACCENT    ::Key::Keys::GraveAccent   /* ` */
#define KEY_KEY_WORLD_1         ::Key::Keys::World1        /* non-US #1 */
#define KEY_KEY_WORLD_2         ::Key::Keys::World2        /* non-US #2 */

/* Function keys */
#define KEY_KEY_ESCAPE          ::Key::Keys::Escape
#define KEY_KEY_ENTER           ::Key::Keys::Enter
#define KEY_KEY_TAB             ::Key::Keys::Tab
#define KEY_KEY_BACKSPACE       ::Key::Keys::Backspace
#define KEY_KEY_INSERT          ::Key::Keys::Insert
#define KEY_KEY_DELETE          ::Key::Keys::Delete
#define KEY_KEY_RIGHT           ::Key::Keys::Right
#define KEY_KEY_LEFT            ::Key::Keys::Left
#define KEY_KEY_DOWN            ::Key::Keys::Down
#define KEY_KEY_UP              ::Key::Keys::Up
#define KEY_KEY_PAGE_UP         ::Key::Keys::PageUp
#define KEY_KEY_PAGE_DOWN       ::Key::Keys::PageDown
#define KEY_KEY_HOME            ::Key::Keys::Home
#define KEY_KEY_END             ::Key::Keys::End
#define KEY_KEY_CAPS_LOCK       ::Key::Keys::CapsLock
#define KEY_KEY_SCROLL_LOCK     ::Key::Keys::ScrollLock
#define KEY_KEY_NUM_LOCK        ::Key::Keys::NumLock
#define KEY_KEY_PRINT_SCREEN    ::Key::Keys::PrintScreen
#define KEY_KEY_PAUSE           ::Key::Keys::Pause
#define KEY_KEY_F1              ::Key::Keys::F1
#define KEY_KEY_F2              ::Key::Keys::F2
#define KEY_KEY_F3              ::Key::Keys::F3
#define KEY_KEY_F4              ::Key::Keys::F4
#define KEY_KEY_F5              ::Key::Keys::F5
#define KEY_KEY_F6              ::Key::Keys::F6
#define KEY_KEY_F7              ::Key::Keys::F7
#define KEY_KEY_F8              ::Key::Keys::F8
#define KEY_KEY_F9              ::Key::Keys::F9
#define KEY_KEY_F10             ::Key::Keys::F10
#define KEY_KEY_F11             ::Key::Keys::F11
#define KEY_KEY_F12             ::Key::Keys::F12
#define KEY_KEY_F13             ::Key::Keys::F13
#define KEY_KEY_F14             ::Key::Keys::F14
#define KEY_KEY_F15             ::Key::Keys::F15
#define KEY_KEY_F16             ::Key::Keys::F16
#define KEY_KEY_F17             ::Key::Keys::F17
#define KEY_KEY_F18             ::Key::Keys::F18
#define KEY_KEY_F19             ::Key::Keys::F19
#define KEY_KEY_F20             ::Key::Keys::F20
#define KEY_KEY_F21             ::Key::Keys::F21
#define KEY_KEY_F22             ::Key::Keys::F22
#define KEY_KEY_F23             ::Key::Keys::F23
#define KEY_KEY_F24             ::Key::Keys::F24
#define KEY_KEY_F25             ::Key::Keys::F25

/* Keypad */
#define KEY_KEY_KP_0            ::Key::Keys::KP0
#define KEY_KEY_KP_1            ::Key::Keys::KP1
#define KEY_KEY_KP_2            ::Key::Keys::KP2
#define KEY_KEY_KP_3            ::Key::Keys::KP3
#define KEY_KEY_KP_4            ::Key::Keys::KP4
#define KEY_KEY_KP_5            ::Key::Keys::KP5
#define KEY_KEY_KP_6            ::Key::Keys::KP6
#define KEY_KEY_KP_7            ::Key::Keys::KP7
#define KEY_KEY_KP_8            ::Key::Keys::KP8
#define KEY_KEY_KP_9            ::Key::Keys::KP9
#define KEY_KEY_KP_DECIMAL      ::Key::Keys::KPDecimal
#define KEY_KEY_KP_DIVIDE       ::Key::Keys::KPDivide
#define KEY_KEY_KP_MULTIPLY     ::Key::Keys::KPMultiply
#define KEY_KEY_KP_SUBTRACT     ::Key::Keys::KPSubtract
#define KEY_KEY_KP_ADD          ::Key::Keys::KPAdd
#define KEY_KEY_KP_ENTER        ::Key::Keys::KPEnter
#define KEY_KEY_KP_EQUAL        ::Key::Keys::KPEqual
										  
#define KEY_KEY_LEFT_SHIFT      ::Key::Keys::LeftShift
#define KEY_KEY_LEFT_CONTROL    ::Key::Keys::LeftControl
#define KEY_KEY_LEFT_ALT        ::Key::Keys::LeftAlt
#define KEY_KEY_LEFT_SUPER      ::Key::Keys::LeftSuper
#define KEY_KEY_RIGHT_SHIFT     ::Key::Keys::RightShift
#define KEY_KEY_RIGHT_CONTROL   ::Key::Keys::RightControl
#define KEY_KEY_RIGHT_ALT       ::Key::Keys::RightAlt
#define KEY_KEY_RIGHT_SUPER     ::Key::Keys::RightSuper
#define KEY_KEY_MENU            ::Key::Keys::Menu

// Mouse (TODO: move into separate file probably)
#define KEY_MOUSE_BUTTON_LEFT    0
#define KEY_MOUSE_BUTTON_RIGHT   1
#define KEY_MOUSE_BUTTON_MIDDLE  2