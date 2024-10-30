#include "tokenizer.h"
#include "utilities.cpp"
#include <iostream>
#include <stack>
#include <list>

std::vector<parser::Token> parser::Tokenizer::parse(const std::string& inProgram) {
	std::vector<Token> tokens;
	parser::Token currentToken{WHITESPACE};
	std::stack<char> quotes;

	for (int i = 0; i < inProgram.length(); i++) {
		char currentCh = inProgram[i];
		switch (currentCh) {
		case ' ':
		case '\t':
		case '\n':
			if (currentToken.mType == STRING_LITERAL && quotes.empty()) {
				endToken(currentToken, tokens);
			}
			else if (currentToken.mType == STRING_LITERAL && !quotes.empty()) {
				currentToken.mText.append(1, currentCh);
			}
			else if (currentToken.mType != WHITESPACE) {
				endToken(currentToken, tokens);
			}
			break;
		case '-':
			if (currentToken.mType == WHITESPACE) {
				currentToken.mType = OPTION;
			}
			else if (currentToken.mType == OPTION) {
				currentToken.mType = OPTION;
				currentToken.mText.append(1, currentCh);
			}
			else if (currentToken.mType == STRING_LITERAL) currentToken.mText.append(1, currentCh);
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			if (currentToken.mType == OPTION || currentToken.mType == STRING_LITERAL) {
				currentToken.mText.append(1, currentCh);
			}
			else if (currentToken.mType == WHITESPACE) {
				currentToken.mType = STRING_LITERAL;
				currentToken.mText.append(1, currentCh);
			}

			break;
		case '\\':
			if (!quotes.empty() && currentToken.mType == STRING_LITERAL && quotes.top() == '\'') {
				currentToken.mText.append(1, currentCh);
			}
			else if (quotes.empty() && (currentToken.mType == WHITESPACE || currentToken.mType == STRING_LITERAL)) {
				currentToken.mType = STRING_LITERAL;
				int lookahead = i + 1;
				if (lookahead < inProgram.length()) { parser::appendEscapedCharacter(inProgram[lookahead], currentToken.mText); i = lookahead; }
			}
			else if (!quotes.empty() && currentToken.mType == STRING_LITERAL && quotes.top() != '\'') {
				int lookahead = i + 1;
				if (lookahead < inProgram.length()) { parser::appendEscapedCharacter(inProgram[lookahead], currentToken.mText); i = lookahead; }
			}
			break;
		case '\"':
		case '\'':
			if (currentToken.mType == WHITESPACE) {
				currentToken.mType = STRING_LITERAL;
				currentToken.mText.append(1, currentCh);
				quotes.push(currentCh);
			}
			else if (currentToken.mType == STRING_LITERAL) {
				if (quotes.empty()) quotes.push(currentCh);
				else if (quotes.top() == currentCh) quotes.pop();
				else currentToken.mText.append(1, currentCh);
			}
			break;

			default:
				if (currentToken.mType == WHITESPACE || currentToken.mType == STRING_LITERAL) { 
					currentToken.mType = STRING_LITERAL;
					currentToken.mText.append(1, currentCh); 
				}
		}
	}

		endToken(currentToken, tokens);
		return tokens;

}

void parser::Tokenizer::endToken(Token& token, std::vector<Token>& tokens)
{
	if (token.mType != WHITESPACE) tokens.push_back(token);

	token.mType = WHITESPACE;
	token.mText.erase();
}