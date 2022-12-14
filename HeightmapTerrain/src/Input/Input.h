#pragma once
#include <GLFW/glfw3.h>
#include "Math/vec2.h"

namespace Height
{
	enum EKeyCode : uint16_t
	{
		HT_KEY_UNKNOWN = 0,


		HT_KEY_SPACE = GLFW_KEY_SPACE,

		HT_KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE  /* ' */,

		HT_KEY_COMMA = GLFW_KEY_COMMA  /* , */,

		HT_KEY_MINUS = GLFW_KEY_MINUS   /* - */,

		HT_KEY_PERIOD = GLFW_KEY_PERIOD   /* . */,

		HT_KEY_SLASH = GLFW_KEY_SLASH   /* / */,

		HT_KEY_0 = GLFW_KEY_0,

		HT_KEY_1 = GLFW_KEY_1,

		HT_KEY_2 = GLFW_KEY_2,

		HT_KEY_3 = GLFW_KEY_3,

		HT_KEY_4 = GLFW_KEY_4,

		HT_KEY_5 = GLFW_KEY_5,

		HT_KEY_6 = GLFW_KEY_6,

		HT_KEY_7 = GLFW_KEY_7,

		HT_KEY_8 = GLFW_KEY_8,

		HT_KEY_9 = GLFW_KEY_9,

		HT_KEY_SEMICOLON = GLFW_KEY_SEMICOLON,

		HT_KEY_EQUAL = GLFW_KEY_EQUAL,

		HT_KEY_A = GLFW_KEY_A,

		HT_KEY_B = GLFW_KEY_B,

		HT_KEY_C = GLFW_KEY_C,


		HT_KEY_D = GLFW_KEY_D,

		HT_KEY_E = GLFW_KEY_E,

		HT_KEY_F = GLFW_KEY_F,

		HT_KEY_G = GLFW_KEY_G,

		HT_KEY_H = GLFW_KEY_H,

		HT_KEY_I = GLFW_KEY_I,

		HT_KEY_J = GLFW_KEY_J,

		HT_KEY_K = GLFW_KEY_K,

		HT_KEY_L = GLFW_KEY_L,

		HT_KEY_M = GLFW_KEY_M,

		HT_KEY_N = GLFW_KEY_N,

		HT_KEY_O = GLFW_KEY_O,

		HT_KEY_P = GLFW_KEY_P,

		HT_KEY_Q = GLFW_KEY_Q,

		HT_KEY_R = GLFW_KEY_R,

		HT_KEY_S = GLFW_KEY_S,

		HT_KEY_T = GLFW_KEY_T,

		HT_KEY_U = GLFW_KEY_U,

		HT_KEY_V = GLFW_KEY_V,

		HT_KEY_W = GLFW_KEY_W,

		HT_KEY_X = GLFW_KEY_X,

		HT_KEY_Y = GLFW_KEY_Y,

		HT_KEY_Z = GLFW_KEY_Z,

		HT_KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,

		HT_KEY_BACKSLASH = GLFW_KEY_BACKSLASH,

		HT_KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,

		HT_KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,

		HT_KEY_WORLD_1 = GLFW_KEY_WORLD_1,

		HT_KEY_WORLD_2 = GLFW_KEY_WORLD_2,

		HT_KEY_ESCAPE = GLFW_KEY_ESCAPE,

		HT_KEY_ENTER = GLFW_KEY_ENTER,

		HT_KEY_TAB = GLFW_KEY_TAB,

		HT_KEY_BACKSPACE = GLFW_KEY_BACKSPACE,

		HT_KEY_INSERT = GLFW_KEY_INSERT,

		HT_KEY_DELETE = GLFW_KEY_DELETE,

		HT_KEY_RIGHT = GLFW_KEY_RIGHT,

		HT_KEY_LEFT = GLFW_KEY_LEFT,

		HT_KEY_DOWN = GLFW_KEY_DOWN,

		HT_KEY_UP = GLFW_KEY_UP,

		HT_KEY_PAGE_UP = GLFW_KEY_PAGE_UP,

		HT_KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,

		HT_KEY_HOME = GLFW_KEY_HOME,

		HT_KEY_END = GLFW_KEY_END,

		HT_KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,

		HT_KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,

		HT_KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,

		HT_KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,

		HT_KEY_PAUSE = GLFW_KEY_PAUSE,

		HT_KEY_F1 = GLFW_KEY_F1,

		HT_KEY_F2 = GLFW_KEY_F2,


		HT_KEY_F3 = GLFW_KEY_F3,

		HT_KEY_F4 = GLFW_KEY_F4,

		HT_KEY_F5 = GLFW_KEY_F5,

		HT_KEY_F6 = GLFW_KEY_F6,

		HT_KEY_F7 = GLFW_KEY_F7,

		HT_KEY_F8 = GLFW_KEY_F8,

		HT_KEY_F9 = GLFW_KEY_F9,

		HT_KEY_F10 = GLFW_KEY_F10,

		HT_KEY_F11 = GLFW_KEY_F11,

		HT_KEY_F12 = GLFW_KEY_F12,

		HT_KEY_F13 = GLFW_KEY_F13,

		HT_KEY_F14 = GLFW_KEY_F14,

		HT_KEY_F15 = GLFW_KEY_F15,

		HT_KEY_F16 = GLFW_KEY_F16,

		HT_KEY_F17 = GLFW_KEY_F17,

		HT_KEY_F18 = GLFW_KEY_F18,

		HT_KEY_F19 = GLFW_KEY_F19,

		HT_KEY_F20 = GLFW_KEY_F20,

		HT_KEY_F21 = GLFW_KEY_F21,

		HT_KEY_F22 = GLFW_KEY_F22,

		HT_KEY_F23 = GLFW_KEY_F23,

		HT_KEY_F24 = GLFW_KEY_F24,

		HT_KEY_F25 = GLFW_KEY_F25,

		HT_KEY_KP_0 = GLFW_KEY_KP_0,

		HT_KEY_KP_1 = GLFW_KEY_KP_1,

		HT_KEY_KP_2 = GLFW_KEY_KP_2,

		HT_KEY_KP_3 = GLFW_KEY_KP_3,

		HT_KEY_KP_4 = GLFW_KEY_KP_4,

		HT_KEY_KP_5 = GLFW_KEY_KP_5,

		HT_KEY_KP_6 = GLFW_KEY_KP_6,

		HT_KEY_KP_7 = GLFW_KEY_KP_7,

		HT_KEY_KP_8 = GLFW_KEY_KP_8,

		HT_KEY_KP_9 = GLFW_KEY_KP_9,

		HT_KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,

		HT_KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,

		HT_KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,

		HT_KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,

		HT_KEY_KP_ADD = GLFW_KEY_KP_ADD,

		HT_KEY_KP_ENTER = GLFW_KEY_KP_ENTER,

		HT_KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,

		HT_KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,

		HT_KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,

		HT_KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,

		HT_KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,

		HT_KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,

		HT_KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,

		HT_KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,

		HT_KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,

		HT_KEY_MENU = GLFW_KEY_MENU,

		HT_KEY_LAST = HT_KEY_MENU
	};

	enum MouseButtonsCode : uint8_t
	{
		HT_MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1,
		HT_MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2,
		HT_MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3,
		HT_MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,
		HT_MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,
		HT_MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,
		HT_MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,
		HT_MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8,
		HT_MOUSE_BUTTON_LAST = GLFW_MOUSE_BUTTON_LAST,
		HT_MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
		HT_MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
		HT_MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
	};

	class Input
	{
	public:
		static bool IsKeyPressed(EKeyCode kc);
		static bool IsMouseButtonPressed(MouseButtonsCode mb);
		static void HideAndLockCursor(bool cond);
		static vec2 GetMousePosition();
		static void SetCursorPosition(int x, int y);
	};

}