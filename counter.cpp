#include "counter.h"
#include <cctype>

void Counter::finalize()
{
}

void Counter::reset()
{
	value = BigNumber("0");
}

BigNumber ByteCounter::count(std::string text)
{
	value = value + BigNumber(std::to_string(text.size()));
	return value;
}

void ByteCounter::finalize()
{
}

BigNumber CharacterCounter::count(std::string text)
{
	value = value + BigNumber(std::to_string(text.length()));
	return value;
}

void CharacterCounter::finalize()
{
}

BigNumber NewlineCounter::count(std::string text)
{
	for (auto& c : text) {
		if (c == '\n') value = value + BigNumber("1");
	}
	return value;
}

void NewlineCounter::finalize()
{
}

BigNumber MaxLineLengthCounter::count(std::string text)
{
	for (auto& c : text) {
		if (c != '\n') {
			value = value + BigNumber("1");
			currentLineLength = currentLineLength + BigNumber("1");
		}
		else {
			value = value <= currentLineLength ? currentLineLength : value;
			currentLineLength = BigNumber();
		}
	}
	return value;
}

BigNumber WordCounter::count(std::string text)
{
	BigNumber one = BigNumber("1");
	for (auto& c : text) {
		if (isspace(c)) {
			if (one <= currentWordLength) {
				value = value + one;
				currentWordLength = BigNumber();
			}
		}
		else {
			currentWordLength = currentWordLength + one;
		}
	}
	return value;
}

void WordCounter::finalize() {
	if (BigNumber("1") <= currentWordLength) {
		currentWordLength = BigNumber("0");
		value = value + BigNumber("1");
	}
}

void WordCounter::reset()
{
	Counter::reset();
	currentWordLength = BigNumber("0");
}

void MaxLineLengthCounter::finalize()
{
}

void MaxLineLengthCounter::reset()
{
	Counter::reset();
	currentLineLength = BigNumber("0");
}
