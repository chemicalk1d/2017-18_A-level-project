#include "Interpreter.hpp"

#include "Methods.hpp"

Object TextWindowInit() {
	Object text_window;
	text_window.SetName("TextWindow");

	text_window.AddMethod("Show", TextWindow::Show);
	text_window.AddMethod("Hide", TextWindow::Hide);
	text_window.AddMethod("Clear", TextWindow::Clear);
	text_window.AddMethod("Pause", TextWindow::Pause);
	text_window.AddMethod("PauseIfVisible", TextWindow::PauseIfVisible);
	text_window.AddMethod("PauseWithoutMessage", TextWindow::PauseWithoutMessage);
	text_window.AddMethod("Read", TextWindow::Read);
	text_window.AddMethod("ReadNumber", TextWindow::ReadNumber);
	text_window.AddMethod("WriteLine", TextWindow::WriteLine);
	text_window.AddMethod("Write", TextWindow::Write);

	Object::Property prop;
	prop.getter = TextWindow::Get_Title;
	prop.setter = TextWindow::Set_Title;
	text_window.AddProperty("title", prop);

	prop.getter = TextWindow::Get_ForegroundColor;
	prop.setter = TextWindow::Set_ForegroundColor;
	text_window.AddProperty("ForegroundColor", prop);

	prop.getter = TextWindow::Get_BackgroundColor;
	prop.setter = TextWindow::Set_BackgroundColor;
	text_window.AddProperty("BackgroundColor", prop);

	prop.getter = TextWindow::Get_CursorLeft;
	prop.setter = TextWindow::Set_CursorLeft;
	text_window.AddProperty("CursorLeft", prop);

	prop.getter = TextWindow::Get_CursorTop;
	prop.setter = TextWindow::Set_CursorTop;
	text_window.AddProperty("CursorTop", prop);

	return text_window;
}

Object TextInit() {
	Object text;

	text.AddMethod("Append", Text::Append);
	text.AddMethod("GetLength", Text::GetLength);
	text.AddMethod("IsSubText", Text::IsSubText);
	text.AddMethod("EndsWith", Text::EndsWith);
	text.AddMethod("StartsWith", Text::StartsWith);
	text.AddMethod("GetSubText", Text::GetSubText);
	text.AddMethod("GetSubTextToEnd", Text::GetSubTextToEnd);
	text.AddMethod("GetIndexOf", Text::GetIndexOf);
	text.AddMethod("ConvertToLowerCase", Text::ConvertToLowerCase);
	text.AddMethod("ConvertToUpperCase", Text::ConvertToUpperCase);
	text.AddMethod("GetCharacter", Text::GetCharacter);
	text.AddMethod("GetCharacterCode", Text::GetCharacterCode);
	return text;
}

Object TimerInit() {
	return Object();
}

Object StackInit() {
	Object stack;

	stack.AddMethod("GetCount", Stack::GetCount);
	stack.AddMethod("PopValue", Stack::PopValue);
	stack.AddMethod("PushValue", Stack::PushValue);

	return stack;
}

Object ProgramInit() {
	Object program;

	program.AddMethod("Delay", Program::Delay);
	program.AddMethod("End", Program::End);

	return program;
}

Object MathInit() {
	Object maths;

	maths.AddMethod("Abs", Math::Abs);
	maths.AddMethod("Ceiling", Math::Ceiling);
	maths.AddMethod("Floor", Math::Floor);
	maths.AddMethod("NaturalLog", Math::NaturalLog);
	maths.AddMethod("Log", Math::Log);
	maths.AddMethod("Cos", Math::Cos);
	maths.AddMethod("Sin", Math::Sin);
	maths.AddMethod("Tan", Math::Tan);
	maths.AddMethod("ArcSin", Math::ArcSin);
	maths.AddMethod("ArcCos", Math::ArcCos);
	maths.AddMethod("ArcTan", Math::ArcTan);
	maths.AddMethod("GetDegrees", Math::GetDegrees);
	maths.AddMethod("GetRadians", Math::GetRadians);
	maths.AddMethod("SquareRoot", Math::SquareRoot);
	maths.AddMethod("Power", Math::Power);
	maths.AddMethod("Round", Math::Round);
	maths.AddMethod("Max", Math::Max);
	maths.AddMethod("Min", Math::Min);
	maths.AddMethod("Remainder", Math::Remainder);
	maths.AddMethod("GetRandomNumber", Math::GetRandomNumber);
	
	Object::Property prop;
	prop.getter = Math::Get_Pi;
	prop.setter = NULL;
	maths.AddProperty("PI", prop);
	return maths;
}

Object FileInit() {
	Object file;

	file.AddMethod("ReadContents", File::ReadContents);
	file.AddMethod("WriteContents", File::WriteContents);

	Object::Property prop;
	prop.getter = File::Get_LastError;
	prop.setter = NULL;

	file.AddProperty("LastError", prop);

	return file;
}

Object ClockInit() {
	Object obj;

	obj.SetName("Clock");

	Object::Property prop;
	prop.setter = NULL;

	prop.getter = Clock::Get_Time;
	obj.AddProperty("Time", prop);

	prop.getter = Clock::Get_Date;
	obj.AddProperty("Date", prop);

	prop.getter = Clock::Get_Year;
	obj.AddProperty("Year", prop);

	prop.getter = Clock::Get_Month;
	obj.AddProperty("Month", prop);

	prop.getter = Clock::Get_Day;
	obj.AddProperty("Day", prop);

	prop.getter = Clock::Get_WeekDay;
	obj.AddProperty("WeekDay", prop);

	prop.getter = Clock::Get_Hour;
	obj.AddProperty("Hour", prop);

	prop.getter = Clock::Get_Minute;
	obj.AddProperty("Minute", prop);

	prop.getter = Clock::Get_Second;
	obj.AddProperty("Second", prop);

	return obj;
}

Object QueueInit() {
	Object queue;

	queue.SetName("Queue");

	queue.AddMethod("PushValue", Queue::PushValue);
	queue.AddMethod("GetCount", Queue::GetCount);
	queue.AddMethod("PopValue", Queue::PopValue);

	return queue;
}

Object ListInit() {
	Object list;

	list.SetName("List");

	list.AddMethod("Append", List::Append);
	list.AddMethod("Insert", List::Insert);
	list.AddMethod("Remove", List::Remove);
	list.AddMethod("Delete", List::Delete);
	list.AddMethod("Get", List::Get);
	list.AddMethod("Size", List::Size);
	list.AddMethod("Clear", List::Clear);

	return list;
}

void Interpreter::SetupObjects() {
	Object obj;

	obj = ClockInit();
	objects["Clock"] = obj;

	obj = FileInit();
	objects["File"] = obj;

	obj = MathInit();
	objects["Math"] = obj;

	obj = ProgramInit();
	objects["Program"] = obj;

	obj = StackInit();
	objects["Stack"] = obj;

	obj = TextInit();
	objects["Text"] = obj;

	obj = TextWindowInit();
	objects["TextWindow"] = obj;

	obj = TimerInit();
	objects["Timer"] = obj;

	obj = ListInit();
	objects["List"] = obj;

	obj = QueueInit();
	objects["Queue"] = obj;
}


//goes through and finds each statement that is a label statement and adds it to the map of labels
void Interpreter::LabelPass(Statement* st) {

	if (st->GetStatementType() == "Expression Statement") {
		//do nothing
	}
	else if (st->GetStatementType() == "Label Statement") {
		LabelPassLabelStatement((LabelStatement*)st);
	}
	else if (st->GetStatementType() == "Goto Statement") {
		//do nothing
	}
	else if (st->GetStatementType() == "If Statement") {
		LabelPassIfStatement((IfStatement*)st);
	}
	else if (st->GetStatementType() == "While Loop") {
		LabelPassWhileLoop((WhileLoop*)st);
	}
	else if (st->GetStatementType() == "For Loop") {
		LabelPassForLoop((ForLoop*)st);
	}
	else if (st->GetStatementType() == "Subroutine") {
		LabelPassSubroutine((Subroutine*)st);
	}
}

void Interpreter::LabelPassLabelStatement(LabelStatement* st) {
	//get the labels name
	LabelStatement* ls = (LabelStatement*)st;
	std::string name = ls->GetName();

	//check if a label with that name has already been added
	auto ptr = labels.find(name);
	if (ptr != labels.end()) {
		runtime_error = true;
		error_message += "Program error at line " + std::to_string(ls->GetLineNumber()) + "\n";
		error_message += "More than one label with the same name";
		return;
	}
	//else

	//add label to map of labels
	labels[name] = ls;
}

void Interpreter::LabelPassIfStatement(IfStatement* st){
	IfStatement* if_st = (IfStatement*)st;

	//go through all the subcode in the if clause to check for labels
	for (auto st2 : if_st->GetStatements()) {
		LabelPass(st2);
	}

	//go through each else if and the subcode to check for labels
	for (auto el_if : if_st->GetElseIfClauses()) {
		for (auto st2 : el_if->GetSubcode()) {
			LabelPass(st2);
		}
	}

	//go through all the subcode in the else clause if there is one to check for labels
	if (if_st->GetElseClause() != nullptr) {
		IfStatement::ElseClause* el_cl = if_st->GetElseClause();
		for (auto st2 : el_cl->GetSubcode()) {
			LabelPass(st2);
		}
	}
}

void Interpreter::LabelPassWhileLoop(WhileLoop* st) {
	WhileLoop* wh_lp = (WhileLoop*)st;

	for (auto st : wh_lp->GetStatements()) {
		LabelPass(st);
	}
}

void Interpreter::LabelPassForLoop(ForLoop* st) {
	ForLoop* f_lp = (ForLoop*)st;

	for (auto st : f_lp->GetStatements()) {
		LabelPass(st);
	}
}

void Interpreter::LabelPassSubroutine(Subroutine* st) {
	Subroutine* sub = (Subroutine*)st;

	auto ptr = subroutines.find(sub->GetName());
	if (ptr != subroutines.end()) {
		//error - more than one subroutine with the same name
	}

	subroutines[sub->GetName()] = sub;

	for (auto st : sub->GetStatements()) {
		LabelPass(st);
	}
}

//goes through and sets the next pointer in each statement
void Interpreter::DirectionPass(std::vector<Statement*> stv, Statement* currentLoop) {

	for (int i = 0; i < stv.size(); i++) {

		if (stv[i]->GetStatementType() == "Expression Statement") {
			DirectionPassExpressionStatement(stv, i, currentLoop);
		}
		else if (stv[i]->GetStatementType() == "Label Statement") {
			DirectionPassLabelStatement(stv, i, currentLoop);
		}
		else if (stv[i]->GetStatementType() == "Goto Statement") {
			DirectionPassGotoStatement(stv, i, currentLoop);
		}
		else if (stv[i]->GetStatementType() == "If Statement") {
			DirectionPassIfStatement(stv, i, currentLoop);
		}
		else if (stv[i]->GetStatementType() == "While Loop") {
			DirectionPassWhileLoop(stv, i, currentLoop);
		}
		else if (stv[i]->GetStatementType() == "For Loop") {
			DirectionPassForLoop(stv, i, currentLoop);
		}
		else if (stv[i]->GetStatementType() == "Subroutine") {
			DirectionPassSubroutine(stv, i, currentLoop);
		}
		else if (stv[i]->GetStatementType() == "Break Statement") {
			DirectionPassBreakStatement(stv, i, currentLoop);
		}
		else if (stv[i]->GetStatementType() == "Continue Statement") {
			DirectionPassContinueStatement(stv, i, currentLoop);
		}
		else if (stv[i]->GetStatementType() == "Import Statement") {
			DirectionPassImportStatement(stv, i, currentLoop);
		}
	}
}

void Interpreter::DirectionPassExpressionStatement(std::vector<Statement*> stv, int i, Statement* current_loop) {
	if (stv[i]->GetNext() != nullptr) {
		//it has already been set so we don't need to change it
	}
	else if (i + 1 == stv.size()) {
		//there is no next statement
		stv[i]->SetNext(nullptr);
	}
	else {
		//set it to the statement after this
		stv[i]->SetNext(stv[i + 1]);
	}
}

void Interpreter::DirectionPassLabelStatement(std::vector<Statement*> stv, int i, Statement* current_loop) {
	if (stv[i]->GetNext() != nullptr) {
		//it has already been set so we don't need to change it
	}
	else if (i + 1 == stv.size()) {
		//there is no next statement
		stv[i]->SetNext(nullptr);
	}
	else {
		//set it to the statement after this
		stv[i]->SetNext(stv[i + 1]);
	}
}

void Interpreter::DirectionPassGotoStatement(std::vector<Statement*> stv, int i, Statement* current_loop) {
	GotoStatement* gtst = (GotoStatement*)stv[i];

	//get the label name
	std::string labelname = gtst->GetName();

	//check that the label actually exists
	auto ptr = labels.find(labelname);
	if (ptr == labels.end()) {
		runtime_error = true;
		error_message = "Program Error - Trying to goto a label that does not exist";
		return;
	}
	//else

	//set the next pointer as the location of the label
	gtst->SetNext(ptr->second);

}

void Interpreter::DirectionPassIfStatement(std::vector<Statement*> stv, int i, Statement* current_loop) {
	//where the program actually goes to is dependant on what happens as it is running
	//the next pointer in this case just points to the statement after the whole if/else if/else block

	Statement* next = nullptr;

	if (stv[i]->GetNext() != nullptr) {
		//it has already been set so we don't need to change it
		next = stv[i]->GetNext();
	}
	else if (i + 1 == stv.size()) {
		//there is no next statement
		stv[i]->SetNext(nullptr);
		next = nullptr;
	}
	else {
		//set it to the statement after this
		stv[i]->SetNext(stv[i + 1]);
		next = stv[i + 1];
	}

	IfStatement* if_st = (IfStatement*)stv[i];

	if(if_st->GetStatements().empty()) {
		if_st->AddStatement(new VoidStatement);
	}


	//set the end of the if statement clause code to the statement after the if statement
	if_st->GetStatements().back()->SetNext(next);

	//perform a direction pass through the if clause code
	DirectionPass(if_st->GetStatements(), current_loop);

	for (auto el_if : if_st->GetElseIfClauses()) {

		if (el_if->GetSubcode().empty()) {
			el_if->AddStatement(new VoidStatement);
		}

		//set the end of the else if statement clause code to the statement after the if statement
		el_if->GetSubcode().back()->SetNext(next);

		//perform a direction pass through each else if clause code
		DirectionPass(el_if->GetSubcode(), current_loop);
	}

	if (if_st->GetElseClause()) {
		
		if (if_st->GetElseClause()->GetSubcode().empty()) {
			if_st->GetElseClause()->AddStatement(new VoidStatement);
		}
		
		if_st->GetElseClause()->GetSubcode().back()->SetNext(next);

		//perform a direction pass through the else clause if there is one
		DirectionPass(if_st->GetElseClause()->GetSubcode(), current_loop);
	}

}

void Interpreter::DirectionPassWhileLoop(std::vector<Statement*> stv, int i, Statement* current_loop) {
	//where the program actually goes to is dependant on what happens as it is running
	//the next pointer in this case just points to the statement after the whole while loop block

	if (stv[i]->GetNext() != nullptr) {
		//it has already been set so we don't need to change it
	}
	else if (i + 1 == stv.size()) {
		//there is no next statement
		stv[i]->SetNext(nullptr);
	}
	else {
		//set it to the statement after this
		stv[i]->SetNext(stv[i + 1]);
	}

	WhileLoop* wh_lp = (WhileLoop*)stv[i];

	if (wh_lp->GetStatements().empty()) {
		wh_lp->AddStatement(new VoidStatement);
	}

	//loop the last statement back to the while loop so after each pass through the while loop code the condition is re-evaluated
	wh_lp->GetStatements().back()->SetNext(stv[i]);

	//perform a direction pass of the while loop subcode
	DirectionPass(wh_lp->GetStatements(), wh_lp);
}

void Interpreter::DirectionPassForLoop(std::vector<Statement*> stv, int i, Statement* current_loop) {
	if (stv[i]->GetNext() != nullptr) {
		//it has already been set so we don't need to change it
	}
	else if (i + 1 == stv.size()) {
		//there is no next statement
		stv[i]->SetNext(nullptr);
	}
	else {
		//set it to the statement after this
		stv[i]->SetNext(stv[i + 1]);
	}

	ForLoop* f_lp = (ForLoop*)stv[i];

	if (f_lp->GetStatements().empty()) {
		f_lp->AddStatement(new VoidStatement);
	}

	f_lp->GetStatements().back()->SetNext(f_lp);

	DirectionPass(f_lp->GetStatements(), f_lp);

	//if the step value does not exist set it to the default value of one
	if (f_lp->GetStep() == nullptr) {
		IntExpression* oneExpression = new IntExpression;
		oneExpression->Set_Integer(1);
		f_lp->SetStep(oneExpression);
	}
}

void Interpreter::DirectionPassSubroutine(std::vector<Statement*> stv, int i, Statement* current_loop) {
	if (stv[i]->GetNext() != nullptr) {
		//it has already been set so we don't need to change it
	}
	else if (i + 1 == stv.size()) {
		//there is no next statement
		stv[i]->SetNext(nullptr);
	}
	else {
		//set it to the statement after this
		stv[i]->SetNext(stv[i + 1]);
	}

	Subroutine* sub = (Subroutine*)stv[i];

	//add dummy end sub
	sub->AddStatement(new EndSub);

	DirectionPass(sub->GetStatements());
}

void Interpreter::DirectionPassEndSub(std::vector<Statement*> stv, int i, Statement* current_loop) {
	//nothing to do so this function is purely symbolic
}

void Interpreter::DirectionPassBreakStatement(std::vector<Statement*> stv, int i, Statement* current_loop) {
	if (current_loop == nullptr) {
		runtime_error = true;
		error_message += "Program error at line " + std::to_string(stv[i]->GetLineNumber()) + " in file " + stv[i]->GetStatementFileName() + "\n";
		error_message += "Break statement used outside of any loop";
		return;
	}
	BreakStatement* bs = (BreakStatement*)stv[i];

	if (current_loop->GetStatementType() == "While Loop") {
		WhileLoop* wh_lp = (WhileLoop*)current_loop;
		bs->SetNext(wh_lp->GetNext());
	}
	else if (current_loop->GetStatementType() == "For Loop") {
		ForLoop* f_lp = (ForLoop*)current_loop;
		bs->SetNext(f_lp->GetNext());
	}
	else {
		assert(false);//not possible
	}
}

void Interpreter::DirectionPassContinueStatement(std::vector<Statement*> stv, int i, Statement* current_loop) {
	if (current_loop == nullptr) {
		runtime_error = true;
		error_message += "Program error at line " + std::to_string(stv[i]->GetLineNumber()) + " in file " + stv[i]->GetStatementFileName() + "\n";
		error_message += "Break statement used outside of any loop";
		return;
	}
	ContinueStatement* cs = (ContinueStatement*)stv[i];
	cs->SetNext(current_loop);
}

void Interpreter::DirectionPassImportStatement(std::vector<Statement*> stv, int i, Statement* current_loop) {
	if (stv[i]->GetNext() != nullptr) {
		//it has already been set so we don't need to change it
	}
	else if (i + 1 == stv.size()) {
		//there is no next statement
		stv[i]->SetNext(nullptr);
	}
	else {
		//set it to the statement after this
		stv[i]->SetNext(stv[i + 1]);
	}
}
