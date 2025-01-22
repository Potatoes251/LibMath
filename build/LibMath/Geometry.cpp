#define _USE_MATH_DEFINES
#include <cmath>

#include "Geometry.h"

LibMath::Point2D::Point2D() :
	m_x(0), 
	m_y(0)
{}

LibMath::Point2D::Point2D(float x, float y) : 
	m_x(x),
	m_y(y)
{}

float LibMath::Point2D::getX() const
{
	return m_x;
}

float LibMath::Point2D::getY() const
{
	return m_y;
}

float LibMath::Point2D::distance(Point2D other) const
{
	return sqrt((m_x - other.m_x) * (m_x - other.m_x) + (m_y - other.m_y) * (m_y - other.m_y));
}

float LibMath::Point2D::distanceSquare(Point2D other) const
{
	return ((m_x - other.m_x) * (m_x - other.m_x) + (m_y - other.m_y) * (m_y - other.m_y));
}

LibMath::Line2D::Line2D() :
	m_start(Point2D{}), 
	m_end(Point2D{}) 
{}

LibMath::Line2D::Line2D(Point2D start, Point2D end) :
	m_start(start), 
	m_end(end) 
{}

LibMath::Point2D LibMath::Line2D::getStart() const
{
	return m_start;
}

LibMath::Point2D LibMath::Line2D::getEnd() const
{
	return m_end;
}

float LibMath::Line2D::length() const
{
	return m_start.distance(m_end);
}

float LibMath::Line2D::lengthSquare() const
{
	return m_start.distanceSquare(m_end);
}

float LibMath::Line2D::slope() const
{
	return (m_start.getY() - m_end.getY()) / (m_start.getX() - m_end.getX());
}

float LibMath::Line2D::slopeIntercept() const
{
	return m_start.getY() - slope() * m_start.getX();
}

LibMath::Rectangle::Rectangle() : 
	m_corner(Point2D{}),
	m_width(0.f),
	m_height(0.f), 
	m_rotation(0.f) 
{}

LibMath::Rectangle::Rectangle(Point2D corner, float width, float height) : 
	m_corner(corner), 
	m_width(width), 
	m_height(height), 
	m_rotation(0.f) 
{}

LibMath::Rectangle::Rectangle(Point2D corner, float width, float height, float rotation) :
	m_corner(corner), 
	m_width(width), 
	m_height(height), 
	m_rotation(rotation)
{}

float LibMath::Rectangle::extentX() const
{
	return m_width;
}

float LibMath::Rectangle::extentY() const
{
	return m_height;
}




LibMath::Circle::Circle() : 
	m_center(Point2D{}),
	m_radius(0.f)
{}

LibMath::Circle::Circle(Point2D center, float radius) :
	m_center(center),
	m_radius(radius)
{}

LibMath::Circle::Circle(Circle const& other) : 
	m_center(other.m_center), 
	m_radius(other.m_radius)
{}

float LibMath::Circle::getRadius() const
{
	return m_radius;
}

LibMath::Point2D LibMath::Circle::getCenter() const
{
	return m_center;
}