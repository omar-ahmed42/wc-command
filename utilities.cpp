#include <string>

namespace parser {
static bool isEscapable(char c) {
		switch (c) {
		case 'a':
		case 'b':
		case 'f':
		case 'n':
		case 'r':
		case '\t':
		case '\v':
		case '\\':
		case '\'':
		case '\"':
		case '\0':
		case '\ooo':
		case '\xdd':
			return true;
		}

		return false;
	}


static char createEscapedCharacter(char c) {
	// TODO: handle \U0001f34c , etc
	char escaped;
	switch (c) {
	case 'a': escaped = '\a'; break;
	case 'b': escaped = '\b'; break;
	case 'f': escaped = '\f'; break;
	case 'n': escaped = '\n'; break;
	case 'r': escaped = '\r'; break;
	case '\t': escaped = '\t'; break;
	case '\v': escaped = '\v'; break;
	case '\\': escaped = '\\'; break;
	case '\'': escaped = '\''; break;
	case '\"': escaped = '\"'; break;
	case '\0': escaped = '\0'; break;
	default: escaped = '\\'; break;
	}

	return escaped;
}

static void appendEscapedCharacter(char c, std::string& text) {
	if (isEscapable(c)) text.append(1, createEscapedCharacter(c));
	else text.append(1, '\\' + c);
}
}