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

		Matrix2x2&		operator=(Matrix2x2);

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

	private:
		float m_values[2][2];
	};
}

#endif // !LIBMATH_MATRIX_MATRIX2_H_