// ReadMagicCard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReadMagicCard.h"
#include "OcvCardReaderApplication.h"
#include "boost\algorithm\string.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	//Enable debug if you want the program to output images and
	//text showing the different steps in the card identification.
	bool doDebugging = getInputArgumentValue(argv, argc, 1, false);
	//Running the program parallelized will read the cards
	//quicker but makes it harder to debug.
	bool runParallelized = getInputArgumentValue(argv, argc, 2, true);

	OcvCardReaderApplication application;
	int result = application.Run(doDebugging, runParallelized);

	return result;
}

bool getInputArgumentValue(char* arguments[], int numberOfArguments, int index, bool defaultValue) {

	if (index >= numberOfArguments) { return defaultValue; }

	char* argumentPtr = arguments[index];
	string argumentStr = string(argumentPtr);
	boost::algorithm::to_lower(argumentStr);

	if (argumentStr == "true") { return true; }
	if (argumentStr == "false") { return false; }
	if (argumentStr == "1") { return true; }
	if (argumentStr == "0") { return false; }

	throw new OcvParameterException("The first two command arguments must be booleans!", "argv[]");
}
