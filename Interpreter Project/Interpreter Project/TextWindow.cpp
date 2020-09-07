#include "TextWindow.hpp"

#include <Windows.h>
#include <algorithm>

#include "Libs\conmanip.h"

namespace TextWindow {
	namespace Internal {
		conmanip::console_out_context ctxout;
		conmanip::console_out conout(ctxout);

		//colors
		Value fg_color = Value("white");//foreground color
		Value bg_color = Value("black");//background color
	}
}


bool ConsoleOpen = true;

//TextWindow.Show()
Value TextWindow::Show(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 0) {
		error = true;
		error_message = "Program Error - TextWindow.Show expects no arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (!ConsoleOpen) {
		AllocConsole();
		ConsoleOpen = true;
	}
	return Value();
}

//TextWindow.Hide()
Value TextWindow::Hide(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 0) {
		error = true;
		error_message = "Program Error - TextWindow.Hide expects no arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (ConsoleOpen) {
		FreeConsole();
		ConsoleOpen = false;
	}
	return Value();
}

//TextWindow.Clear()
Value TextWindow::Clear(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 0) {
		error = true;
		error_message = "Program Error - TextWindow.Clear expects no arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	system("cls");
	return Value();
}

//TextWindow.Pause()
Value TextWindow::Pause(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 0) {
		error = true;
		error_message = "Program Error - TextWindow.Pause expects no arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	system("pause");
	return Value();
}

//TextWindow.PauseIfVisible()
Value TextWindow::PauseIfVisible(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 0) {
		error = true;
		error_message = "Program Error - TextWindow.PauseIfVisible expects no arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (ConsoleOpen) {
		system("pause");
	}
	return Value();
}

//TextWindow.PauseWithoutMessage()
Value TextWindow::PauseWithoutMessage(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 0) {
		error = true;
		error_message = "Program Error - TextWindow.PauseWithoutMessage expects no arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	std::string tmp;
	std::cin >> tmp;
	return Value();
}

Value TextWindow::Read(std::vector<Value> args, bool& error, std::string& error_message) {

	if (args.size() != 0) {
		error = true;
		error_message = "Program Error - TextWindow.Read expects 0 arguments but was passed " + std::to_string(args.size());
		return Value();
	}

	std::string input;
	std::cin >> input;

	//eat the enter key that is pressed to enter the text
	std::cin.get();

	return Value(input);
}

//TextWindow.ReadNumber()
Value TextWindow::ReadNumber(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 0) {
		error = true;
		error_message = "Program Error - TextWindow.ReadNumber expects no arguments but was passed " + std::to_string(args.size());
		return Value();
	}

	//TOD test the string to check that it is a number
	std::string str;
	std::cin >> str;
	return Value(std::stoll(str));
}

//TextWindow.WriteLine(data)
Value TextWindow::WriteLine(std::vector<Value> args, bool& error, std::string& error_message) {

	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - TextWindow.WriteLine expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}

	switch (args[0].Get_Type())
	{
	case Value::INT:
		std::cout << args[0].Get_Int() << std::endl;
		break;
	case Value::FLOAT:
		std::cout << args[0].Get_Float() << std::endl;
		break;
	case Value::STRING:
		std::cout << args[0].Get_String() << std::endl;
		break;
	case Value::BOOLEAN:
		std::cout << args[0].Get_Bool() << std::endl;
		break;
	case Value::NONE:
		std::cout << std::endl;
		break;
	default:
		break;
	}
	return Value();
}

//TextWindow.Write(data)
Value TextWindow::Write(std::vector<Value> args, bool& error, std::string& error_message) {

	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - TextWindow.Write expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}

	switch (args[0].Get_Type())
	{
	case Value::INT:
		std::cout << args[0].Get_Int();
		break;
	case Value::FLOAT:
		std::cout << args[0].Get_Float();
		break;
	case Value::STRING:
		std::cout << args[0].Get_String();
		break;
	case Value::BOOLEAN:
		std::cout << args[0].Get_Bool();
		break;
	case Value::NONE:
		break;
	default:
		break;
	}
	return Value();
}

//TODO test and fix
Value TextWindow::Set_ForegroundColor(Value arg, bool& error, std::string& error_message) {
	if (arg.Get_Type() != Value::INT && arg.Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Type mismatch trying to set TextWindow.ForegroundColor";
		return Value();
	}
	else if (arg.Get_Type() == Value::INT) {
		if (arg.Get_Int() >= 0 && arg.Get_Int() <= 15) {
			Internal::conout.settextcolor((conmanip::console_text_colors)arg.Get_Int());
			Internal::fg_color = arg;
			return arg;
		}
		else {
			error = true;
			error_message = "Program Error - when setting TextWindow.ForegroundColor with integer the number must be between 0 and 15";
			return Value();
		}
	}
	else /*Value::STRING*/{
		std::string str = arg.Get_String();
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		if (str == "black") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x00);
		}
		else if (str == "blue") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x01);
		}
		else if (str == "green") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x02);
		}
		else if (str == "cyan") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x03);
		}
		else if (str == "red") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x04);
		}
		else if (str == "magenta") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x05);
		}
		else if (str == "brown") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x06);
		}
		else if (str == "light gray") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x07);
		}
		else if (str == "dark gray") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x08);
		}
		else if (str == "light blue") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x09);
		}
		else if (str == "light green") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x0A);
		}
		else if (str == "light cyan") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x0B);
		}
		else if (str == "light red") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x0C);
		}
		else if (str == "light magenta") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x0D);
		}
		else if (str == "yellow") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x0E);
		}
		else if (str == "white") {
			Internal::conout.settextcolor((conmanip::console_text_colors)0x0F);
		}
		else {
			error = true;
			error_message = "Program Error - Unknown color used when setting TextWindow.ForegroundColor";
			return Value();
		}
		Internal::fg_color = arg;
		return arg;
	}
}

Value TextWindow::Get_ForegroundColor() {
	return Internal::fg_color;
}

//TODO test and fix
Value TextWindow::Set_BackgroundColor(Value arg, bool& error, std::string& error_message) {
	if (arg.Get_Type() != Value::INT && arg.Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Type mismatch trying to set TextWindow.BackgroundColor";
		return Value();
	}
	else if (arg.Get_Type() == Value::INT) {
		if (arg.Get_Int() >= 0 && arg.Get_Int() <= 15) {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)arg.Get_Int());
			Internal::bg_color = arg;
			return arg;
		}
		else {
			error = true;
			error_message = "Program Error - when setting TextWindow.BackgroundColor with integer the number must be between 0 and 15";
			return Value();
		}
	}
	else /*Value::STRING*/ {
		std::string str = arg.Get_String();
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		if (str == "black") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x00);
		}
		else if (str == "blue") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x01);
		}
		else if (str == "green") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x02);
		}
		else if (str == "cyan") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x03);
		}
		else if (str == "red") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x04);
		}
		else if (str == "magenta") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x05);
		}
		else if (str == "brown") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x06);
		}
		else if (str == "light gray") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x07);
		}
		else if (str == "dark gray") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x08);
		}
		else if (str == "light blue") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x09);
		}
		else if (str == "light green") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x0A);
		}
		else if (str == "light cyan") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x0B);
		}
		else if (str == "light red") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x0C);
		}
		else if (str == "light magenta") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x0D);
		}
		else if (str == "yellow") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x0E);
		}
		else if (str == "white") {
			Internal::conout.setbgcolor((conmanip::console_bg_colors)0x0F);
		}
		else {
			error = true;
			error_message = "Program Error - Unknown color used when setting TextWindow.BackgroundColor";
			return Value();
		}
		Internal::bg_color = arg;
		return arg;
	}
}

Value TextWindow::Get_BackgroundColor() {
	return Internal::bg_color;
}

Value TextWindow::Set_CursorLeft(Value arg, bool& error, std::string& error_message) {
	if (arg.Get_Type() != Value::INT) {
		error = true;
		error_message = "Program Error - An integer must be used to set TextWindow.CursorLeft";
		return Value();
	}
	Internal::conout.setposx(arg.Get_Int());
	return arg;
}

Value TextWindow::Get_CursorLeft() {
	return Value((int64_t)Internal::conout.getposx());
}

Value TextWindow::Set_CursorTop(Value arg, bool& error, std::string& error_message) {
	if (arg.Get_Type() != Value::INT) {
		error = true;
		error_message = "Program Error - An integer must be used to set TextWindow.CursorTop";
		return Value();
	}
	Internal::conout.setposy(arg.Get_Int());
	return arg;
}

Value TextWindow::Get_CursorTop() {
	return Value((int64_t)Internal::conout.getposy());
}

Value TextWindow::Set_Title(Value arg, bool& error, std::string& error_message) {
	switch (arg.Get_Type())
	{
	case Value::INT:
		Internal::conout.settitle(std::to_string(arg.Get_Int()));
		break;
	case Value::FLOAT:
		Internal::conout.settitle(std::to_string(arg.Get_Float()));
		break;
	case Value::BOOLEAN:
		Internal::conout.settitle(std::to_string(arg.Get_Bool()));
		break;
	case Value::STRING:
		Internal::conout.settitle(arg.Get_String());
		break;
	default:
		Internal::conout.settitle("");
		break;
	}
	return arg;
}

Value TextWindow::Get_Title() {
	return Value(Internal::conout.gettitle());
}
