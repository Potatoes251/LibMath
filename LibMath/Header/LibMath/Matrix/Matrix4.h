#ifndef LIBMATH_MATRIX_MATRIX4_H_
#define LIBMATH_MATRIX_MATRIX4_H_

namespace LibMath
{
	class Matrix4
	{
	public:
		Matrix4();														// default constructor
		Matrix4(float);													// construct a matrix with diagonal
		Matrix4(float, float, float, float,								// construct a matrix with all components
			float, float, float, float,
			float, float, float, float,
			float, float, float, float);

		Matrix4& operator=(Matrix4 const);								// copy asignement

		float* operator[](int);

	private:
		float m_values[4][4];
	};
}

#ifdef LIBMATH_VECTOR_VECTOR4_H_
#include "Matrix4Vector4Operation.h"
#endif // LIBMATH_MATRIX_H_

#endif // !LIBMATH_MATRIX_MATRIX4_H_
