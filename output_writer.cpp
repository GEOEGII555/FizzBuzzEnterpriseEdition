#include "output_writer.hpp"
#include "cpp_tstring.hpp"
#include "fizz_buzz.hpp"
#include <vector>
#include <algorithm>
#include "console.hpp"
#include <tchar.h>

void BaseOutputWriter::writeOne(unsigned long long int number, FizzBuzzResult result) {
	tstring str;
	if (number == 0) str = TEXT("0");
	else while (number != 0) {
		str.push_back((TCHAR)(number + TEXT('0')));
	}
	str.reserve();
	str.append(TEXT(":"));
	
	if ((result & FizzBuzzResult::FIZZ) != FizzBuzzResult::UNKNOWN) str.append(TEXT("Fizz"));
	if ((result & FizzBuzzResult::BUZZ) != FizzBuzzResult::UNKNOWN) str.append(TEXT("Buzz"));
	if ((result & FizzBuzzResult::NONE) != FizzBuzzResult::UNKNOWN) str.append(str.substr(0, str.length() - 1));
	str.push_back('\n');
	_write(str);
}

void BaseOutputWriter::writeMany(std::vector<std::pair<unsigned long long int, FizzBuzzResult>> values) {
	std::for_each(values.begin(), values.end(), [&](std::pair<unsigned long long int, FizzBuzzResult>& pair) {
		writeOne(pair.first, pair.second);
	});
}

void ConsoleOutputWriter::_write(tstring str) {
	console.writeOutput(str);
}

FileOutputWriter::FileOutputWriter(tstring file) {
	this->hFile = CreateFile(file.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() != NO_ERROR && GetLastError() != ERROR_ALREADY_EXISTS) {
		DWORD error = GetLastError();
		TCHAR* arr;
		if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, LANG_USER_DEFAULT, reinterpret_cast<LPTSTR>(&arr), 1, NULL)) abort();
		console.writeError(TEXT("Failed to open the output file for writing: "));
		console.writeError(arr);
		console.writeError(TEXT("\n"));
		abort();
	}
}

void FileOutputWriter::_write(tstring str) {
	DWORD dataWritten;
	WriteFile(this->hFile, str.c_str(), str.length(), &dataWritten, NULL);
	if (dataWritten != str.length()) abort();
}