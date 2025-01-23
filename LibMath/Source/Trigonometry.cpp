
#include <cmath>

#include "LibMath/Trigonometry.h"


float LibMath::sin(Radian angle)
{
	return std::sin(angle.raw());
}

float LibMath::cos(Radian angle)
{
	return std::cos(angle.raw());
}

float LibMath::tan(Radian angle)
{
	return std::tan(angle.raw());
}