#ifndef LIBMATH_VECTOR_VECTOR2_H_
#define LIBMATH_VECTOR_VECTOR2_H_

namespace LibMath
{
	class Vector2
	{
	public:
						Vector2();										// set all component to 0
		explicit		Vector2(float);									// set all component to the same value
						Vector2(float, float);							// set all component individually
						Vector2(Vector2 const&);						// copy all component
						~Vector2() = default;

		Vector2&		operator=(Vector2 const&);
		Vector2&		operator=(Vector2 const&&);

		Vector2&		operator-();

		Vector2&		operator+(Vector2);
		Vector2&		operator-(Vector2);
		Vector2&		operator*(float);
		Vector2&		operator/(float);

		Vector2&		operator+=(Vector2 const);
		Vector2&		operator-=(Vector2 const);
		Vector2&		operator*=(float);
		Vector2&		operator/=(float);
						
		float&			operator[](int);								// return this vector component value
		float			operator[](int) const;							// return this vector component value

		float			magnitude() const;								// return vector magnitude
		float			magnitudeSquared() const;						// return square value of the vector magnitude
		float			dotProduct(Vector2 const&) const;
		Vector2&		crossProduct(Vector2 const&) const;

		bool			operator==(Vector2 const&) const;
		bool			isUnitVector() const;							// return true if this vector magnitude is 1

		void			normalize();									// scale this vector to have a magnitude of 1


	private:
		float m_x;
		float m_y;
	};
}

#endif // !LIBMATH_VECTOR_VECTOR2_H_