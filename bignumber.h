#pragma once

#include <iostream>
#include <string>

class BigNumber {
public:
	BigNumber(const std::string& num = "0");

	BigNumber operator+(const BigNumber& other) const;
	BigNumber operator-(const BigNumber& other) const;
	bool operator==(const BigNumber& other) const;
	bool operator<=(const BigNumber& other) const;
	friend std::ostream& operator<<(std::ostream& os, const BigNumber& num);
private:
	std::string num_;
};