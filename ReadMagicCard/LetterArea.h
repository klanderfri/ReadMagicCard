#pragma once
#include "Contour.h"
//Class holding information about the area of a letter.
class LetterArea
{
public:
	typedef std::vector<LetterArea> LetterAreas;

	LetterArea();
	~LetterArea();

	//Compares two letter areas by the X-coordinate of the left border when the letters are standing stright up.
	static bool CompareLetterAreaByBorderXAscending(LetterArea area1, LetterArea area2);
	//Checks if a letter is a child to any other letter.
	static bool HasParentLetter(LetterArea letterToCheck, LetterAreas possibleParents);

	//The contour of the letter.
	Contour contour;
	//The box containing the letter.
	cv::RotatedRect box;

private:

	//Checks if one letter is child to another letter.
	static bool hasChildParentRelation(LetterArea child, LetterArea parent);
};
typedef LetterArea::LetterAreas LetterAreas;
