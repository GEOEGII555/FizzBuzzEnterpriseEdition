#include "fizz_buzz.hpp"

FizzBuzzResult _FizzBuzzer::fizzBuzz(const unsigned long long int number) {
	FizzBuzzResult cacheLookupResult = this->cache[number]; // Performance of an std::unordered_map lookup: O(1)
	if (cacheLookupResult != FizzBuzzResult::UNKNOWN) return cacheLookupResult;
	// Performance of an actual calculation:
	FizzBuzzResult calculatedResult = FizzBuzzResult::NONE;
	if (number % 15 == 0) { // O(1)
		calculatedResult = FizzBuzzResult::FIZZBUZZ;
	}
	else if (number % 5 == 0) { // O(1)
		calculatedResult = FizzBuzzResult::BUZZ;
	}
	else if (number % 3 == 0) { // O(1)
		calculatedResult = FizzBuzzResult::FIZZ;
	}
	this->cache[number] = calculatedResult;
	return calculatedResult;
}

_FizzBuzzer fizzbuzzer = {};