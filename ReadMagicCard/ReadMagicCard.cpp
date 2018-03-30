// ReadMagicCard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReadMagicCard.h"
#include "OcvCardReaderApplication.h"

int main(int argc, char** argv)
{
	//Enable debug if you want the program to output images and
	//text showing the different steps in the card identification.
	bool doDebugging = true;
	//Running the program parallelized will read the cards
	//quicker but makes it harder to debug.
	//Set to false when doing a release!
	bool runParallelized = true;

	OcvCardReaderApplication application;
	int result = application.Run(doDebugging, runParallelized);

	return result;
}
