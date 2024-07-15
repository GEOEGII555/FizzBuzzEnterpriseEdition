#include <Windows.h>
#include <tchar.h>
#include "cpp_tstring.hpp"
#include "argparser.hpp"

TCHAR helpMessage[] = TEXT("Usage: [program] [--output file] [--enable_cache cache_file] [--source source]\n\
\t--no-splash - Don't show the FizzBuzz Enterprise Edition splash message.\n\
\t--help - Display this help message, even if the input source is configured properly.\n\
\t--output [file] - Specify the file to write the result to. If this argument is omitted, the result is written into the standard output\n\
\t--enable_cache [cache_file] - Enable persistent caching.\n\
\t--input_source [source] - Specify where to read the numbers from. If you don't specify this argument, the help message will be displayed instead. [source] can be one of:\n\
\t\tstdinput - The program's standard input. It's recommended to disable the splash if you use this option when calling FizzBuzz Enterprise Edition from an another program.\n\
\t\tfile filename.txt - A file. If you set the source to file, you need to specify the filename right after the source argument.\n\
\t\ttestinput - A fake input source. It inputs all numbers from 1 to 100 (both sides included).\n");

// See the help message above for more info about these flags.
constexpr TCHAR HELP_FLAG[] = TEXT("--help");
constexpr TCHAR OUTPUT_FILENAME_FLAG[] = TEXT("--output");
constexpr TCHAR ENABLE_CACHE_FLAG[] = TEXT("--enable_cache");
constexpr TCHAR INPUT_SOURCE_FLAG[] = TEXT("--input_source");
constexpr TCHAR INPUT_SOURCE_STDINPUT[] = TEXT("stdinput");
constexpr TCHAR INPUT_SOURCE_FILE[] = TEXT("file");
constexpr TCHAR INPUT_SOURCE_TESTINPUT[] = TEXT("testinput");
constexpr TCHAR NO_SPLASH_FLAG[] = TEXT("--no-spplash");

void ArgumentParser::parse(const unsigned int argc, const TCHAR* const argv[]) {
	unsigned int i = 0;
	while (i < argc) {
		if (lstrcmp(argv[i], HELP_FLAG) == 0) showHelp = true;
		else if (lstrcmp(argv[i], OUTPUT_FILENAME_FLAG) == 0) {
			i++;
			if (i >= argc) {
				showHelp = true;
				break;
			}
			this->outputFilename = argv[i];
			if (this->outputFilename == TEXT("")) {
				showHelp = true;
				break;
			}
		}
		else if (lstrcmp(argv[i], ENABLE_CACHE_FLAG) == 0) {
			i++;
			if (i >= argc) {
				showHelp = true;
				break;
			}
			this->cacheFile = argv[i];
			if (this->cacheFile == TEXT("")) {
				showHelp = true;
				break;
			}
		}
		else if (lstrcmp(argv[i], INPUT_SOURCE_FLAG) == 0) {
			inputSourceSpecified = true;
			i++;
			if (i >= argc) {
				showHelp = true;
				break;
			}
			if (lstrcmp(argv[i], INPUT_SOURCE_STDINPUT) == 0) {
				this->inputFile = TEXT("");
			}
			else if (lstrcmp(argv[i], INPUT_SOURCE_FILE) == 0) {
				i++;
				if (i >= argc) {
					showHelp = true;
					break;
				}
				this->inputFile = argv[i];
				if (this->inputFile == TEXT("")) {
					showHelp = true;
					break;
				}
			}
			else if (lstrcmp(argv[i], INPUT_SOURCE_TESTINPUT) == 0) {
				this->useTestInput = true;
			}
			else {
				showHelp = true;
				break;
			}
		}
		else if (lstrcmp(argv[i], NO_SPLASH_FLAG) == 0) {
			this->noSplash = true;
		}
		i++;
	}
	if (!inputSourceSpecified) showHelp = true;
}