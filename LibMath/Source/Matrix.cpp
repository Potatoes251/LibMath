#include "LibMath/Matrix.h"
#include "LibMath/Trigonometry.h"

LibMath::Matrix2x2::Matrix2x2()
{
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

LibMath::Matrix2x2& LibMath::Matrix2x2::operator=(Matrix2x2 const other)
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

LibMath::Matrix2x2 LibMath::Matrix2x2::operator+(Matrix2x2 const other) const
{
	Matrix2x2 sum;
	sum[0][0] = m_values[0][0] + other.m_values[0][0];
	sum[0][1] = m_values[0][1] + other.m_values[0][1];
	sum[1][0] = m_values[1][0] + other.m_values[1][0];
	sum[1][1] = m_values[1][1] + other.m_values[1][1];

	return sum;
}

LibMath::Matrix2x2 LibMath::Matrix2x2::operator*(float const val) const
{
	return Matrix2x2 (
		m_values[0][0] * val,
		m_values[0][1] * val,
		m_values[1][0] * val,
		m_values[1][1] * val);

}

LibMath::Vector2 LibMath::Matrix2x2::operator*(Vector2 const v) const
{
	float x = v[0] * m_values[0][0] + v[1] * m_values[0][1];
	float y = v[0] * m_values[1][0] + v[1] * m_values[1][1];
	Vector2 product(x, y);
	return product;
}

LibMath::Matrix2x2 LibMath::Matrix2x2::operator*(Matrix2x2 const other) const
{
	Matrix2x2 product;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2;j++)
		{
			product[i][j] = m_values[i][0] * other.m_values[0][j] + m_values[i][1] * other.m_values[1][j];
		}
	}
	return product;
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

LibMath::Matrix2x2& LibMath::Matrix2x2::identity()
{
	m_values[0][0] = 1;
	m_values[0][1] = 0;
	m_values[1][0] = 0;
	m_values[1][1] = 1;

	return *this;
}

LibMath::Matrix2x2& LibMath::Matrix2x2::createScale(Vector2 v)
{
	m_values[0][0] = v[0];
	m_values[1][1] = v[1];

	return *this;
}

LibMath::Matrix2x2 LibMath::Matrix2x2::createRotation(Point2D point, Radian angle)
{
	Matrix2x2 toOrigin;
	toOrigin[0][2] = -point.getX();
	toOrigin[1][2] = -point.getY();

	Matrix2x2 rotation;
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);
	rotation[0][0] = cosTheta;
	rotation[0][1] = -sinTheta;
	rotation[1][0] = sinTheta;
	rotation[1][1] = cosTheta;

	Matrix2x2 toPivot;
	toPivot[0][2] = point.getX();
	toPivot[1][2] = point.getY();

	return toPivot * rotation * toOrigin;
}

LibMath::Matrix2x2 LibMath::Matrix2x2::createTransform(Radian angle, Vector2 scale)
{
	Matrix2x2 rotation = createRotation(Point2D(0, 0), angle);

	Matrix2x2 scaler;
	scaler.createScale(scale);

	return rotation * scaler;
}


LibMath::Matrix3x3::Matrix3x3()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3;j++)
		{
			m_values[i][j] = 0;
		}
	}
}

LibMath::Matrix3x3::Matrix3x3(float val)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
			{
				m_values[i][j] = val;
			}
			else
			{
				m_values[i][j] = 0;
			}
		}
	}
}

LibMath::Matrix3x3& LibMath::Matrix3x3::operator=(Matrix3x3 const other)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3;j++)
		{
			m_values[i][j] = other.m_values[i][j];
		}
	}
	return *this;
}

float* LibMath::Matrix3x3::operator[](int index)
{
	return m_values[index];
}

LibMath::Matrix3x3 LibMath::Matrix3x3::operator+(Matrix3x3 const other) const
{
	Matrix3x3 sum;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3;j++)
		{
			sum[i][j] += other.m_values[i][j];
		}
	}

	return sum;
}

LibMath::Matrix3x3 LibMath::Matrix3x3::operator*(float const val)
{
	Matrix3x3 res{};
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3;j++)
		{
			res.m_values[i][j] = m_values[i][j] * val;
		}
	}
	return res;
}

LibMath::Matrix3x3 LibMath::Matrix3x3::operator*(Matrix3x3 const other) const
{
	Matrix3x3 product;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3;j++)
		{
			product[i][j] = m_values[i][0] * other.m_values[0][j] + m_values[i][1] * other.m_values[1][j];
		}
	}
	return product;
}

LibMath::Matrix3x3& LibMath::Matrix3x3::identity()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
			{
				m_values[i][j] = 1;
			}
			else
			{
				m_values[i][j] = 0;
			}
		}
	}
	return *this;
}

LibMath::Matrix3x3& LibMath::Matrix3x3::createScale(Vector2 v)
{
	m_values[0][0] = v[0];
	m_values[1][1] = v[1];

	return *this;
}

LibMath::Matrix3x3 LibMath::Matrix3x3::createTranslation(Vector2 v)
{
	Matrix3x3 TransMatrix{};
	TransMatrix.identity();
	TransMatrix[0][2] = v[0];
	TransMatrix[1][2] = v[1];

	return TransMatrix;
}

LibMath::Matrix3x3 LibMath::Matrix3x3::createRotation(Point2D point, Radian angle)
{
	Matrix3x3 toOrigin;
	toOrigin[0][2] = -point.getX();
	toOrigin[1][2] = -point.getY();

	Matrix3x3 rotation;
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);
	rotation[0][0] = cosTheta;
	rotation[0][1] = -sinTheta;
	rotation[1][0] = sinTheta;
	rotation[1][1] = cosTheta;

	Matrix3x3 toPivot;
	toPivot[0][2] = point.getX();
	toPivot[1][2] = point.getY();

	return toPivot * rotation * toOrigin;
}

LibMath::Matrix3x3 LibMath::Matrix3x3::createTransform(Vector2 translate, Radian angle, Vector2 scale)
{
	Matrix3x3 translation = createTranslation(translate);

	Matrix3x3 rotation = createRotation(Point2D(0, 0), angle);

	Matrix3x3 scaler;
	scaler.createScale(scale);

	return translation * rotation * scaler;
}