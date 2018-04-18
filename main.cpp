#include <iostream>
#include <string>

#include "math_definitions.h"
#include "polish_notation_converter.h"

int main(int argc, char** argv) {
	PolishNotationConverter converter;
	std::string input;
	std::cout << "Equation to differentiate: ";
	std::cin >> input;
	std::vector<Token> infix = converter.ParseString(input);
	std::vector<Token> prefix = converter.InfixToPrefix(infix);
	std::vector<Token> infix2 = converter.PrefixToInfix(prefix);
	std::string output = converter.OutputString(infix2);
	std::string outputTex = converter.OutputTex(infix2);

	std::cout << output << std::endl << std::endl;
	std::cout << outputTex << std::endl << std::endl;

	return 0;
}