#include "../include/SlaskNamespace.h"

void slask::getKeyName(char *str, int keycode)
{
	std::string s;
	getKeyName(&s, keycode);
	strcpy(str, s.c_str());
}
void slask::getMouseName(char *str, int i)
{
	std::string s;
	getMouseName(&s, i);
	strcpy(str, s.c_str());
}

void slask::getKeyName(std::string *str, int keycode)
{
	if (keycode < 0 || keycode >= sf::Keyboard::Key::KeyCount)
	{
		std::string unhandledKey = "Reading key ";
		unhandledKey += std::to_string(keycode);
		unhandledKey += " name out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		*(str)="";
		return;
	}
	switch (keycode)
	{
	default:
		*(str) = "Key ";
		*(str) += std::to_string(keycode);
		break;
	case slask::Key::A:
		*(str) = "A";
		break;
	case slask::Key::B:
		*(str) = "B";
		break;
	case slask::Key::C:
		*(str) = "C";
		break;
	case slask::Key::D:
		*(str) = "D";
		break;
	case slask::Key::E:
		*(str) = "E";
		break;
	case slask::Key::F:
		*(str) = "F";
		break;
	case slask::Key::G:
		*(str) = "G";
		break;
	case slask::Key::H:
		*(str) = "H";
		break;
	case slask::Key::I:
		*(str) = "I";
		break;
	case slask::Key::J:
		*(str) = "J";
		break;
	case slask::Key::K:
		*(str) = "K";
		break;
	case slask::Key::L:
		*(str) = "L";
		break;
	case slask::Key::M:
		*(str) = "M";
		break;
	case slask::Key::N:
		*(str) = "N";
		break;
	case slask::Key::O:
		*(str) = "O";
		break;
	case slask::Key::P:
		*(str) = "P";
		break;
	case slask::Key::Q:
		*(str) = "Q";
		break;
	case slask::Key::R:
		*(str) = "R";
		break;
	case slask::Key::S:
		*(str) = "S";
		break;
	case slask::Key::T:
		*(str) = "T";
		break;
	case slask::Key::U:
		*(str) = "U";
		break;
	case slask::Key::V:
		*(str) = "V";
		break;
	case slask::Key::W:
		*(str) = "W";
		break;
	case slask::Key::X:
		*(str) = "X";
		break;
	case slask::Key::Y:
		*(str) = "Y";
		break;
	case slask::Key::Z:
		*(str) = "Z";
		break;
	case slask::Key::Num0:
		*(str) = "0";
		break;
	case slask::Key::Num1:
		*(str) = "1";
		break;
	case slask::Key::Num2:
		*(str) = "2";
		break;
	case slask::Key::Num3:
		*(str) = "3";
		break;
	case slask::Key::Num4:
		*(str) = "4";
		break;
	case slask::Key::Num5:
		*(str) = "5";
		break;
	case slask::Key::Num6:
		*(str) = "6";
		break;
	case slask::Key::Num7:
		*(str) = "7";
		break;
	case slask::Key::Num8:
		*(str) = "8";
		break;
	case slask::Key::Num9:
		*(str) = "9";
		break;
	case slask::Key::Left:
		*(str) = "Left";
		break;
	case slask::Key::Right:
		*(str) = "Right";
		break;
	case slask::Key::Up:
		*(str) = "Up";
		break;
	case slask::Key::Down:
		*(str) = "Down";
		break;
	case slask::Key::Escape:
		*(str) = "Escape";
		break;
	case slask::Key::LControl:
		*(str) = "Left Control";
		break;
	case slask::Key::RControl:
		*(str) = "Right Control";
		break;
	case slask::Key::LShift:
		*(str) = "Left Shift";
		break;
	case slask::Key::RShift:
		*(str) = "Right Shift";
		break;
	case slask::Key::LAlt:
		*(str) = "Left Alt";
		break;
	case slask::Key::RAlt:
		*(str) = "Right Alt";
		break;
	case slask::Key::LSystem:
		*(str) = "Left System";
		break;
	case slask::Key::RSystem:
		*(str) = "Right System";
		break;
	case slask::Key::Menu:
		*(str) = "Menu";
		break;
	case slask::Key::LBracket:
		*(str) = "[";
		break;
	case slask::Key::RBracket:
		*(str) = "]";
		break;
	case slask::Key::SemiColon:
		*(str) = ";";
		break;
	case slask::Key::Comma:
		*(str) = ",";
		break;
	case slask::Key::Period:
		*(str) = ".";
		break;
	case slask::Key::Quote:
		*(str) = "'";
		break;
	case slask::Key::Slash:
		*(str) = "/";
		break;
	case slask::Key::BackSlash:
		*(str) = "\\";
		break;
	case slask::Key::Tilde:
		*(str) = "~";
		break;
	case slask::Key::Equal:
		*(str) = "=";
		break;
	case slask::Key::Space:
		*(str) = "Space";
		break;
	case slask::Key::Return:
		*(str) = "Return";
		break;
	case slask::Key::BackSpace:
		*(str) = "Backspace";
		break;
	case slask::Key::Tab:
		*(str) = "Tab";
		break;
	case slask::Key::PageUp:
		*(str) = "Page Up";
		break;
	case slask::Key::PageDown:
		*(str) = "Page Down";
		break;
	case slask::Key::End:
		*(str) = "End";
		break;
	case slask::Key::Insert:
		*(str) = "Insert";
		break;
	case slask::Key::Delete:
		*(str) = "Delete";
		break;
	case slask::Key::Add:
		*(str) = "+";
		break;
	case slask::Key::Subtract:
		*(str) = "-";
		break;
	case slask::Key::Multiply:
		*(str) = "*";
		break;
	case slask::Key::Divide:
		*(str) = "Numpad /";
		break;
	case slask::Key::Numpad0:
		*(str) = "Numpad 0";
		break;
	case slask::Key::Numpad1:
		*(str) = "Numpad 1";
		break;
	case slask::Key::Numpad2:
		*(str) = "Numpad 2";
		break;
	case slask::Key::Numpad3:
		*(str) = "Numpad 3";
		break;
	case slask::Key::Numpad4:
		*(str) = "Numpad 4";
		break;
	case slask::Key::Numpad5:
		*(str) = "Numpad 5";
		break;
	case slask::Key::Numpad6:
		*(str) = "Numpad 6";
		break;
	case slask::Key::Numpad7:
		*(str) = "Numpad 7";
		break;
	case slask::Key::Numpad8:
		*(str) = "Numpad 8";
		break;
	case slask::Key::Numpad9:
		*(str) = "Numpad 9";
		break;
	case slask::Key::F1:
		*(str) = "F1";
		break;
	case slask::Key::F2:
		*(str) = "F2";
		break;
	case slask::Key::F3:
		*(str) = "F3";
		break;
	case slask::Key::F4:
		*(str) = "F4";
		break;
	case slask::Key::F5:
		*(str) = "F5";
		break;
	case slask::Key::F6:
		*(str) = "F6";
		break;
	case slask::Key::F7:
		*(str) = "F7";
		break;
	case slask::Key::F8:
		*(str) = "F8";
		break;
	case slask::Key::F9:
		*(str) = "F9";
		break;
	case slask::Key::F10:
		*(str) = "F10";
		break;
	case slask::Key::F11:
		*(str) = "F11";
		break;
	case slask::Key::F12:
		*(str) = "F12";
		break;
	case slask::Key::F13:
		*(str) = "F13";
		break;
	case slask::Key::F14:
		*(str) = "F14";
		break;
	case slask::Key::F15:
		*(str) = "F15";
		break;
	case slask::Key::Pause:
		*(str) = "Pause";
		break;
	}
}

void slask::getMouseName(std::string *str, int i)
{
	if (i < 0 || i >= _SLASK_MAXMOUSEBUTTONS)
	{
		std::string unhandledKey = "Reading mouse button ";
		unhandledKey += std::to_string(i);
		unhandledKey += " name out of range.";
		LogHandler::notify("Input", unhandledKey.c_str());
		*(str) = "";
		return;
	}
	switch (i)
	{
	default:
		*(str) = "Button ";
		*(str) += std::to_string(i);
		break;
	case slask::Mouse::MouseLeft:
		*(str) = "Left Mouse";
		break;
	case slask::Mouse::MouseRight:
		*(str) = "Right Mouse";
		break;
	case slask::Mouse::MouseMiddle:
		*(str) = "Middle Mouse";
		break;
	case slask::Mouse::Mouse4:
		*(str) = "Mouse 4";
		break;
	case slask::Mouse::Mouse5:
		*(str) = "Mouse 5";
		break;
	}
}