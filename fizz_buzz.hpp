#pragma once

#include <cstdint>
#include <unordered_map>

enum class FizzBuzzResult : uint8_t {
	UNKNOWN = 0, NONE = 1 << 0, FIZZ = 1 << 1, BUZZ = 1 << 2, FIZZBUZZ = FIZZ | BUZZ
};

struct _FizzBuzzer {
	std::unordered_map<unsigned long long int, FizzBuzzResult> cache;
	FizzBuzzResult fizzBuzz(const unsigned long long int number);
};

extern _FizzBuzzer fizzbuzzer;

FizzBuzzResult operator|(FizzBuzzResult lhs, FizzBuzzResult rhs);
FizzBuzzResult operator&(FizzBuzzResult lhs, FizzBuzzResult rhs);