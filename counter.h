#pragma once
#include <string>

class Counter {
	std::string value;
public:
	std::string getValue() { return this->value; };
	virtual std::string count(std::string text) = 0;
};

class ByteCounter : public Counter {
public:
	std::string count(std::string text) {
		
		return "";
	}
};

class CharacterCounter : public Counter {
	std::string count(std::string text) {
		return "";
	}
};

class NewlineCounter : public Counter {
	std::string count(std::string text) {
		return "";
	}
};

class MaxLineLengthCounter : public Counter {
	std::string count(std::string text) {
		return "";
	}
};

class WordCounter : public Counter {
	std::string count(std::string text) {
		return "";
	}
};