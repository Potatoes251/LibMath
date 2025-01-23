#ifndef LIBMATH_MATRIX_MATRIX2_H_
#define LIBMATH_MATRIX_MATRIX2_H_

#include "LibMath/Vector.h"

namespace LibMath
{
	class Matrix2x2
	{
	public:
		Matrix2x2();
		Matrix2x2(float);
		Matrix2x2(float, float, float, float);

		Matrix2x2&		operator=(Matrix2x2&);

		float*			operator[](int);

		Matrix2x2&		operator+(Matrix2x2);
		Matrix2x2		operator*(float);
		Vector2			operator*(Vector2);
		Matrix2x2&		operator*(Matrix2x2);

		void			transpose();
		float			determinant();
		void			minors();
		void			cofactors();
		void			adjugate();
		void			inverse();

		Matrix2x2&		identity();

	private:
		float m_values[2][2];
	};


	class Matrix3x3
	{
	public:
		Matrix3x3();
		Matrix3x3(float);
		Matrix3x3(float, float, float, float);

		Matrix3x3&		operator=(Matrix3x3&);

		float*			operator[](int);

		Matrix3x3&		operator+(Matrix3x3);
		Matrix3x3		operator*(float);
		Vector2			operator*(Vector2);
		Matrix3x3&		operator*(Matrix3x3);

		Matrix3x3&		identity();

	private:
		float m_values[3][3];
	};
}

#endif // !LIBMATH_MATRIX_MATRIX2_H_