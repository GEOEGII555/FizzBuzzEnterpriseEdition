#include <Windows.h>
#include <tchar.h>
#include "console.hpp"

TCHAR copyrightMessage[] = {
	TEXT("FizzBuzz Enterprise Edition. Copyright 2024 EnterpriseQualityCoding - the most serious and not satire or fake company in the uinverse.")
};

int _tmain(unsigned int argc, TCHAR* argv[]) {
	console.writeOutput(copyrightMessage);
}