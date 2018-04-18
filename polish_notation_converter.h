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

		bool lastCharOperator = true;

		while(int(str.length()) > 0) {
			//Clear out whitespace at the beginning of str
			while(int(str.length())>0 && str[0] == ' ') {
				str.erase(str.begin());
			}
			if(int(str.length()) == 0) {
				//Then there was trailing whitespace, and we're now done.
				break;
			}

			bool found = false;

			//Check if we're reading in a negative number/number
			bool isNegative = false;
			if(lastCharOperator && str[0] == '-') {
				assert(int(str.size()) >= 2); //Training minus sign?
				isNegative = isdigit(str[1]);
			}
			bool isNumber = isNegative || isdigit(str[0]);
			found = found || isNumber;

			//Check if it's a constant
			bool isConstant = false;
			if(!found) {
				for(int i=0; i<int(mathConstants.size()); ++i) {
					bool match = true;
					for(int j=0; j<int(mathConstants[i].size()); ++j) {
						if(mathConstants[i][j] != str[j]) {
							match = false;
							break;
						}
					}
					if(match) {
						isConstant = true;
						break;
					}
				}
			}
			found = found || isConstant;

			//Check if it's a parentheses
			bool isBracket = false;
			bool isLeftBracket = false;
			if(!found) {
				for(int i=0; i<int(mathBrackets.size()); ++i) {
					if(strBeginMatch(str, mathBrackets[i])) {
						isBracket = true;
						break;
					}
				}
				if(isBracket) {
					for(int i=0; i<int(mathLeftBrackets.size()); ++i) {
						if(strBeginMatch(str, mathLeftBrackets[i])) {
							isLeftBracket = true;
							break;
						}
					}
				}
			}
			found = found || isBracket;

			//Check if it's an operator
			bool isOperator = false;
			if(!found) {
				for(int i=0; i<int(mathOperators.size()); ++i) {
					if(strBeginMatch(str, mathOperators[i])) {
						isOperator = true;
						break;
					}
				}
			}
			found = found || isOperator;

			//Check if it's the parameter
			bool isVar = false;
			if(!found) {
				isVar = strBeginMatch(str, varName);
			}
			found = found || isVar;

			assert(found);

			//Now, we have the following booleans to help us determine what to do:
			//isNegative, isNumber, isConstant, isBracket, isVar, isOperator
			if(isNumber) {
				//
			}
			else if(isConstant) {
				//
			}
			else if(isBracket) {
				if(isLeftBracket) {
					//
				}
				else {
					//
				}
			}
			else if(isVar) {
				//
			}
			else if(isOperator) {
				//
			}
		}
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

private:
	bool strBeginMatch(std::string str, std::string token) {
		if(token.size() > str.size()) {
			return false;
		}
		bool match = true;
		for(int i=0; i<int(token.size()); ++i) {
			if(token[i] != str[i]) {
				match = false;
				break;
			}
		}
		return match;
	}
};

#endif