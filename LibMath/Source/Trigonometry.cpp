
#include <cmath>

#include "LibMath/Trigonometry.h"


float LibMath::sin(Radian angle)
{
	angle.wrap();

	float x = angle.raw();
	float xSquare = x * x;
	float sin = x;

	float sign = -1;

	long long int factorials[8] = { 6, 120, 5040, 362880, 39916800, 6227020800, 1307674368000, 355687428096000 };
	// precompute the factorial to avoid to many calculations

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
	// precompute the factorial to avoid to many calculations

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
	return std::tan(angle.raw());
}