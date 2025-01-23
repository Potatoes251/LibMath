#pragma once
#include "Geometry.h"

constexpr float g_epsilon = 1e-6f;

namespace LibMath
{
	//2D collision

	bool			colisionPointLine(Point2D, Line2D);				// done
	bool			colisionTwoLine(Line2D, Line2D);				// done

	bool			colisionPointCircle(Point2D, Circle);			// done
	bool			colisionLineCircle(Line2D, Circle);				// done
	bool			colisionTwoCircle(Circle, Circle);				// done

	bool			colisionPointRectangle(Point2D, Rectangle);		// TODO
	bool			colisionLineRectangle(Line2D, Rectangle);		// TODO
	bool			colisionTwoRectangle(Rectangle, Rectangle);		// TODO


}