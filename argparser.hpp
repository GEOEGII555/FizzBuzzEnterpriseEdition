#include <Windows.h>
#include <tchar.h>
#include "cpp_tstring.hpp"

extern TCHAR helpMessage[];

class ArgumentParser {
	bool showHelp = false;
	tstring outputFilename = TEXT("");
	tstring cacheFile = TEXT("");
	tstring inputFile = TEXT("");
	bool inputSourceSpecified = false;
	bool noSplash = false;
	bool useTestInput = false;

public:
	void parse(const unsigned int argc, const TCHAR* const argv[]);
	bool shouldShowHelp();
	tstring getOutputFilename();
	tstring getCacheFile();
	tstring getInputFile();
	bool isInputSourceSpecified();
	bool shouldShowSplash();
	bool shouldUseTestInput();
	
	bool getBooleanFlag(tstring flag);
	tstring getStringArgument(tstring argument);
};
