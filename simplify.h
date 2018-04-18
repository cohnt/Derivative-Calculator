#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include "derivative.h" //For getArguments

//Helpers
bool isNumeral(std::string str) {
	//
	return isdigit(str[0]) || (int(str.size() > 1 && isdigit(str[1])));
}

//Simplify rules:
bool timesOne(std::vector<Token> & function) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "*") {
			std::vector<Token> section(function.begin()+i, function.end());
			std::pair<std::vector<Token>, std::vector<Token>> args = getArguments(section);
			std::cout << "args.first[0]=" << args.first[0] << "\targs.second[0]=" << args.second[0] << std::endl;
			if(args.first[0] == "1") {
				function.erase(function.begin()+i, function.begin()+i+2);
				return true;
			}
			else if(args.second[0] == "1") {
				std::cout << "Times 1 in arg 2!" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					std::cout << function[i] << " ";
				}
				std::cout << std::endl;
				function.erase(function.begin()+i+1+int(args.first.size()));
				function.erase(function.begin()+i);
				std::cout << "Now it's" << std::endl;
				for(int i=0; i<int(function.size()); ++i) {
					std::cout << function[i] << " ";
				}
				std::cout << std::endl;
				return true;
			}
		}
	}
	return false;
}
bool evalAddSub(std::vector<Token> & function) {
	for(int i=0; i<int(function.size()); ++i) {
		if(function[i] == "+" || function[i] == "-") {
			if((isdigit(function[i+1][0]) || (int(function[i+1].size()) > 1 && isdigit(function[i+1][1])))
			 && (isdigit(function[i+2][0]) || (int(function[i+2].size()) > 1 && isdigit(function[i+2][1])))) {
				if(function[i] == "+") {
					function[i] = std::to_string(stod(function[i+1])+stod(function[i+2]));
				}
				else {
					function[i] = std::to_string(stod(function[i+1])-stod(function[i+2]));
				}
				function.erase(function.begin()+i+1, function.begin()+i+3);
				return true;
			}
		}
	}
	return false;
}
bool trimTrailingZeros(std::vector<Token> & function) {
	for(int i=0; i<int(function.size()); ++i) {
		if(isNumeral(function[i])) {
			if(function[i].find('.') != std::string::npos) {
				if(function[i].back() == '0') {
					while(function[i].back() == '0') {
						function[i].pop_back();
					}
					if(function[i].back() == '.') {
						function[i].pop_back(); //If it ends with an unnecessary decimal point, clear that out too
					}
					return true;
				}
			}
		}
	}
	return false;
}

std::vector<bool(*)(std::vector<Token>&)> simplifyFunctions = {
	timesOne,
	evalAddSub,
	trimTrailingZeros
};

//Call this to actually do the thing
void simplify(std::vector<Token> & function) {
	bool madeAChange = true;
	while(madeAChange) {
		madeAChange = false;
		for(int i=0; i<int(simplifyFunctions.size()); ++i) {
			if(simplifyFunctions[i](function)) {
				madeAChange = true;
				break;
			}
		}
	}
}

#endif