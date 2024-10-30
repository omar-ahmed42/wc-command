#pragma once
#include <vector>
#include <unordered_set>
#include <string>
#include "tokenizer.h"

namespace parser {
	enum Option: int {
		PRINT_CHARACTER_COUNT,
		PRINT_BYTE_COUNT,
		PRINT_NEWLINE_COUNT,
		PRINT_MAXLINE_LENGTH,
		PRINT_WORD_COUNT
	};

	class Parser {
		std::unordered_set<Option> options;
		std::vector<std::string> filenames;
	public:
		void parse(const std::vector<parser::Token> tokens);
		std::unordered_set<Option> getOptions();
		std::vector<std::string> getFilenames();

	private:
		bool isPrintCharacterCount(parser::Token token);
		bool isPrintByteCount(parser::Token token);
		bool isPrintNewlineCount(parser::Token token);
		bool isPrintMaxLineLength(parser::Token token);
		bool isPrintWordCount(parser::Token token);
		bool isOption(parser::Token token);
	};

}