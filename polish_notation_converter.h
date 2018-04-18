#ifndef POLISH_NOTATION_CONVERTER_H
#define POLISH_NOTATION_CONVERTER_H

#include <string>
#include <vector>

#include "math_definitions.h"

class PolishNotationConverter {
public:
	PolishNotationConverter() {} //Only constructor needed

	std::vector<Token> ParseString(std::string str) {
		std::vector<Token> infix;
		//
		return infix;
	}
	std::vector<Token> InfixToPrefix(std::vector<Token> infix) {
		std::vector<Token> prefix;
		//
		return prefix;
	}
	std::vector<Token> PrefixToInfix(std::vector<Token> prefix) {
		std::vector<Token> infix;
		//
		return infix;
	}
	std::string OutputString(std::vector<Token> infix) {
		std::string output;
		//
		return output;
	}
	std::string OutputTex(std::vector<Token> infix) {
		std::string output;
		//
		return output;
	}
};

#endif