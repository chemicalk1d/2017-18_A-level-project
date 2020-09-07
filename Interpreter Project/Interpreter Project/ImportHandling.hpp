#ifndef IMPORTHANDLING_HPP
#define IMPORTHANDLING_HPP

#include "AbstractSyntaxTree.hpp"

//function that handles the import statements in an abstract syntax tree
extern void HandleImports(AbstractSyntaxTree& ast, std::string dir);

#endif