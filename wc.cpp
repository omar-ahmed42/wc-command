// wc.cpp : Defines the entry point for the application.
//

#include "wc.h"
#include <fstream>
#include <filesystem>
#include <io.h>

int main(int argc, const char* argv[]) {
	parser::Tokenizer tokenizer;
	std::string inProgram;
	for (int i = 1; i < argc; i++) {
		inProgram.append(argv[i]);
		if (i + 1 < argc) inProgram.append(" ");
	}
	std::vector<parser::Token> tokens = tokenizer.parse(inProgram);
	parser::Parser parser;
	try {
		parser.parse(tokens);
	}
	catch (std::runtime_error e) {
		std::cerr << e.what();
		return 0;
	}
	std::unordered_set<parser::Option> parsedOptions = parser.getOptions();

	std::vector<Counter*> counters;
	if (parsedOptions.contains(parser::Option::HELP)) {
		std::cout << "Usage: wc [OPTION]... [FILE]...\n  or:  wc [OPTION]... --files0-from=F\nPrint newline, word, and byte counts for each FILE, and a total line if\nmore than one FILE is specified.  A word is a non-zero-length sequence of\ncharacters delimited by white space.\n\nWith no FILE, or when FILE is -, read standard input.\n\nThe options below may be used to select which counts are printed, always in\nthe following order: newline, word, character, byte, maximum line length.\n  -c, --bytes            print the byte counts\n  -m, --chars            print the character counts\n  -l, --lines            print the newline counts\n      --files0-from=F    read input from the files specified by\n                           NUL-terminated names in file F;\n                           If F is - then read names from standard input\n  -L, --max-line-length  print the maximum display width\n  -w, --words            print the word counts\n      --help     display this help and exit\n      --version  output version information and exit\n\nGNU coreutils online help: <https://www.gnu.org/software/coreutils/>\nFull documentation <https://www.gnu.org/software/coreutils/wc>\nor available locally via: info '(coreutils) wc invocation'";
		return 0;
	}
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

	int __cdecl inFileno = fileno(stdin);
	bool isInputRedirected = !_isatty(inFileno) || !isatty(inFileno);
	if (isInputRedirected) {
		constexpr size_t bufferSize = static_cast<size_t>(1024) * 1024;
		std::unique_ptr<char[]> buffer(new char[bufferSize]);

		std::istream* redirectedStream;
		while ((redirectedStream = &std::cin.read(buffer.get(), static_cast<std::streamsize>(1024) * 1024)) && redirectedStream->gcount() > 0) {
			size_t gcount = redirectedStream->gcount();

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

		return 1;
	}

	std::vector<std::string> parsedFilenames = parser.getFilenames();
	if (!parsedFilenames.empty()) {
		for (auto& filename : parsedFilenames) {
			// TODO: Calculate cummulative values
			if (!std::filesystem::exists(filename)) {
				std::cerr << "wc: " << filename << " No such file or directory" << std::endl;
				continue;
			}
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

			file.close();
			std::cout << "  ";
			for (auto& counter : counters) {
				counter->finalize();
				std::cout << counter->getValue() << " ";
				counter->reset();
			}

			std::cout << filename << std::endl;
		}
	}

	return 0;
}