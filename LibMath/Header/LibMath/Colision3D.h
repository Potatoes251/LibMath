#ifndef COLISION3D_H
#define COLISION3D_H

#include "Geometry3D.h"
#include "Vector/Vector3.h"

namespace LibMath
{
	//3D collision

	bool			collisionLinePlane(Line3D, Plane);
	bool			collisionTwoPlane(Plane, Plane); 

	bool			collisionPointSphere(Point3D, Sphere);
	bool			collisionRaySphere(Line3D, Sphere);
	bool			collisionPlaneSphere(Plane, Sphere);
	bool			collisionTwoSphere(Sphere, Sphere);

	bool			collisionPointCapsule(Point3D, Capsule);
	bool			collisionRayCapsule(Line3D, Capsule);
	bool			collisionPlaneCapsule(Plane, Capsule);
	bool			collisionSphereCapsule(Sphere, Capsule);
	bool			collisionTwoCapsule(Capsule, Capsule);

	bool			collisionPointPrism(Point3D, Prism);					// aabb
	bool			collisionRayPrism(Line3D, Prism);						// aabb
	bool			intersectionRayPrism(Line3D, Prism, Vector3&);			// aabb		return the first touching point
	bool			collisionCapsulePrism(Capsule, Prism);					// aabb
	bool			intersectionCapsulePrism(Capsule, Prism, Vector3&);		// aabb		return the first correction to apply to make em not touch
}


#endif