#ifndef LIBMATH_ANGLE_H_
#define LIBMATH_ANGLE_H_

#define _USE_MATH_DEFINES
#include <cmath>
#include "Angle/Radian.h"
#include "Angle/Degree.h"

constexpr float g_Pi = static_cast<float>(M_PI);
constexpr float g_twoPi = 2 * static_cast<float>(M_PI);
constexpr float g_epsilon = 1e-6f;

float wrapWithinRange(float value, float min, float max);

#endif // !LIBMATH_ANGLE_H_
