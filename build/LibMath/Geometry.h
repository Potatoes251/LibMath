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

		Rectangle();
		Rectangle(Point2D, float, float);
		Rectangle(Point2D, float, float, float);

	private:
		Point2D m_corner;
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