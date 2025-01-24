#include "LibMath/Vector.h"


LibMath::Vector2::Vector2() : m_x(0), m_y(0) {}

LibMath::Vector2::Vector2(float val) : m_x(val), m_y(val) {}

LibMath::Vector2::Vector2(float x, float y) : m_x(x), m_y(y) {}

LibMath::Vector2::Vector2(Vector2 const& other) : m_x(other.m_x), m_y(other.m_y) {}

LibMath::Vector2::Vector2(Vector2 const&& other) : m_x(other.m_x), m_y(other.m_y) {}

float& LibMath::Vector2::operator[](int index)
{
	if (index == 0)
	{
		return m_x;
	}
	else if (index == 1)
	{
		return m_y;
	}
	else
	{
		throw std::out_of_range("Invalid index: Vector2 only supports indices 0 and 1.");
	}
}

float LibMath::Vector2::operator[](int index) const
{
	if (index == 0)
	{
		return m_x;
	}
	else if (index == 1)
	{
		return m_y;
	}
	else
	{
		throw std::out_of_range("Invalid index: Vector2 only supports indices 0 and 1.");
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

float LibMath::Vector2::crossProduct(Vector2 const& other) const
{
	return m_x * other.m_x, m_y * other.m_y;
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

LibMath::Vector2 LibMath::Vector2::operator-()
{
	return Vector2(-m_x, -m_y);
}

LibMath::Vector2 LibMath::Vector2::operator+(Vector2 const& other) const
{
	return Vector2(m_x + other.m_x, m_y + other.m_y);
}

LibMath::Vector2 LibMath::Vector2::operator-(Vector2 const& other) const
{
	return Vector2(m_x - other.m_x, m_y - other.m_y);
}

LibMath::Vector2 LibMath::Vector2::operator*(float val) const
{
	return Vector2(m_x * val, m_y * val);
}

LibMath::Vector2 LibMath::Vector2::operator/(float val) const
{
	return Vector2(m_x / val, m_y / val);
}

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

bool LibMath::Vector2::isLongerThan(Vector2 const& other) const
{
	return magnitudeSquared() > other.magnitudeSquared();
}

bool LibMath::Vector2::isShorterThan(Vector2 const& other) const
{
	return magnitudeSquared() < other.magnitudeSquared();
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

LibMath::Radian LibMath::Vector2::angleBetween(Vector2 const& other) const
{
	float dot = dotProduct(other);
	float magnitudes = magnitude() * other.magnitude();

	if (magnitudes == 0.0)
	{
		throw std::runtime_error("Cannot calculate angle with a zero-length vector.");
	}

	float cosTheta = dot / magnitudes;
	return Radian(acos(cosTheta));
}

LibMath::Vector2 LibMath::Vector2::projectOnto(Vector2 const& other) const
{
	float otherMagnitudeSquared = other.magnitudeSquared();

	float scalar = dotProduct(other) / otherMagnitudeSquared;

	return Vector2(scalar * other.m_x, scalar * other.m_y);
}

LibMath::Vector2 LibMath::Vector2::reflectOnto(const Vector2& other) const
{
	Vector2 projection = projectOnto(other);
	return Vector2(2 * projection.m_x - m_x, 2 * projection.m_y - m_y);
}