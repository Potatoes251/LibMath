#ifndef LIBMATH_MATRIX_MATRIX3_H_
#define LIBMATH_MATRIX_MATRIX3_H_

namespace LibMath
{
	class Matrix3x3
	{
	public:
		Matrix3x3();														// default constructor
		Matrix3x3(float);													// construct a matrix with diagonal
		Matrix3x3(float, float, float,										// construct a matrix with all components
			float, float, float,
			float, float, float);

		Matrix3x3& operator=(Matrix3x3 const);								// copy asignement

		float* operator[](int);

		Matrix3x3		operator+(Matrix3x3 const) const;
		Matrix3x3		operator*(float const);
		//Vector3			operator*(Vector3 const);
		Matrix3x3		operator*(Matrix3x3 const) const;

		bool			operator==(Matrix3x3 const) const;

		Matrix3x3& identity();												// create an identity matrix

		Matrix3x3& createScale(Vector2);									// return a scaling matrix

		static Matrix3x3		createTranslation(Vector2);					// return a translation matrix
		static Matrix3x3		createRotation(Point2D, Radian);			// return a rotation matrix
		static Matrix3x3		createTransform(Vector2, Radian, Vector2);	// return a transformation matrix

	private:
		float m_values[3][3];
	};
}

#endif // !LIBMATH_MATRIX_MATRIX3_H_
