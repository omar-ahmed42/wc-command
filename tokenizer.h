#pragma once

#include <vector>
#include <string>

namespace parser {

enum TokenType {
	WHITESPACE,
	OPTION,
	STRING_LITERAL
};

struct Token {
	TokenType mType;
	std::string mText;
};

class Tokenizer {

public: 
	std::vector<Token> parse(const std::string& inProgram);

private:
	void endToken(Token& token, std::vector<Token>& tokens);
};

}