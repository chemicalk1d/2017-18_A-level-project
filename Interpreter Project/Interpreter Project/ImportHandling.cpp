
#include "ImportHandling.hpp"
#include "Statements.hpp"
#include "AbstractSyntaxTree.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Utils.hpp"

#include <map>
#include <iostream>
#include <string>

//TODO add handling for more complicated directorys
std::string CombineDirectory(std::string dir, std::string file) {
	return dir + file;
}

AbstractSyntaxTree Import(ImportStatement* is, std::string dir) {
	std::string filepath = CombineDirectory(dir, is->GetFilePath());
	
	std::string filecontents = ReadFile(filepath);

	Lexer l;
	l.Lex(filecontents, filepath);

	std::vector<Token> tokens = l.GetTokens();

	Parser p;
	p.Parse(tokens, filepath);

	if (p.Error_occured()) {
		std::cout << p.GetErrorMessage() << std::endl;
		system("pause");
		exit(0);
	}

	return p.Get_AST();
}

void AddImportedCode(AbstractSyntaxTree& ast, AbstractSyntaxTree subtree) {
	//for (auto st : subtree.GetStatements()) {
	//	ast.AddStatement(st->Duplicate());
	//}
		ast.CombineFront(subtree);
}

struct ImportInfo {
	ImportStatement* is;
	bool imported;
};

void HandleImports(AbstractSyntaxTree& ast, std::string dir) {

	//this map holds a group of all the imports, the boolean is there to say whether we have been added
	std::map<std::string, ImportInfo> imports;

	//add the starting file as an import so that you can't import it
	ImportInfo ii;
	ii.imported = true;
	ii.is = nullptr;
	imports[ast.GetStatements()[0]->GetStatementFileName()] = ii;

	while (true) {

		bool newImport = false;

		for (auto st : ast.GetStatements()) {

			if (st->GetStatementType() != "Import Statement") {
				continue;
			}
			//else

			ImportStatement* is = (ImportStatement*)st;

			auto ptr = imports.find(is->GetFilePath());
			if (ptr == imports.end()) {
				ImportInfo ii;
				ii.is = is;
				ii.imported = false;
				imports[is->GetFilePath()] = ii;
			}
		}

		//iterate through the map
		for (auto ptr = imports.begin(); ptr != imports.end(); ptr++) {
			ImportStatement* is = ptr->second.is;
			bool imported = ptr->second.imported;

			if (imported == true) {
				continue;
			}
			//else

			newImport = true;

			ptr->second.imported = true;

			AbstractSyntaxTree subtree = Import(is, dir);

			AddImportedCode(ast, subtree);

			//subtree.DeleteStatements();
		}

		//no new imports were made on this pass therefore we don't need to carry on
		if (newImport == false) {
			break;
		}

	}

}
