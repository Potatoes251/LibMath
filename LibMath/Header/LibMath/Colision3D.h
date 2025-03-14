#ifndef COLISION3D_H
#define COLISION3D_H

#include "Geometry3D.h"
#include "Vector/Vector3.h"

namespace LibMath
{
	//3D collision

	bool			colisionLinePlane(Line3D, Plane);
	bool			colisionTwoPlane(Plane, Plane);

	bool			colisionPointSphere(Point3D, Sphere);
	bool			colisionLineSphere(Line3D, Sphere);		// todo
	bool			colisionPlaneSphere(Plane, Sphere);		// todo
	bool			colisionTwoSphere(Sphere, Sphere);

	bool			colisionPointCapsule(Point3D, Capsule);	// todo
	bool			colisionLineCapsule(Line3D, Capsule);	// todo
	bool			colisionPlaneCapsule(Plane, Capsule);	// todo
	bool			colisionSphereCapsule(Sphere, Capsule);	// todo
	bool			colisionTwoCapsule(Capsule, Capsule);	// todo

	//void			getMinMax(float& min, float& max, Point3D corners[4], Vector2 axis);
	//void			getNormals(Vector2 axes[8], Point3D corners1[4], Point3D corners2[4]);

	bool			colisionPointPrism(Point3D, Prism);		// aabb
	bool			colisionLinePrism(Line3D, Prism);		// aabb		todo
	bool			colisionSpherePrism(Sphere, Prism);		// obb		todo
	bool			colisionCapsulePrism(Capsule, Prism);	// aabb		todo
	bool			colisionTwoPrism(Prism, Prism);			// obb		todo
}


#endif