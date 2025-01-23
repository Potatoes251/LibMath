
#include <cmath>

#include "Colision.h"

bool LibMath::colisionPointLine(Point2D point, Line2D line)
{
	float lineLength = line.length();

	float d1 = point.distance(line.getStart());
	float d2 = point.distance(line.getEnd());

	return (d1 + d2) - lineLength <= g_epsilon;
}

bool LibMath::colisionTwoLine(Line2D line1, Line2D line2)
{
	float x1 = line1.getStart().getX();
	float y1 = line1.getStart().getY();
	float x2 = line1.getEnd().getX();
	float y2 = line1.getEnd().getY();

	float x3 = line2.getStart().getX();
	float y3 = line2.getStart().getY();
	float x4 = line2.getEnd().getX();
	float y4 = line2.getEnd().getY();

	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
	{
		return true;
	}
	return false;
}

bool LibMath::colisionPointCircle(Point2D point, Circle circle)
{
	return point.distance(circle.getCenter()) <= circle.getRadius();
}

bool LibMath::colisionLineCircle(Line2D line, Circle circle)
{
	if (colisionPointCircle(line.getStart(), circle) ||
		colisionPointCircle(line.getEnd(), circle))
	{
		return true;
	}

	float lineLength = line.lengthSquare();

	float cx = circle.getCenter().getX();
	float cy = circle.getCenter().getY();
	float x1 = line.getStart().getX();
	float y1 = line.getStart().getY();
	float x2 = line.getEnd().getX();
	float y2 = line.getEnd().getY();

	float dot = (((cx - x1) * (x2 - x1)) + ((cy - y1) * (y2 - y1))) / lineLength;

	Point2D closest(x1 + (dot * (x2 - x1)), y1 + (dot * (y2 - y1)));


	return colisionPointLine(closest, line) && closest.distance(circle.getCenter()) <= circle.getRadius();
}

bool LibMath::colisionTwoCircle(Circle circle1, Circle circle2)
{
	return circle1.getCenter().distance(circle2.getCenter()) <= (circle1.getRadius() + circle2.getRadius());
}


bool LibMath::colisionTwoRectangle(Rectangle rec1, Rectangle rec2)
{
	//if (rec.)
}