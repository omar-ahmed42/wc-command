#pragma once
#include <string>
#include "parser.h"
#include "counter.h"

class CounterFactory {
public:
	static Counter* createCounter(parser::Option option);
};