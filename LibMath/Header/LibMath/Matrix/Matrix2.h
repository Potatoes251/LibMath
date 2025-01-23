#ifndef LIBMATH_MATRIX_MATRIX2_H_
#define LIBMATH_MATRIX_MATRIX2_H_

#include "LibMath/Vector.h"
#include "LibMath/Geometry.h"

namespace LibMath
{
	class Matrix2x2
	{
	public:
		Matrix2x2();
		Matrix2x2(float);
		Matrix2x2(float, float, float, float);

		Matrix2x2&		operator=(Matrix2x2 const);

		float*			operator[](int);

		Matrix2x2&		operator+(Matrix2x2 const);
		Matrix2x2		operator*(float const);
		Vector2			operator*(Vector2 const);
		Matrix2x2&		operator*(Matrix2x2 const);

		void			transpose();
		float			determinant();
		void			minors();
		void			cofactors();
		void			adjugate();
		void			inverse();

		Matrix2x2&		identity();

		Matrix2x2&				createScale(Vector2);
		static Matrix2x2		createRotation(Point2D, Radian);
		static Matrix2x2		createTransform(Radian, Vector2);

	private:
		float m_values[2][2];
	};


	class Matrix3x3
	{
	public:
		Matrix3x3();
		Matrix3x3(float);

		Matrix3x3&		operator=(Matrix3x3 const);

		float*			operator[](int);

		Matrix3x3&		operator+(Matrix3x3 const);
		Matrix3x3		operator*(float const);
		Vector2			operator*(Vector2 const);
		Matrix3x3&		operator*(Matrix3x3 const);

		Matrix3x3&		identity();

		Matrix3x3&		createScale(Vector2);

		static Matrix3x3		createTranslation(Vector2);
		static Matrix3x3		createRotation(Point2D, Radian);
		static Matrix3x3		createTransform(Vector2, Radian, Vector2);

	private:
		float m_values[3][3];
	};
}

#endif // !LIBMATH_MATRIX_MATRIX2_H_