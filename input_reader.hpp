#pragma once

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include "cpp_tstring.hpp"
#include "console.hpp"

struct BaseInputReader {
	bool inputExhausted = false;

	virtual unsigned long long int read() = 0;
	virtual std::vector<unsigned long long int> readRemainingInput();
};

struct FileInputReader : BaseInputReader {
	HANDLE hFile;

	FileInputReader(tstring file);

	virtual unsigned long long int read();
};

struct ConsoleInputReader : BaseInputReader {
	HANDLE stdOutput;

	ConsoleInputReader() : stdOutput(GetStdHandle(STD_OUTPUT_HANDLE)) {};

	virtual unsigned long long int read();
};

struct TestInputReader : BaseInputReader {
	unsigned long long int i = 1;
	virtual unsigned long long int read();
};