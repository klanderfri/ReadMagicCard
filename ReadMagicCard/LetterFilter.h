#pragma once
#include "LetterArea.h"
#include "TrendLine.h"
#include "BasicReaderData.h"
//Class for filtering out image parts that are noise.
class LetterFilter : 
	public BasicReaderData
{
public:
	LetterFilter(Session* session, std::wstring imageFilePath, cv::Mat originalImageData);
	~LetterFilter();

	//Runs the filter and returns the letters.
	LetterAreas RunFilter(Contours contours, int numberOfTries);
	//Gets the center line of the text.
	TrendLine GetTextCenterLine();
	//Gets the base line of the text.
	TrendLine GetTextBaseLine();

private:
	//Finds the center line for a set of letters.
	TrendLine findCenterLine(LetterAreas letters);
	//Finds the base line (the line marking the bottom) for a set of letters.
	TrendLine findBaseLine(LetterAreas letters);
	//Filter out letter areas that are identical, ie letter areas pointing at the same letter.
	LetterAreas filterOutDuplicates(LetterAreas lettersToFilter);
	//Removes the areas that are noise.
	LetterAreas filterOutNoise(LetterAreas lettersToFilter);
	//Filter out the holes inside the letters. Like the hole in 'o' and 'P'.
	LetterAreas filterOutLetterHoles(LetterAreas lettersToFilter);
	//Filter out the symbols not belonging to the title elements.
	LetterAreas filterOutNonTitleSymbols(LetterAreas lettersToFilter);
	//Removes the areas containing symbols not belonging to the card name.
	LetterAreas filterOutNonNameSymbols(LetterAreas lettersToFilter);
	//Removes the areas that belongs to the transform symbol.
	LetterAreas filterOutTransformSymbol(LetterAreas lettersToFilter);
	//Groups the letters by section separated by wide distances.
	std::vector<LetterAreas> groupLettersBySection(LetterAreas lettersToFilter);
	//Checks if to letter areas has a "wide" distance between its' centers, indicating that one is a title letter and the other a mana cost.
	bool hasWideLimitDistance(cv::RotatedRect leftLetterArea, cv::RotatedRect rightLetterArea);

	//The approximal line going through the center of the text.
	TrendLine textCenterLine;
	//The approximal line going through the base of the text.
	TrendLine textBaseLine;
};

