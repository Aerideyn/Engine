#pragma once
namespace Services
{
	namespace KeyboardKey
	{
		enum KeyboardKey
		{
			Unknown = -1, ///< Unhandled key
			A = 65,        ///< The A key
			B = 66,            ///< The B key
			C = 67,            ///< The C key
			D = 68,            ///< The D key
			E = 69,            ///< The E key
			F = 70,            ///< The F key
			G = 71,            ///< The G key
			H = 72,            ///< The H key
			I = 73,            ///< The I key
			J = 74,            ///< The J key
			K = 75,            ///< The K key
			L = 76,            ///< The L key
			M = 77,            ///< The M key
			N = 78,            ///< The N key
			O = 79,            ///< The O key
			P = 80,            ///< The P key
			Q = 81,            ///< The Q key
			R = 82,            ///< The R key
			S = 83,            ///< The S key
			T = 84,            ///< The T key
			U = 85,            ///< The U key
			V = 86,            ///< The V key
			W = 87,            ///< The W key
			X = 88,            ///< The X key
			Y = 89,            ///< The Y key
			Z = 90,            ///< The Z key
			Num0,         ///< The 0 key
			Num1,         ///< The 1 key
			Num2,         ///< The 2 key
			Num3,         ///< The 3 key
			Num4,         ///< The 4 key
			Num5,         ///< The 5 key
			Num6,         ///< The 6 key
			Num7,         ///< The 7 key
			Num8,         ///< The 8 key
			Num9,         ///< The 9 key
			Escape = 256,       ///< The Escape key
			LControl,     ///< The left Control key
			LShift,       ///< The left Shift key
			LAlt,         ///< The left Alt key
			LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
			RControl,     ///< The right Control key
			RShift,       ///< The right Shift key
			RAlt,         ///< The right Alt key
			RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
			Menu,         ///< The Menu key
			LBracket,     ///< The [ key
			RBracket,     ///< The ] key
			SemiColon,    ///< The ; key
			Comma,        ///< The , key
			Period,       ///< The . key
			Quote,        ///< The ' key
			Slash,        ///< The / key
			BackSlash,    ///< The \ key
			Tilde,        ///< The ~ key
			Equal,        ///< The = key
			Dash,         ///< The - key
			Space,        ///< The Space key
			Return = 257,       ///< The Return key
			BackSpace,    ///< The Backspace key
			Tab,          ///< The Tabulation key
			PageUp,       ///< The Page up key
			PageDown,     ///< The Page down key
			End,          ///< The End key
			Home,         ///< The Home key
			Insert,       ///< The Insert key
			Delete,       ///< The Delete key
			Add = 334,          ///< The + key
			Subtract = 333,     ///< The - key
			Multiply,     ///< The * key
			Divide,       ///< The / key
			Left,         ///< Left arrow
			Right,        ///< Right arrow
			Up,           ///< Up arrow
			Down,         ///< Down arrow
			Numpad0,      ///< The numpad 0 key
			Numpad1,      ///< The numpad 1 key
			Numpad2,      ///< The numpad 2 key
			Numpad3,      ///< The numpad 3 key
			Numpad4,      ///< The numpad 4 key
			Numpad5,      ///< The numpad 5 key
			Numpad6,      ///< The numpad 6 key
			Numpad7,      ///< The numpad 7 key
			Numpad8,      ///< The numpad 8 key
			Numpad9,      ///< The numpad 9 key
			F1,           ///< The F1 key
			F2,           ///< The F2 key
			F3,           ///< The F3 key
			F4,           ///< The F4 key
			F5,           ///< The F5 key
			F6,           ///< The F6 key
			F7,           ///< The F7 key
			F8,           ///< The F8 key
			F9,           ///< The F9 key
			F10,          ///< The F10 key
			F11,          ///< The F11 key
			F12,          ///< The F12 key
			F13,          ///< The F13 key
			F14,          ///< The F14 key
			F15,          ///< The F15 key
			Pause,        ///< The Pause key

			KeyCount      ///< Keep last -- the total number of keyboard keys
		};
	}

	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard();
	public:
		static bool IsKeyDown(KeyboardKey::KeyboardKey key);
	};
}