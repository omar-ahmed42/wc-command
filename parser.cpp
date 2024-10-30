#include "parser.h"
#include <stdexcept>

void parser::Parser::parse(const std::vector<parser::Token> tokens)
{
	for (std::vector<parser::Token>::const_iterator currentToken = tokens.cbegin(); currentToken != tokens.cend(); currentToken++) {
		if (isOption(*currentToken)) {
			if (isPrintByteCount(*currentToken)) { options.insert(PRINT_BYTE_COUNT);}
			else if (isPrintCharacterCount(*currentToken)) { options.insert(PRINT_CHARACTER_COUNT); }
			else if (isPrintNewlineCount(*currentToken)) { options.insert(PRINT_NEWLINE_COUNT); }
			else if (isPrintMaxLineLength(*currentToken)) { options.insert(PRINT_MAXLINE_LENGTH); }
			else if (isPrintWordCount(*currentToken)) { options.insert(PRINT_WORD_COUNT); }
			//else if (currentToken->mText == "-help") {}
			else { throw std::runtime_error("wc: unknown option -- " + currentToken->mText + "\nTry \'wc --help\' for more information."); }
		}
		else if (currentToken->mType == STRING_LITERAL) { filenames.push_back(currentToken->mText); }
		else throw std::runtime_error("Undefined token for " + currentToken->mText);
	}
}

bool parser::Parser::isPrintCharacterCount(parser::Token token) {
	return token.mText == "m" || token.mText == "-chars";
}

bool parser::Parser::isPrintByteCount(parser::Token token) {
	return token.mText == "c" || token.mText == "-bytes";
}

bool parser::Parser::isPrintNewlineCount(parser::Token token) {
	return token.mText == "l" || token.mText == "-lines";
}

bool parser::Parser::isPrintMaxLineLength(parser::Token token) {
	return token.mText == "L" || token.mText == "-max-line-length";
}

bool parser::Parser::isPrintWordCount(parser::Token token) {
	return token.mText == "w" || token.mText == "words";
}

std::vector<std::string> parser::Parser::getFilenames()
{
	return parser::Parser::filenames;
}

std::unordered_set<parser::Option> parser::Parser::getOptions()
{
	return parser::Parser::options;
}

bool parser::Parser::isOption(parser::Token token) {
	return token.mType == OPTION;
}
