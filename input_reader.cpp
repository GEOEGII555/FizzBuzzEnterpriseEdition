#pragma once

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include "cpp_tstring.hpp"
#include "console.hpp"
#include "input_reader.hpp"

std::vector<unsigned long long int> BaseInputReader::readRemainingInput() {
	std::vector<unsigned long long int> results;
	while (!this->inputExhausted) results.push_back(read());
	return results;
}

FileInputReader::FileInputReader(tstring file) {
	this->hFile = CreateFile(file.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() != NO_ERROR) {
		DWORD error = GetLastError();
		TCHAR* arr;
		if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, LANG_USER_DEFAULT, reinterpret_cast<LPTSTR>(&arr), 1, NULL)) abort();
		console.writeError(TEXT("Failed to open the input file for reading: "));
		console.writeError(arr);
		console.writeError(TEXT("\n"));
		abort();
	}
	DWORD fileSize;
	GetFileSize(this->hFile, &fileSize);
	if (fileSize == 0) inputExhausted = true;
}

unsigned long long int FileInputReader::read() {
	if (inputExhausted) throw std::exception("There's nothing more in the input.");
	TCHAR currChar = '\0';
	DWORD temp = 0;
	unsigned long long int result = 0;
	do {
		if (!ReadFile(this->hFile, &currChar, 1, &temp, NULL)) {
			if (GetLastError() != ERROR_HANDLE_EOF) abort();
			temp = 0;
		}
		if (temp == 0) {
			inputExhausted = true;
			break;
		}
		result *= 10;
		result += currChar - TEXT('0');
	} while (currChar >= TEXT('0') && currChar <= TEXT('9'));
	return result;
}

unsigned long long int ConsoleInputReader::read() {
	if (inputExhausted) throw std::exception("There's nothing more in the input.");
	TCHAR currChar = '\0';
	DWORD temp = 0;
	unsigned long long int result = 0;
	do {
		if (!ReadConsole(this->stdOutput, &currChar, 1, &temp, NULL)) {
			if (GetLastError() != ERROR_HANDLE_EOF) abort();
			temp = 0;
		}
		if (temp == 0) {
			inputExhausted = true;
			break;
		}
		result *= 10;
		result += currChar - TEXT('0');
	} while (currChar >= TEXT('0') && currChar <= TEXT('9'));
	return result;
}

unsigned long long int TestInputReader::read() {
	if (inputExhausted) throw std::exception("There's nothing more in the input.");
	if (i == 100) inputExhausted = true;
	return i++;
}