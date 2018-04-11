#pragma once
#include "SystemMethods.h"
#include "Hierarchy.h"
//Base class for classes that handles card or part of cards.
class BasicReaderData
{
public:
	BasicReaderData(std::wstring imageFileName, cv::Mat imageData, SystemMethods* systemMethods, bool doDebugging);
	~BasicReaderData();

protected:

	//The height of the shrinked card image we work with to maximize performance.
	const int WORKING_CARD_HEIGHT;

	//The name of the file with the card the reader should handle.
	std::wstring imageFileName;
	//The image data of the image containing the card.
	cv::Mat originalImageData;
	//Telling if the program should do debugging such as exporting the images to files.
	bool doDebugging;
	//Pointer to object handling the system dependent methods.
	SystemMethods* systemMethods;
};