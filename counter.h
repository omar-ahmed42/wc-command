#pragma once
#include <string>
#include "bignumber.h"

class Counter {
protected:
	BigNumber value;
public:
	BigNumber getValue() { return this->value; };
	virtual BigNumber count(std::string text) = 0;
	virtual void finalize();
	virtual void reset();
};

class ByteCounter : public Counter {
public:
	BigNumber count(std::string text);
	void finalize();
};

class CharacterCounter : public Counter {
	BigNumber count(std::string text);
	void finalize();
};

class NewlineCounter : public Counter {
	BigNumber count(std::string text);
	void finalize();
};

class MaxLineLengthCounter : public Counter {
private:
	BigNumber currentLineLength;
public:
	BigNumber count(std::string text);
	void finalize();
	void reset();
};

class WordCounter : public Counter {
private:
	BigNumber currentWordLength;
public:
	BigNumber count(std::string text);
	void finalize();
	void reset();
};