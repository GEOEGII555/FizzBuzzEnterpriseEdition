#include <Windows.h>
#include <tchar.h>
#include "cpp_tstring.hpp"

extern TCHAR helpMessage[];

struct ArgumentParser {
	bool showHelp = false;
	tstring outputFilename = TEXT("");
	tstring cacheFile = TEXT("");
	tstring inputFile = TEXT("");
	bool inputSourceSpecified = false;
	bool noSplash = false;

	void parse(const unsigned int argc, const TCHAR* const argv[]);
};
