#include "stdafx.h"
#include "ContourHelper.h"
#include <opencv2\imgproc.hpp>

using namespace cv;
using namespace std;

ContourHelper::ContourHelper()
{
	this->drawingMethods = new DrawingHelper();
	this->imageEditor = new ImageEditHelper();
}

ContourHelper::~ContourHelper()
{
	delete drawingMethods;
	delete imageEditor;
}

Mat ContourHelper::GetContourAreaFromImage(const Contour contour, const Mat rawImage, const int margins, const bool drawContour) {

	//This method crashes when the cut area goes outside the image.
	//But that probably won't happen often so we'll cross that bridge when we get to it.

	Mat outImage;
	rawImage.copyTo(outImage);

	if (drawContour) {
		Contours contours{ contour };
		outImage = drawingMethods->DrawLimits(outImage, contours, Hierarchy(), false);
	}

	Rect bounds = boundingRect(Mat(contour));
	Rect cutArea(bounds.x - margins, bounds.y - margins, bounds.width + margins * 2, bounds.height + margins * 2);
	imageEditor->CropImage(outImage, outImage, cutArea);

	return outImage;
}

Contours ContourHelper::GetCannyContours(const Mat greyScaleImage, int thresh) {

	Contours contours;
	Hierarchy hierarchy;
	Mat canny;

	Canny(greyScaleImage, canny, thresh, thresh * 2, 3);
	findContours(canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	return contours;
}

Contour ContourHelper::GetConvexHullContours(const Contours contours)
{
	//Implemented as suggested at:
	//http://answers.opencv.org/question/74777/how-to-use-approxpolydp-to-close-contours/

	Contour result;
	Contour pts;

	for (size_t i = 0; i < contours.size(); i++) {

		for (size_t j = 0; j < contours[i].size(); j++) {

			pts.push_back(contours[i][j]);
		}
	}

	convexHull(pts, result);

	return result;
}

Contour ContourHelper::GetCombinedLetterContorus(LetterAreas letters) {

	Contour combinedLetterContorus;

	for (size_t i = 0; i < letters.size(); i++) {

		LetterArea area = letters[i];

		combinedLetterContorus.insert(combinedLetterContorus.end(), area.OuterContour.begin(), area.OuterContour.end());
	}

	return combinedLetterContorus;
}

Mat ContourHelper::GetContourDrawing(const Contour contour) {

	Rect2i bounds = boundingRect(contour);
	int margins = (int)ceil(min(bounds.width, bounds.height) * 0.1);

	Mat contourImage;
	contourImage.create(bounds.y + bounds.height + 1, bounds.x + bounds.width + 1, 0);
	contourImage = drawingMethods->DrawLimits(contourImage, Contours{ contour }, Hierarchy(), false);

	imageEditor->CropImage(contourImage, contourImage, bounds);

	return contourImage;
}

bool ContourHelper::IsIdenticalContours(Contour contour1, Contour contour2) {

	if (contour1.size() != contour2.size()) { return false; }

	for (size_t i = 0; i < contour1.size(); i++) {

		Point point1 = contour1[i];
		Point point2 = contour2[i];

		if (point1 != point2) { return false; }
	}

	return true;
}
