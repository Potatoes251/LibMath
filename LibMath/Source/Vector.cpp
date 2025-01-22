#include "LibMath/Vector.h"


LibMath::Vector2::Vector2() : m_x(0), m_y(0) {}

LibMath::Vector2::Vector2(float val) : m_x(val), m_y(val) {}

LibMath::Vector2::Vector2(float x, float y) : m_x(x), m_y(y) {}

LibMath::Vector2::Vector2(Vector2 const& other) : m_x(other.m_x), m_y(other.m_y) {}

float& LibMath::Vector2::operator[](int index)
{
	if (index == 0)
	{
		return m_x;
	}
	else
	{
		return m_y;
	}
}

float LibMath::Vector2::operator[](int index) const
{
	if (index == 0)
	{
		return m_x;
	}
	else
	{
		return m_y;
	}
}

float LibMath::Vector2::magnitude() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

float LibMath::Vector2::magnitudeSquared() const
{
	return (m_x * m_x + m_y * m_y);
}

float LibMath::Vector2::dotProduct(Vector2 const& other) const
{
	return (m_x * other.m_x + m_y * other.m_y);
}

LibMath::Vector2& LibMath::Vector2::operator=(Vector2 const& other)
{
	m_x = other.m_x;
	m_y = other.m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator=(Vector2 const&& other) noexcept
{
	m_x = other.m_x;
	m_y = other.m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator-()
{
	m_x = -m_x;
	m_y = -m_y;

	return *this;
}

//LibMath::Vector2& LibMath::Vector2::operator+(Vector2 other)
//{
//	Vector2 res(m_x + other.m_x, m_y + other.m_y);
//	return res;
//}
//
//LibMath::Vector2& LibMath::Vector2::operator-(Vector2 other)
//{
//	Vector2 res(m_x - other.m_x, m_y - other.m_y);
//	return res;
//}
//
//LibMath::Vector2& LibMath::Vector2::operator*(float val)
//{
//	Vector2 res(m_x * val, m_y * val);
//	return res;
//}
//
//LibMath::Vector2& LibMath::Vector2::operator/(float val)
//{
//	Vector2 res(m_x / val, m_y / val);
//	return res;
//}

LibMath::Vector2& LibMath::Vector2::operator+=(Vector2 const other)
{
	m_x += other.m_x;
	m_y += other.m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator-=(Vector2 const other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator*=(float val)
{
	m_x *= val;
	m_y *= val;

	return *this;
}

LibMath::Vector2& LibMath::Vector2::operator/=(float val)
{
	m_x /= val;
	m_y /= val;

	return *this;
}

bool LibMath::Vector2::operator==(Vector2 const& other) const
{
	return (this->m_x == other.m_x && this->m_y == other.m_y);
}

bool LibMath::Vector2::isUnitVector() const
{
	return 1 == magnitudeSquared();
}

void LibMath::Vector2::normalize()
{
	if (!isUnitVector())
	{
		float magnitude = this->magnitude();

		m_x = m_x / magnitude;
		m_y = m_y / magnitude;
	}
}
