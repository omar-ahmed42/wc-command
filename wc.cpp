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

		std::vector<Counter*> counters;
		if (!parsedOptions.empty()) {
			for (auto& option : parsedOptions) {
				Counter* counter(CounterFactory::createCounter(option));
				counters.push_back(counter);
			}
		}
		else {
			counters.push_back(CounterFactory::createCounter(parser::Option::PRINT_NEWLINE_COUNT));
			counters.push_back(CounterFactory::createCounter(parser::Option::PRINT_WORD_COUNT));
			counters.push_back(CounterFactory::createCounter(parser::Option::PRINT_BYTE_COUNT));
		}

		std::vector<std::string> parsedFilenames = parser.getFilenames();
		if (!parsedFilenames.empty()) {
			for (auto& filename : parsedFilenames) {
				std::ifstream file(filename, std::ios::binary);
				constexpr size_t bufferSize = static_cast<size_t>(1024) * 1024;
				std::unique_ptr<char[]> buffer(new char[bufferSize]);
				while (file) {
					file.read(buffer.get(), bufferSize);
					size_t gcount = file.gcount();
					std::string text(buffer.get(), gcount);
					for (auto& counter : counters) {
						counter->count(text);
					}
				}
				
				std::cout << "  ";
				for (auto& counter : counters) {
					counter->finalize();
					std::cout << counter->getValue() << " ";
					counter->reset();
				}

				std::cout << filename << std::endl;
				file.close();
			}
		}


	}
	else {
		std::cout << "No args have been passed" << std::endl;
	}

	return 0;
}