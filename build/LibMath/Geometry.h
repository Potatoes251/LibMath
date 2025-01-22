#pragma once


namespace LibMath
{
	//2D classes

	class Point2D
	{
	public:

		Point2D();
		Point2D(float, float);

		float distance(Point2D) const;
		float distanceSquare(Point2D) const;

	private:
		float m_x;
		float m_y;
	};


	class Line2D
	{
	public:

		Line2D();
		Line2D(Point2D, Point2D);

		float length() const;
		float lengthSquare() const;

	private:
		Point2D m_start;
		Point2D m_end;
	};


	class Rectangle
	{
	public:

	private:
		Point2D m_corner1;
		Point2D m_corner2;
		Point2D m_corner3;
		Point2D m_corner4;
	};


	class Circle
	{
	public:

		Circle();
		Circle(Point2D, float);
		Circle(Circle const&);

		float getRadius() const;
		Point2D getCenter() const;

	private:
		Point2D m_center;
		float m_radius;
	};

	//2D collision

	bool colisionPointCircle(Point2D, Circle);
	bool colisionTwoCircle(Circle, Circle);
	bool colisionTwoRectangle(Rectangle, Rectangle);
}