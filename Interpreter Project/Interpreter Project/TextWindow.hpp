#ifndef TEXTWINDOW_HPP
#define TEXTWINDOW_HPP


#include "Value.hpp"

#include <vector>
#include <iostream>
#include <string>

namespace TextWindow {

	Value Set_ForegroundColor(Value arg, bool& error, std::string& error_message);
	Value Get_ForegroundColor();

	Value Set_BackgroundColor(Value arg, bool& error, std::string& error_message);
	Value Get_BackgroundColor();

	Value Set_CursorLeft(Value arg, bool& error, std::string& error_message);
	Value Get_CursorLeft();

	Value Set_CursorTop(Value arg, bool& error, std::string& error_message);
	Value Get_CursorTop();


	Value Set_Title(Value arg, bool& error, std::string& error_message);
	Value Get_Title();


	//TextWindow.Show()
	Value Show(std::vector<Value> args, bool& error, std::string& error_message);

	//TextWindow.Hide()
	Value Hide(std::vector<Value> args, bool& error, std::string& error_message);

	//TextWindow.Clear()
	Value Clear(std::vector<Value> args, bool& error, std::string& error_message);

	//TextWindow.Pause()
	Value Pause(std::vector<Value> args, bool& error, std::string& error_message);

	//TextWindow.PauseIfVisible()
	Value PauseIfVisible(std::vector<Value> args, bool& error, std::string& error_message);

	//TextWindow.PauseWithoutMessage()
	Value PauseWithoutMessage(std::vector<Value> args, bool& error, std::string& error_message);

	//TextWindow.Read()
	Value Read(std::vector<Value> args, bool& error, std::string& error_message);

	//TextWindow.ReadNumber()
	Value ReadNumber(std::vector<Value> args, bool& error, std::string& error_message);

	//TextWindow.WriteLine(data)
	Value WriteLine(std::vector<Value> args, bool& error, std::string& error_message);

	//TextWindow.Write(data)
	Value Write(std::vector<Value> args, bool& error, std::string& error_message);

	

}

#endif