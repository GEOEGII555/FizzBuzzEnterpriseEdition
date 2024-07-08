#include "fizz_buzz_persistent_cache.hpp"
#include <Windows.h>
#include <unordered_map>
#include "fizz_buzz.hpp"
#include "cpp_tstring.hpp"
#include "console.hpp"
#include <algorithm>
#include <cstdint>

FizzBuzzCacheLoader::FizzBuzzCacheLoader(tstring file) {
	this->hFile = CreateFile(file.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() != NO_ERROR && GetLastError()) {
		DWORD error = GetLastError();
		TCHAR* arr;
		if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, LANG_USER_DEFAULT, reinterpret_cast<LPTSTR>(&arr), 1, NULL)) abort();
		console.writeError(TEXT("Failed to open the persistent cache file for reading and writing: "));
		console.writeError(arr);
		console.writeError(TEXT("\n"));
		abort();
	}
}

void FizzBuzzCacheLoader::loadCache(std::unordered_map<unsigned long long int, FizzBuzzResult>& cache) {
	cache.clear();
	unsigned long long int size;
	GetFileSizeEx(this->hFile, (PLARGE_INTEGER)&size);
	if (size > ((size_t)-1)) abort(); // (not possible under normal circumstances)
	TCHAR* fileData = new TCHAR[size];
	ZeroMemory(fileData, size * sizeof(TCHAR));
	SetFilePointer(this->hFile, NULL, NULL, FILE_BEGIN);
	DWORD actualDataSize = 0;
	if (!ReadFile(this->hFile, fileData, size, &actualDataSize, NULL)) abort();
	tistream str(tstring(fileData));
	tstring line;
	while (std::getline<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>(str, line), TEXT('\n')) {
		if (line[line.size() - 1] == TEXT('\r')) line.pop_back();
		if (line.length() == 0) continue;
		size_t separator = line.find_first_of(':');
		if (separator == tstring::npos) continue;
		tstring numberStr, resultStr;
		unsigned long long int number = 0;
		uint8_t numberResult = 0;
		FizzBuzzResult result = FizzBuzzResult::UNKNOWN;
		numberStr = line.substr(0, separator);
		resultStr = line.substr(separator + 1);
		std::reverse(numberStr.begin(), numberStr.end());
		while (numberStr != TEXT("")) {
			number *= 10;
			if (numberStr[numberStr.size() - 1] < '0' || numberStr[numberStr.size() - 1] > '9') abort();
			number += numberStr[numberStr.size() - 1] - TEXT('0');
			numberStr.pop_back();
		}
		std::reverse(resultStr.begin(), resultStr.end());
		while (resultStr != TEXT("")) {
			numberResult *= 10;
			if (resultStr[resultStr.size() - 1] < '0' || resultStr[resultStr.size() - 1] > '9') abort();
			numberResult += resultStr[resultStr.size() - 1] - TEXT('0');
			resultStr.pop_back();
		}
		result = static_cast<FizzBuzzResult>(numberResult);
		cache[number] = result;
	}
}

void FizzBuzzCacheLoader::dumpCache(std::unordered_map<unsigned long long int, FizzBuzzResult>& cache)  {
	SetFilePointer(this->hFile, NULL, NULL, FILE_BEGIN);
	SetEndOfFile(this->hFile);
	std::for_each(cache.begin(), cache.end(), [&](std::pair<unsigned long long int, FizzBuzzResult>& data) {
		tstring line;
		tstring temp;

		while (data.first != 0) {
			line.push_back((TCHAR)(data.first + TEXT('0')));
		}
		std::reverse(line.begin(), line.end());
		line.push_back(TEXT(':'));

		uint8_t value = static_cast<uint8_t>(data.second);
		while (value != 0) {
			temp.push_back((TCHAR)(value + TEXT('0')));
		}
		line.append(temp);
		DWORD realDataWritten = 0;
		WriteFile(this->hFile, line.c_str(), line.size() * sizeof(TCHAR), &realDataWritten, NULL);
		if (realDataWritten != line.size() * sizeof(TCHAR)) abort();
		SetFilePointer(this->hFile, NULL, NULL, FILE_END);
		});
}

FizzBuzzCacheLoader::~FizzBuzzCacheLoader() {
	CloseHandle(this->hFile);
}