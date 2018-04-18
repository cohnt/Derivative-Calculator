#include <iostream>
#include <string>

#include "math_definitions.h"
#include "polish_notation_converter.h"

bool debug = true;

int main(int argc, char** argv) {
	PolishNotationConverter converter;
	std::string input;
	std::cout << "Equation to differentiate: ";
	std::cin >> input;
	std::vector<Token> infix = converter.ParseString(input);
	if(debug) {
		for(int i=0; i<int(infix.size()); ++i) {
			std::cout << infix[i] << std::endl;
		}
		std::cout << std::endl;
	}

	std::vector<Token> prefix = converter.InfixToPrefix(infix);

	std::vector<Token> infix2 = converter.PrefixToInfix(prefix);

	std::string output = converter.OutputString(infix2);

	std::string outputTex = converter.OutputTex(infix2);

	if(debug) {
		std::cout << output << std::endl << std::endl;
		std::cout << outputTex << std::endl << std::endl;
	}

	return 0;
}