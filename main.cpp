#include <Windows.h>
#include <tchar.h>
#include "console.hpp"
#include "argparser.hpp"
#include "output_writer.hpp"
#include "input_reader.hpp"
#include "fizz_buzz_persistent_cache.hpp"

// Welcome to 2024, where open source projects have a copyright.
TCHAR copyrightMessage[] = {
	TEXT("FizzBuzz Enterprise Edition.\nEnterpriseQualityCoding - the most serious and not satire or fake company in the uinverse.\n")
};

ArgumentParser argParser;
BaseInputReader* inputReader;
BaseOutputWriter* outputWriter;
FizzBuzzCacheLoader* cacheLoader;

int _tmain(unsigned int argc, TCHAR* argv[]) {
	argParser.parse(argc, argv);
	if (!argParser.noSplash) console.writeOutput(copyrightMessage);
	if (argParser.showHelp) {
		console.writeOutput(helpMessage);
		return -1;
	}
	if (argParser.useTestInput) {
		inputReader = new TestInputReader();
	}
	else if (argParser.inputFile == TEXT("")) {
		inputReader = new ConsoleInputReader();
	}
	else {
		inputReader = new FileInputReader(argParser.inputFile);
	}
	if (argParser.outputFilename != TEXT("")) {
		outputWriter = new FileOutputWriter(argParser.outputFilename);
	}
	else {
		outputWriter = new ConsoleOutputWriter();
	}

	if (argParser.cacheFile != TEXT("")) {
		cacheLoader = new FizzBuzzCacheLoader(argParser.cacheFile);
		cacheLoader->loadCache(fizzbuzzer.cache);
	}

	while (!inputReader->getIsInputExhausted()) {
		try {
			unsigned long long int value = inputReader->read();
			outputWriter->writeOne(value, fizzbuzzer.fizzBuzz(value));
		}
		catch (std::exception e) { // Just in case something goes wrong (is the input stream empty?).
			continue;
		}
	}

	if (argParser.cacheFile != TEXT("")) {
		cacheLoader->dumpCache(fizzbuzzer.cache);
	}

	delete[] cacheLoader;
	delete[] outputWriter;
	delete[] inputReader;
	return 0;
}