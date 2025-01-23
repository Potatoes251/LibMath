#include "LibMath/Matrix.h"


LibMath::Matrix2x2::Matrix2x2()
{
	//m_values = { {0,0}, {0,0} };
	m_values[0][0] = 0;
	m_values[0][1] = 0;
	m_values[1][0] = 0;
	m_values[1][1] = 0;
}

LibMath::Matrix2x2::Matrix2x2(float diagonal)
{
	m_values[0][0] = diagonal;
	m_values[0][1] = 0;
	m_values[1][0] = 0;
	m_values[1][1] = diagonal;
}

LibMath::Matrix2x2::Matrix2x2(float val1, float val2, float val3, float val4)
{
	m_values[0][0] = val1;
	m_values[0][1] = val2;
	m_values[1][0] = val3;
	m_values[1][1] = val4;
}

LibMath::Matrix2x2& LibMath::Matrix2x2::operator=(Matrix2x2 other)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2;j++)
		{
			m_values[i][j] = other.m_values[i][j];
		}
	}
	return *this;
}

float* LibMath::Matrix2x2::operator[](int index)
{
	return m_values[index];
}

LibMath::Matrix2x2& LibMath::Matrix2x2::operator+(Matrix2x2 other)
{
	m_values[0][0] += other.m_values[0][0];
	m_values[0][1] += other.m_values[0][1];
	m_values[1][0] += other.m_values[1][0];
	m_values[1][1] += other.m_values[1][1];

	return *this;
}

LibMath::Matrix2x2 LibMath::Matrix2x2::operator*(float val)
{
	return Matrix2x2 (
		m_values[0][0] * val,
		m_values[0][1] * val,
		m_values[1][0] * val,
		m_values[1][1] * val);

}

LibMath::Vector2 LibMath::Matrix2x2::operator*(Vector2 v)
{
	float x = v[0] * m_values[0][0] + v[1] * m_values[0][1];
	float y = v[0] * m_values[1][0] + v[1] * m_values[1][1];
	Vector2 product(x, y);
	return product;
}

LibMath::Matrix2x2& LibMath::Matrix2x2::operator*(Matrix2x2 other)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2;j++)
		{
			m_values[i][j] = m_values[i][0] * other.m_values[0][j] + m_values[i][1] * other.m_values[1][j];
		}
	}
	return *this;
}

void LibMath::Matrix2x2::transpose()
{
	float temp = m_values[0][1];
	m_values[0][1] = m_values[1][0];
	m_values[1][0] = temp;
}

float LibMath::Matrix2x2::determinant()
{
	return m_values[0][0] * m_values[1][1] - m_values[0][1] * m_values[1][0];
}

void LibMath::Matrix2x2::minors()
{
	float temp = m_values[0][0];
	m_values[0][0] = m_values[1][1];
	m_values[1][1] = temp;

	temp = m_values[0][1];
	m_values[0][1] = m_values[1][0];
	m_values[1][0] = temp;
}

void LibMath::Matrix2x2::cofactors()
{
	float temp = m_values[0][0];
	m_values[0][0] = m_values[1][1];
	m_values[1][1] = temp;

	temp = m_values[0][1];
	m_values[0][1] = -m_values[1][0];
	m_values[1][0] = -temp;
}

void LibMath::Matrix2x2::adjugate()
{
	float temp = m_values[0][0];
	m_values[0][0] = m_values[1][1];
	m_values[1][1] = temp;

	m_values[0][1] = -m_values[0][1];
	m_values[1][0] = -m_values[1][0];
}

void LibMath::Matrix2x2::inverse()
{
	float det = determinant();

	adjugate();

	m_values[0][0] /= det;
	m_values[0][1] /= det;
	m_values[1][0] /= det;
	m_values[1][1] /= det;
}
