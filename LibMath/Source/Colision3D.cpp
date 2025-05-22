#include "LibMath/Colision3D.h"


bool	LibMath::colisionLinePlane(Line3D line, Plane plane)
{
	return line.getDirection().dot(plane.getNormal()) != 0;
}

bool	LibMath::colisionTwoPlane(Plane plane1, Plane plane2)
{
	return plane1.getNormal() != plane2.getNormal();
}


bool	LibMath::colisionPointSphere(Point3D point, Sphere sphere)
{
	return sphere.getCenter().distanceSquare(point) - sphere.getRadius() > g_epsilon;
}

bool	LibMath::colisionRaySphere(Line3D line3D, Sphere sphere)
{
	Vector3 m = line3D.getCenter() - sphere.getCenter();

	float b = m.dot(line3D.getDirection());
	float c = m.dot(m) - sphere.getRadius() * sphere.getRadius();
	return 0 <= (b * b * c);
}

bool	LibMath::colisionPlaneSphere(Plane plane, Sphere sphere)
{
	return plane.getPointOnPlane().distance(sphere.getCenter()) < sphere.getRadius();
}

bool	LibMath::colisionTwoSphere(Sphere sphere1, Sphere sphere2)
{
	return sphere1.getCenter().distanceSquare(sphere2.getCenter()) - (sphere1.getRadius() + sphere2.getRadius()) > g_epsilon;
}




bool LibMath::colisionPointPrism(Point3D point, Prism prism)
{
	return (point.getX() <= prism.getCenter().getX() + prism.extentX() &&
			point.getY() <= prism.getCenter().getY() + prism.extentY() &&
			point.getZ() <= prism.getCenter().getZ() + prism.extentZ() &&
			point.getX() >= prism.getCenter().getX() &&
			point.getY() >= prism.getCenter().getY() &&
			point.getZ() >= prism.getCenter().getZ());
}