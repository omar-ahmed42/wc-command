#include "bignumber.h"

BigNumber::BigNumber(const std::string& num)
{
	num_ = num;
}

BigNumber BigNumber::operator+(const BigNumber& other) const {
	std::string result;
	int i = num_.length() - 1, j = other.num_.length() - 1, carry = 0;

	while (i >= 0 || j >= 0 || carry) {
		int digit1 = i >= 0 ? num_[i] - '0' : 0;
		int digit2 = j >= 0 ? other.num_[j] - '0' : 0;
		int sum = digit1 + digit2 + carry;
		carry = sum / 10;
		result = std::to_string(sum % 10) + result;
		i--;
		j--;
	}

	return BigNumber(result);
}

BigNumber BigNumber::operator-(const BigNumber& other) const {
	std::string result;
	int i = num_.length() - 1, j = other.num_.length() - 1, borrow = 0;

	while (i >= 0 || j >= 0 || borrow) {
		int digit1 = i >= 0 ? num_[i] - '0' : 0;
		int digit2 = j >= 0 ? other.num_[j] - '0' : 0;
		int diff = digit1 - digit2 - borrow;
		if (diff < 0) {
			diff += 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}
		result = std::to_string(diff) + result;
		i--;
		j--;
	}

	// Remove leading zeros  

	while (result.length() > 1 && result[0] == '0') {
		result.erase(0, 1);
	}

	return BigNumber(result);
}

bool BigNumber::operator==(const BigNumber& other) const {
	return num_ == other.num_;
}

bool BigNumber::operator<=(const BigNumber& other) const {
	if (num_.length() < other.num_.length()) {
		return true;
	}
	else if (num_.length() > other.num_.length()) {
		return false;
	}

	for (int i = 0; i < num_.length(); ++i) {
		if (num_[i] < other.num_[i]) {
			return true;
		}
		else if (num_[i] > other.num_[i]) {
			return false;
		}
	}

	return true; // If all digits are equal
}


std::ostream& operator<<(std::ostream& os, const BigNumber& num)
{
	return os << num.num_;
}
