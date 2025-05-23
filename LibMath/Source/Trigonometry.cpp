
#include <cmath>

#include "LibMath/Trigonometry.h"
#include <iostream>


float LibMath::sin(Radian angle)
{
	angle.wrap();

	float x = angle.raw();
	float xSquare = x * x;
	float sin = x;

	float sign = -1;

	long long int factorials[8] = { 6, 120, 5040, 362880, 39916800, 6227020800, 1307674368000, 355687428096000 };
	// precompute the factorial to avoid too many unnecessary calculations

	for (int i = 0; i < 8; ++i)
	{
		x *= xSquare;
		sin += sign * x / factorials[i];
		sign = -sign;
	}
	return sin;
}

float LibMath::cos(Radian angle)
{
	angle.wrap();

	double	x = angle.raw();
	double	xSquare = x * x;
	double	cos = 1;
	int	sign = -1;
	long long int		factorials[8] = { 2, 24, 720, 40320, 3628800, 479001600, 87178291200, 20922789888000 };
	// precompute the factorial to avoid too many unnecessary calculations

	x = 1;

	for (int i = 0; i < 8; ++i)
	{
		x *= xSquare;
		cos += sign * x / factorials[i];
		sign = -sign;
	}
	return static_cast<float>(cos);
}

float LibMath::tan(Radian angle)
{
	return static_cast<float>(sin(angle) / cos(angle));
}

//LibMath::Radian LibMath::asin(float)
//{
//
//
//	return Radian();
//}

LibMath::Radian LibMath::atan(float x)
{
	if (x > 1.f)
	{
		const float halfPi = g_Pi / 2;
		return Radian(halfPi) - Radian(atan(1 / x));
	}

	int		tanSign = 1;	// store the sign of x

	if (x < 0)
	{
		tanSign = -1;
		x = -x;
	}

	float	xPower = x;			// store the consecutive power of x (x^1, x^3,...)
	float	xSquare = x * x;
	float	angle = x;
	int		sign = 1;
	int		denominator = 1;


	for (int i = 0; i < 8; ++i)
	{
		xPower *= xSquare;
		denominator += 2;
		sign = -sign;
		angle += sign * xPower / denominator;
	}
	return Radian(tanSign * angle);
}

LibMath::Radian LibMath::atan(float y, float x)	// atan per quadrant
{
	if (x == 0)	// angle == 0
	{
		if (y > 0)
		{
			return Radian(g_Pi / 2);
		}
		else if (y < 0)
		{
			return Radian(-g_Pi / 2);
		}
		else // y == 0
		{
			return Radian(0);
		}
	}

	Radian baseAngle = atan(y / x);

	if (x > 0)
	{
		return baseAngle;  // Quadrant I or IV sign depend on Y anyway
	}
	else // x < 0
	{
		if (y >= 0)
		{
			return baseAngle + Radian(g_Pi); // Quadrant II
		}
		else
		{
			return baseAngle - Radian(g_Pi); // Quadrant III
		}
	}
}
