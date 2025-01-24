#ifndef LIBMATH_MATRIX_MATRIX2_H_
#define LIBMATH_MATRIX_MATRIX2_H_

#include "LibMath/Vector.h"
#include "LibMath/Geometry.h"

namespace LibMath
{
	class Matrix2x2
	{
	public:
		Matrix2x2();								// default constructor
		Matrix2x2(float);							// construct a matrix with the diagonal
		Matrix2x2(float, float, float, float);		// construct a matrix with all components

		Matrix2x2&		operator=(Matrix2x2 const);	// copy asignement

		float*			operator[](int);

		Matrix2x2		operator+(Matrix2x2 const) const;
		Matrix2x2		operator*(float const) const;
		Vector2			operator*(Vector2 const) const;
		Matrix2x2		operator*(Matrix2x2 const) const;

		void			transpose();				// transpose the matrix
		float			determinant();				// return the determinant of the matrix
		void			minors();					// change the matrix into a minor matrix
		void			cofactors();				// change the matrix into a cofactor matrix
		void			adjugate();					// change the matrix into the adjugate matrix
		void			inverse();					// inverse the matrix

		Matrix2x2&		identity();									// create an identity matrix

		Matrix2x2&				createScale(Vector2);				// return a scaling matrix
		static Matrix2x2		createRotation(Point2D, Radian);	// return a rotation matrix
		static Matrix2x2		createTransform(Radian, Vector2);	// return a transformation matrix

	private:
		float m_values[2][2];
	};


	class Matrix3x3
	{
	public:
		Matrix3x3();														// default constructor
		Matrix3x3(float);													// construct a matrix with diagonal

		Matrix3x3&		operator=(Matrix3x3 const);							// copy asignement

		float*			operator[](int);

		Matrix3x3		operator+(Matrix3x3 const) const;
		Matrix3x3		operator*(float const);
		//Vector2			operator*(Vector2 const);
		Matrix3x3		operator*(Matrix3x3 const) const;

		Matrix3x3&		identity();											// create an identity matrix

		Matrix3x3&		createScale(Vector2);								// return a scaling matrix

		static Matrix3x3		createTranslation(Vector2);					// return a translation matrix
		static Matrix3x3		createRotation(Point2D, Radian);			// return a rotation matrix
		static Matrix3x3		createTransform(Vector2, Radian, Vector2);	// return a transformation matrix

	private:
		float m_values[3][3];
	};
}

#endif // !LIBMATH_MATRIX_MATRIX2_H_