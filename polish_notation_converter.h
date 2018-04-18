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

		bool lastCharNumber = false; //Used to determine whether - means subtraction or negative

		while(int(str.length()) > 0) {
			//Clear out whitespace at the beginning of str, stop if the string is now empty
			if(clearLeadingWhitespace(str)) {
				break;
			}

			bool found = false;

			//Check if we're reading in a negative number/number
			bool isNegative = !lastCharNumber && checkIfNegative(str);
			bool isNumber = isNegative || isdigit(str[0]);
			found = found || isNumber;

			//Check if it's a constant
			bool isConstant = false;
			std::string whichConstant = "";
			if(!found) {
				isConstant = checkIfConstant(str, whichConstant);
			}
			found = found || isConstant;

			//Check if it's a parentheses
			bool isBracket = false;
			bool isLeftBracket = false;
			std::string whichBracket = "";
			if(!found) {
				isBracket = checkIfBracket(str, whichBracket, isLeftBracket);
			}
			found = found || isBracket;

			//Check if it's an operator
			bool isOperator = false;
			std::string whichOperator = "";
			if(!found) {
				isOperator = checkIfOperator(str, whichOperator);
			}
			found = found || isOperator;

			//Check if it's the parameter
			bool isVar = false;
			if(!found) {
				isVar = checkIfVariable(str);
			}
			found = found || isVar;

			assert(found); //Better find it!

			lastCharNumber = isNumber;

			//Now, we have the following booleans to help us determine what to do:
			//isNegative, isNumber, isConstant, isBracket, isVar, isOperator
			if(isNumber) {
				std::string number = "";
				if(isNegative) {
					number += "-";
					str.erase(str.begin());
				}
				while(str.length() > 0 && isdigit(str[0])) {
					number += str[0];
					str.erase(str.begin());
				}
				infix.push_back(number);
			}
			else if(isConstant) {
				str.erase(str.begin(), str.begin()+int(whichConstant.size()));
				infix.push_back(whichConstant);
			}
			else if(isBracket) {
				str.erase(str.begin(), str.begin()+int(whichBracket.size()));
				if(isLeftBracket) {
					infix.push_back("(");
				}
				else {
					infix.push_back(")");
				}
			}
			else if(isVar) {
				str.erase(str.begin());
				infix.push_back(varName);
			}
			else if(isOperator) {
				str.erase(str.begin(), str.begin()+int(whichOperator.size()));
				infix.push_back(whichOperator);
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
	//Checks if the string token is contained starting from the first
	//character of str
	bool strBeginMatch(const std::string & str, const std::string & token) {
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
	//Clears any leading whitespace in str, and returns whether or not
	//str is now empty
	bool clearLeadingWhitespace(std::string &str) {
		while(int(str.length())>0 && str[0] == ' ') {
			str.erase(str.begin());
		}
		return int(str.length()) == 0;
	}
	//Check if str starts with a negative number
	bool checkIfNegative(const std::string &str) {
		if(str[0] == '-') {
			assert(int(str.size()) >= 2); //Training minus sign?
			return isdigit(str[1]);
		}
		else {
			return false;
		}
	}
	//Check if str starts with a constant name, and if so, stores that constant
	//into whichConstant
	bool checkIfConstant(const std::string &str, std::string &whichConstant) {
		bool isConstant = false;
		for(int i=0; i<int(mathConstants.size()); ++i) {
			if(strBeginMatch(str, mathConstants[i])) {
				isConstant = true;
				whichConstant = mathConstants[i];
				break;
			}
		}
		return isConstant;
	}
	//Check if str starts with a bracket, and if so, stores that bracket
	//into whichBracket
	bool checkIfBracket(const std::string &str, std::string &whichBracket, bool &isLeftBracket) {
		bool isBracket = false;
		for(int i=0; i<int(mathBrackets.size()); ++i) {
			if(strBeginMatch(str, mathBrackets[i])) {
				isBracket = true;
				whichBracket = mathBrackets[i];
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
		return isBracket;
	}
	//Check if str starts with an operator, and if so, stores that operator
	//into whichOperator
	bool checkIfOperator(const std::string &str, std::string &whichOperator) {
		bool isOperator = false;
		for(int i=0; i<int(mathOperators.size()); ++i) {
			if(strBeginMatch(str, mathOperators[i])) {
				isOperator = true;
				whichOperator = mathOperators[i];
				break;
			}
		}
		return isOperator;
	}
	//Check if str starts with the variable
	bool checkIfVariable(const std::string &str) {
		//Only doing this to keep it uniform
		return strBeginMatch(str, varName);
	}
};

#endif