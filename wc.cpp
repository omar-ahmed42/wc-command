// wc.cpp : Defines the entry point for the application.
//

#include "wc.h"

int main(int argc, const char* argv[]) {
	parser::Tokenizer tokenizer;
	if (argc > 1) {
		std::string inProgram;
		for (int i = 1; i < argc; i++) {
			inProgram.append(argv[i]);
			if (i + 1 < argc) inProgram.append(" ");
		}
		std::vector<parser::Token> tokens = tokenizer.parse(inProgram);
	}
	else {
		std::cout << "No args have been passed" << std::endl;
	}

	return 0;
}