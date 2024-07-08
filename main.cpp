#include <Windows.h>
#include <tchar.h>
#include "console.hpp"
#include "argparser.hpp"

// Welcome to 2024, where open source projects have a copyright.
TCHAR copyrightMessage[] = {
	TEXT("FizzBuzz Enterprise Edition.\nEnterpriseQualityCoding - the most serious and not satire or fake company in the uinverse.\n")
};

ArgumentParser argParser;

int _tmain(unsigned int argc, TCHAR* argv[]) {
	argParser.parse(argc, argv);
	if (!argParser.noSplash) console.writeOutput(copyrightMessage);
	if (argParser.showHelp) {
		console.writeOutput(helpMessage);
		return -1;
	}
	return 0;
}