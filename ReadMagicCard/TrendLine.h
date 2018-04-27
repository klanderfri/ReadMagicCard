#pragma once
class TrendLine
{
public:
	TrendLine();
	TrendLine(long double slope, long double offset);
	TrendLine(const std::vector<cv::Point2d>& points);
	~TrendLine();

	//Gets the end points of the line.
	std::vector<cv::Point2d> GetEndPoints(long double leftLimitX, long double rightLimitX);
	//Gets the Y value for a given X value.
	long double GetY(long double x);
	//Gets the X value for a given Y value.
	long double GetX(long double y);
	//Tells if the line is a zero line, i.e equivalent with most often is the X-axis.
	bool IsZeroLine();
	//Gets the equation in the form 'y = kx + m'.
	std::wstring GetEquation();
	//Gets the equation in the form 'y - kx - m = 0'.
	std::wstring GetZeroEquation();
	//Gets the perpendicular distance between two lines.
	static long double GetPerpendicularDistance(TrendLine lineA, TrendLine lineB);
	//Gets the perpendicular distance between the line and a point.
	long double GetPerpendicularDistance(cv::Point2d point);
	//Gets another line perpendicular to the line.
	TrendLine GetPerpendicularLine(cv::Point2d pointOnPerpendicularLine);
	//Gets another line parallel to the line.
	TrendLine GetParallelLine(cv::Point2d pointOnParallelLine);
	//Gets the point in which thw two lines meet.
	static cv::Point2d GetIntersectionPoint(TrendLine lineA, TrendLine lineB);
	//Gets the clockwise angle from the norm line to the relation line.
	static long double GetAngleBetweenLines(TrendLine normLine, TrendLine relationLine);
	//Gets the angle between the line and the X axis.
	long double GetAngleToAxisX();
	//Gets the two lines parallel to the line, having all the points between them.
	std::vector<TrendLine> GetBoundLines(std::vector<cv::Point2d> points);

	//The slope of the line.
	long double Slope = 0;
	//The offset of the line.
	long double Offset = 0;

	//The line representing the X axis.
	static TrendLine XAxis;

private:

	//Sets up the member variables.
	void setupMemberVariables(long double slope, long double offset);
};

