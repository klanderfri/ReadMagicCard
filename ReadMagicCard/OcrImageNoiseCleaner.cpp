#include "stdafx.h"
#include "OcrImageNoiseCleaner.h"

using namespace cv;
using namespace std;

OcrImageNoiseCleaner::OcrImageNoiseCleaner(wstring imageFileName, Mat originalImageData, SystemMethods* systemMethods, bool runDebugging)
	: BasicReaderData(imageFileName, originalImageData, systemMethods, runDebugging)
{
}

OcrImageNoiseCleaner::~OcrImageNoiseCleaner()
{
}

void OcrImageNoiseCleaner::CleanImage(Mat& dirtyImage) {

	Mat originalImage;
	dirtyImage.copyTo(originalImage);

	threshold(dirtyImage, dirtyImage, 130, 255, THRESH_BINARY);
	Contours contours = ImageHelper::GetCannyContours(dirtyImage, 120);
	LetterAreas figures = ImageHelper::ToLetterAreas(contours);

	for (size_t i = 0; i < figures.size(); i++) {

		handleFigure(figures[i], dirtyImage);
	}
}

void OcrImageNoiseCleaner::handleFigure(LetterArea figure, Mat& dirtyImage) {

	if (figure.Box.size.area() == 0) { return; }

	Mat contourImage = ImageHelper::DrawLimits(dirtyImage, { figure.TightContour }, Hierarchy(), false);

	if (isNoise(figure, dirtyImage.size())) {

		Scalar white(255, 255, 255);
		ImageHelper::FillContour(dirtyImage, figure.OuterContour, white);
	}
}

bool OcrImageNoiseCleaner::isNoise(LetterArea figure, Size imageArea) {

	if (isOblong(figure)) { return true; }
	if (isSmallEnoughToBeNoise(figure) &&
		!isInCenter(figure, imageArea)) { return true; }

	return false;
}

bool OcrImageNoiseCleaner::isOblong(LetterArea figure) {

	double height = min(figure.Box.size.height, figure.Box.size.width);
	double width = max(figure.Box.size.height, figure.Box.size.width);
	double relation = width / height;

	return (relation > 5.5);
}

bool OcrImageNoiseCleaner::isSmallEnoughToBeNoise(LetterArea figure) {

	bool isOpen = !isContourConvex(figure.TightContour);
	double area = contourArea(isOpen ? figure.OuterContour : figure.TightContour);
	int maxNoiseArea = (int)(WORKING_CARD_HEIGHT / 8.5); //80

	return (area <= maxNoiseArea);
}

bool OcrImageNoiseCleaner::isInCenter(LetterArea figure, Size imageArea) {

	int borderMargin = (int)(WORKING_CARD_HEIGHT / 27.2); //25
	Rect rCenter(borderMargin, borderMargin, imageArea.width - 2 * borderMargin, imageArea.height - 2 * borderMargin);
	RotatedRect rrCenter = ImageHelper::ToRotatedRectangle(rCenter);
	bool placedInCenter = ImageHelper::DoesRectangleContainPoint(rrCenter, figure.Box.center);

	return placedInCenter;
}