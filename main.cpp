#include <iostream>
#include <string>

#include "math_definitions.h"
#include "polish_notation_converter.h"
#include "derivative.h"
#include "simplify.h"

bool debug = true;

int main(int argc, char** argv) {
	PolishNotationConverter converter;
	std::string input;
	std::cout << "Equation to differentiate: ";
	std::cin >> input;
	std::cout << std::endl;
	std::vector<Token> infix = converter.ParseString(input);
	if(debug) {
		std::cout << "Tokenized:" << std::endl;
		for(int i=0; i<int(infix.size()); ++i) {
			std::cout << infix[i] << std::endl;
		}
		std::cout << std::endl;
	}

	std::vector<Token> prefix = converter.InfixToPrefix(infix);
	if(debug) {
		std::cout << "Prefix:" << std::endl;
		for(int i=0; i<int(prefix.size()); ++i) {
			std::cout << prefix[i] << std::endl;
		}
		std::cout << std::endl;
	}

	std::vector<Token> derivative = differentiate(prefix);
	if(debug) {
		std::cout << "Derivative:" << std::endl;
		for(int i=0; i<int(derivative.size()); ++i) {
			std::cout << derivative[i] << std::endl;
		}
		std::cout << std::endl;
	}

	std::vector<Token> infix2 = converter.PrefixToInfix(derivative);
	if(debug) {
		std::cout << "Infix:" << std::endl;
		for(int i=0; i<int(infix2.size()); ++i) {
			std::cout << infix2[i] << std::endl;
		}
		std::cout << std::endl;
	}

	simplify(derivative);
	std::vector<Token> infix3 = converter.PrefixToInfix(derivative);
	if(debug) {
		std::cout << "Simplified infix:" << std::endl;
		for(int i=0; i<int(infix3.size()); ++i) {
			std::cout << infix3[i] << std::endl;
		}
		std::cout << std::endl;
	}

	std::string output = converter.OutputString(infix3);

	std::cout << "Result:" << std::endl;
	std::cout << output << std::endl << std::endl;

	return 0;
}