#pragma once

#include "Angle.h"

namespace LibMath
{
	//2D classes

	class Point2D
	{
	public:

		Point2D();
		Point2D(float, float);

		float			getX() const;
		float			getY() const;

		float			distance(Point2D) const;
		float			distanceSquare(Point2D) const;

	private:
		float m_x;
		float m_y;
	};


	class Line2D
	{
	public:

		Line2D();
		Line2D(Point2D, Point2D);

		Point2D			getStart() const;
		Point2D			getEnd() const;

		float			length() const;
		float			lengthSquare() const;
		float			slope() const;
		float			slopeIntercept() const;


	private:
		Point2D m_start;
		Point2D m_end;
	};


	class Rectangle
	{
	public:

		Rectangle();
		Rectangle(Point2D, float, float);		// ctor without rotation
		Rectangle(Point2D, float, float, float);// ctor with rotation

		float			extentX() const;
		float			extentY() const;
		float			getRotation() const;
		float			getWidth() const;
		float			getHeight() const;
		Point2D			getCenter() const;

		void			getCorners(Point2D corners[4]);

	private:
		Point2D	m_center;
		float m_width;
		float m_height;
		float m_rotation;
	};


	class Circle
	{
	public:

		Circle();
		Circle(Point2D, float);
		Circle(Circle const&);

		float			getRadius() const;
		Point2D			getCenter() const;

	private:
		Point2D m_center;
		float m_radius;
	};
}