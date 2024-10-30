// wc.cpp : Defines the entry point for the application.
//

#include "wc.h"
#include <fstream>

int main(int argc, const char* argv[]) {
	parser::Tokenizer tokenizer;
	if (argc > 1) {
		std::string inProgram;
		for (int i = 1; i < argc; i++) {
			inProgram.append(argv[i]);
			if (i + 1 < argc) inProgram.append(" ");
		}
		std::vector<parser::Token> tokens = tokenizer.parse(inProgram);
		parser::Parser parser;
		parser.parse(tokens);
		std::unordered_set<parser::Option> parsedOptions = parser.getOptions();

		std::vector<Counter> counters;
		if (!parsedOptions.empty()) {
			for (auto& option : parsedOptions) {
				Counter* counter = CounterFactory::createCounter(option);
				counters.push_back(*counter);
			}
		}

		std::vector<std::string> parsedFilenames = parser.getFilenames();
		if (!parsedFilenames.empty()) {
			for (auto& filename : parsedFilenames) {
				std::ifstream file(filename);
				constexpr size_t bufferSize = static_cast<size_t>(1024) * 1024;
				std::unique_ptr<char[]> buffer(new char[bufferSize]);
				while (file) {
					file.read(buffer.get(), bufferSize);
					std::string text(buffer.get());
					for (auto& counter : counters) {
						counter.count(text);
					}
				}
			}
		}

		for (auto& counter : counters) {
			std::cout << counter.getValue() << std::endl;
		}


	}
	else {
		std::cout << "No args have been passed" << std::endl;
	}

	return 0;
}