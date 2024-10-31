#include "counter-factory.h"

Counter* CounterFactory::createCounter(parser::Option option)
{
	switch (option) {
	case parser::PRINT_BYTE_COUNT: return new ByteCounter;
	case parser::PRINT_CHARACTER_COUNT: return new CharacterCounter();
	case parser::PRINT_MAXLINE_LENGTH: return new MaxLineLengthCounter();
	case parser::PRINT_NEWLINE_COUNT: return new NewlineCounter();
	case parser::PRINT_WORD_COUNT: return new WordCounter();
	default: throw std::runtime_error("Unknown option");
	}
}
