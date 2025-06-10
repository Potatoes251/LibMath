#include <LibMath/Colision.h>
#include <LibMath/Colision3D.h>
#include <LibMath/Geometry.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// 2D tests
TEST_CASE("Point2D", "[.all][geometry][point2d]")
{
	SECTION("Instantiation")
	{

		{
			[[maybe_unused]] LibMath::Point2D temp;
		}

		// Default constructor
		LibMath::Point2D empty;
		CHECK(empty.getX() == 0.f);
		CHECK(empty.getY() == 0.f);

		// Parameterized constructor
		LibMath::Point2D point(3.0f, 4.0f);
		CHECK(point.getX() == 3.0f);
		CHECK(point.getY() == 4.0f);

		LibMath::Point2D copy( point );
		CHECK(point.getX() == copy.getX());
		CHECK(point.getY() == copy.getY());

		LibMath::Point2D moved(LibMath::Point2D(5.0f,7.1f));
		CHECK(moved.getX() == 5.0f);
		CHECK(moved.getY() == 7.1f);

		// Copy assignment
		LibMath::Point2D point2( 3.0f, 4.0f );
		LibMath::Point2D copy2 = point2;
		CHECK(point.getX() == copy2.getX());
		CHECK(point.getY() == copy2.getY());

		// Move assignment
		LibMath::Point2D moved2 = LibMath::Point2D{ 3.0f, 4.0f };
		CHECK(moved2.getX() == 3.0f);
		CHECK(moved2.getY() == 4.0f);
	}

	SECTION("Functionality")
	{
		// Test distance and distanceSquare methods
		LibMath::Point2D point(3.0f, 4.0f);
		LibMath::Point2D origin;

		CHECK(point.distance(origin) == Catch::Approx(5.0f));
		CHECK(point.distanceSquare(origin) == Catch::Approx(25.0f));
	}
}


TEST_CASE("Line2D", "[.all][geometry][line2d]")
{
	SECTION("Instantiation")
	{

		{
			[[maybe_unused]] LibMath::Line2D temp;
		}

		// Default constructor
		LibMath::Line2D empty;
		CHECK(empty.getStart().getX() == 0.0f);
		CHECK(empty.getStart().getY() == 0.0f);
		CHECK(empty.getEnd().getX() == 0.0f);
		CHECK(empty.getEnd().getY() == 0.0f);

		// Parameterized constructor
		LibMath::Point2D start(1.0f, 2.0f);
		LibMath::Point2D end(3.0f, 4.0f);
		LibMath::Line2D line(start, end);
		CHECK(line.getStart().getX() == 1.0f);
		CHECK(line.getStart().getY() == 2.0f);
		CHECK(line.getEnd().getX() == 3.0f);
		CHECK(line.getEnd().getY() == 4.0f);

	}

	SECTION("Functionality")
	{
		LibMath::Point2D start(0.0f, 0.0f);
		LibMath::Point2D end(3.0f, 4.0f);
		LibMath::Line2D line(start, end);

		CHECK(line.length() == Catch::Approx(5.0f));
		CHECK(line.lengthSquare() == Catch::Approx(25.0f));

		CHECK(line.slope() == Catch::Approx(4.0f / 3.0f));
		CHECK(line.slopeIntercept() == Catch::Approx(0.0f));


		// TEST POINT-LINE COLLISIONS

		LibMath::Point2D startLine(0.f, 0.f);
		LibMath::Point2D endLine(4.f, 4.f);
		LibMath::Line2D line1(startLine, endLine);

		LibMath::Point2D pointOnLine(2.f, 2.f);  // on the line
		CHECK(colisionPointLine(pointOnLine, line1));

		// test start and end point of the line
		CHECK(colisionPointLine(startLine, line1));
		CHECK(colisionPointLine(endLine, line1));

		LibMath::Point2D pointOffLine(3.f, 2.f);  // not on the line
		CHECK_FALSE(colisionPointLine(pointOffLine, line1));

		// TEST LINE-LINE COLLISIONS

		LibMath::Point2D startLine2(2.f, 0.f);
		LibMath::Point2D endLine2(2.f, 4.f);
		LibMath::Line2D line2(startLine2, endLine2);

		CHECK(colisionTwoLine(line1, line2));	// collision

		// parallel lines
		LibMath::Point2D startLine4(0.f, 1.f);
		LibMath::Point2D endLine4(4.f, 5.f); 
		LibMath::Line2D line4(startLine4, endLine4);

		CHECK_FALSE(colisionTwoLine(line1, line4));  // No collision

		// identical
		CHECK(colisionTwoLine(line1, line1));	// collision

		// check for colinear line not overlapping (AKA one after the other)
		LibMath::Point2D startLine6(-1.f, -1.f);
		LibMath::Point2D endLine6(-4.f, -4.f);
		LibMath::Line2D line6(startLine6, endLine6);

		CHECK_FALSE(colisionTwoLine(line1, line6));	// No collision
	}
}

TEST_CASE("Rectangle", "[.all][geometry][rectangle]")
{
	SECTION("Instantiation")
	{

		{
			[[maybe_unused]] LibMath::Rectangle tempRectangle;
		}

		// Default constructor
		LibMath::Rectangle rectangleDefault;
		CHECK(rectangleDefault.getWidth() == 0.f);
		CHECK(rectangleDefault.getHeight() == 0.f);
		CHECK(rectangleDefault.getRotation().raw() == 0.f);
		CHECK(rectangleDefault.getCenter().getX() == 0.f);
		CHECK(rectangleDefault.getCenter().getY() == 0.f);

		// Parameterized constructor without rotation
		LibMath::Point2D center(2.0f, 3.0f);
		float width = 4.0f;
		float height = 5.0f;

		LibMath::Rectangle rectangle(center, width, height);
		CHECK(rectangle.getWidth() == 4.0f);
		CHECK(rectangle.getHeight() == 5.0f);
		CHECK(rectangle.getRotation().raw() == 0.f);
		CHECK(rectangle.getCenter().getX() == 2.0f);
		CHECK(rectangle.getCenter().getY() == 3.0f);

		// Parameterized constructor with rotation
		LibMath::Radian rotation(1.2f);
		LibMath::Rectangle rotatedRectangle(center, width, height, rotation);
		CHECK(rotatedRectangle.getWidth() == 4.0f);
		CHECK(rotatedRectangle.getHeight() == 5.0f);
		CHECK(rotatedRectangle.getRotation().raw() == 1.2f);
		CHECK(rotatedRectangle.getCenter().getX() == 2.0f);
		CHECK(rotatedRectangle.getCenter().getY() == 3.0f);
	}

	SECTION("Functionality")
	{
		// Get corners (assuming a non-rotated rectangle)
		LibMath::Point2D center(0.0f, 0.0f);
		float width = 2.0f;
		float height = 4.0f;
		LibMath::Rectangle rectangle(center, width, height);

		LibMath::Point2D corners[4];
		rectangle.getCorners(corners);

		// Check that the corners are positioned correctly based on center, width, and height
		CHECK(corners[0].getX() == -1.0f); // Left, bottom corner
		CHECK(corners[0].getY() == -2.0f);

		CHECK(corners[1].getX() == 1.0f);  // Right, bottom corner
		CHECK(corners[1].getY() == -2.0f);

		CHECK(corners[2].getX() == 1.0f);  // Right, top corner
		CHECK(corners[2].getY() == 2.0f);

		CHECK(corners[3].getX() == -1.0f); // Left, top corner
		CHECK(corners[3].getY() == 2.0f);

		// TEST RECTANGLE-RECTANGLE COLLSION 

		// AABB

		LibMath::Point2D center1(0.f, 0.f);        
		float width1 = 4.f;
		float height1 = 6.f;
		LibMath::Rectangle rect(center1, width1, height1);

		// twice the same
		CHECK(colisionTwoRectangle(rect, rect));

		LibMath::Point2D center2(42.f, 314.f);       
		float width2 = 4.f;
		float height2 = 6.f;
		LibMath::Rectangle rect2(center2, width2, height2);

		CHECK_FALSE(colisionTwoRectangle(rect, rect2));

		// share a side
		LibMath::Point2D center3(0.f, 6.f);
		float width3 = 4.f;
		float height3 = 6.f;
		LibMath::Rectangle rect3(center3, width3, height3);

		CHECK(colisionTwoRectangle(rect, rect3));
		
		// share a corner
		LibMath::Point2D center4(4.f, 6.f);
		float width4 = 4.f;
		float height4 = 6.f;
		LibMath::Rectangle rect4(center4, width4, height4);

		CHECK(colisionTwoRectangle(rect, rect4));

		//one inside another
		LibMath::Point2D center5(0.f, 0.f);
		float width5 = 2.f;
		float height5 = 3.f;
		LibMath::Rectangle rect5(center5, width5, height5);

		CHECK(colisionTwoRectangle(rect, rect5));

		// OBB

		LibMath::Point2D center6(0.f, 0.f);
		float width6 = 4.f;
		float height6 = 4.f;
		LibMath::Radian rotation(1.2f);
		LibMath::Rectangle rect6(center6, width6, height6, rotation);

		CHECK(colisionTwoRectangle(rect6, rect6));

		LibMath::Point2D center7(3.f, 0.f);
		float width7 = 4.f;
		float height7 = 4.f;
		LibMath::Rectangle rect7(center7, width7, height7, -rotation);

		CHECK(colisionTwoRectangle(rect6, rect7));

		LibMath::Point2D center8(3.f, 14.f);
		float width8 = 5.f;
		float height8 = 1.f;
		LibMath::Rectangle rect8(center8, width8, height8, rotation);

		CHECK_FALSE(colisionTwoRectangle(rect6, rect8));


		// TEST LINE-RECTANGLE COLLSION 


		// go through the rectangle
		LibMath::Line2D line(LibMath::Point2D(-3.f, -3.f), LibMath::Point2D(3.f, 3.f));

		CHECK(colisionLineRectangle(line, rect));


		// touches the side of the rectangle
		LibMath::Line2D line2(LibMath::Point2D(-3.f, 0.f), LibMath::Point2D(3.f, 0.f));

		CHECK(colisionLineRectangle(line2, rect));


		// dont touches the rectangle
		LibMath::Line2D line3(LibMath::Point2D(3.f, 14.f), LibMath::Point2D(42.f, 42.f));

		CHECK_FALSE(colisionLineRectangle(line3, rect));


		// TEST POINT-RECTANGLE COLLSION 


		// point inside
		LibMath::Point2D point(0.f, 0.f);

		CHECK(colisionPointRectangle(point, rect));


		// point on the edge
		LibMath::Point2D point2(2.f, 3.f);

		CHECK(colisionPointRectangle(point2, rect));


		// point outside
		LibMath::Point2D point3(42.f, 314.f);

		CHECK_FALSE(colisionPointRectangle(point3, rect));
	}
}

TEST_CASE("Circle", "[.all][geometry][circle]")
{
	SECTION("Instantiation")
	{

		{
			[[maybe_unused]] LibMath::Circle tempCircle;
		}

		// Default constructor
		LibMath::Circle circleDefault;
		CHECK(circleDefault.getRadius() == 0.f);
		CHECK(circleDefault.getCenter().getX() == 0.f);
		CHECK(circleDefault.getCenter().getY() == 0.f);

		// Parameterized constructor
		LibMath::Point2D center(3.0f, 4.0f);
		float radius = 5.0f;
		LibMath::Circle circle(center, radius);
		CHECK(circle.getRadius() == 5.0f);
		CHECK(circle.getCenter().getX() == 3.0f);
		CHECK(circle.getCenter().getY() == 4.0f);
	}

	SECTION("Functionality")
	{
		// TEST POINT-CIRCLE COLLSION
		LibMath::Point2D center(0.f, 0.f);
		float radius = 5.f;

		LibMath::Circle circle(center, radius);

		// Point inside the circle
		LibMath::Point2D point1(3.f, 3.f);
		CHECK(colisionPointCircle(point1, circle));

		// Point on the edge of the circle
		LibMath::Point2D point2(5.f, 0.f);
		CHECK(colisionPointCircle(point2, circle));

		// Point outside the circle
		LibMath::Point2D point3(31.f, 41.f);
		CHECK_FALSE(colisionPointCircle(point3, circle));

		// TEST CIRCLE-CIRCLE COLLSION

		// inside the other circle
		LibMath::Point2D center2(1.f, 1.f);
		float radius2 = 3.f;
		LibMath::Circle circle2(center2, radius2);

		CHECK(colisionTwoCircle(circle, circle2));

		// touches the other circle
		LibMath::Point2D center3(0.f, 7.f);
		float radius3 = 3.f;
		LibMath::Circle circle3(center3, radius3);
		CHECK(colisionTwoCircle(circle, circle3));


		// touches the other circle on the edges
		LibMath::Point2D center4(0.f, 8.f);
		float radius4 = 3.f;
		LibMath::Circle circle4(center4, radius4);
		CHECK(colisionTwoCircle(circle, circle4));

		// no collision
		LibMath::Point2D center5(42.f, 42.f);
		float radius5 = 1.f;
		LibMath::Circle circle5(center5, radius5);
		CHECK_FALSE(colisionTwoCircle(circle, circle5));

		// TEST LINE-CIRCLE COLLSION

		// line go through the circle
		LibMath::Point2D start1(-7.f, -1.f);
		LibMath::Point2D end1(8.f, 1.f);
		LibMath::Line2D line1(start1, end1);
		CHECK(colisionLineCircle(line1, circle));

		// line inside the circle
		LibMath::Point2D start2(-1.f, -1.f);
		LibMath::Point2D end2(3.f, 2.f);
		LibMath::Line2D line2(start2, end2);
		CHECK(colisionLineCircle(line2, circle));

		// line start inside the circle and end outside
		LibMath::Point2D start3(-1.f, -1.f);
		LibMath::Point2D end3(8.f, 2.f);
		LibMath::Line2D line3(start3, end3);
		CHECK(colisionLineCircle(line3, circle));

		// line start on the edge of the circle and go outside
		LibMath::Point2D start4(5.f, 0.f);
		LibMath::Point2D end4(8.f, 412.f);
		LibMath::Line2D line4(start4, end4);
		CHECK(colisionLineCircle(line4, circle));

		// line out of the circle => no collision
		LibMath::Point2D start5(50.f, 0.f);
		LibMath::Point2D end5(8.f, 412.f);
		LibMath::Line2D line5(start5, end5);
		CHECK_FALSE(colisionLineCircle(line5, circle));

		// line touches the circle on one point
		LibMath::Point2D start6(5.f, -12.f);
		LibMath::Point2D end6(5.f, 12.f);
		LibMath::Line2D line6(start6, end6);
		CHECK(colisionLineCircle(line6, circle));
	}
}


// 3D object tests
TEST_CASE("Point3D", "[.all][geometry3D][point3d]")
{
	SECTION("Instantiation")
	{
		LibMath::Point3D defaultPt;
		CHECK(defaultPt.getX() == 0.0f);
		CHECK(defaultPt.getY() == 0.0f);
		CHECK(defaultPt.getZ() == 0.0f);

		LibMath::Point3D p1(1.0f, 2.0f, 3.0f);
		CHECK(p1.getX() == 1.0f);
		CHECK(p1.getY() == 2.0f);
		CHECK(p1.getZ() == 3.0f);

		LibMath::Point3D copy(p1);
		CHECK(copy.getX() == 1.0f);
		CHECK(copy.getY() == 2.0f);
		CHECK(copy.getZ() == 3.0f);

		LibMath::Point3D moved(std::move(p1));
		CHECK(moved.getX() == 1.0f);
		CHECK(moved.getY() == 2.0f);
		CHECK(moved.getZ() == 3.0f);
	}
}

TEST_CASE("Line3D", "[.all][geometry3D][line3d]")
{
	SECTION("Instantiation")
	{
		LibMath::Point3D origin(0.0f, 0.0f, 0.0f);
		LibMath::Vector3 dir(1.0f, 0.0f, 0.0f);
		LibMath::Line3D l(origin, dir);

		CHECK(l.getCenter().getX() == 0.0f);
		CHECK(l.getCenter().getY() == 0.0f);
		CHECK(l.getCenter().getZ() == 0.0f);
		CHECK(l.getDirection() == dir);
	}
}

TEST_CASE("Plane", "[.all][geometry3D][plane]")
{
	SECTION("Instantiation")
	{
		LibMath::Vector3 normal(0.0f, 1.0f, 0.0f);
		float dist = 5.0f;
		LibMath::Plane plane(normal, dist);

		CHECK(plane.getNormal() == normal);
		CHECK(plane.getDistance() == 5.0f);
	}
}

TEST_CASE("Prism", "[.all][geometry3D][prism]")
{
	SECTION("Instantiation")
	{
		LibMath::Point3D center(0.0f, 0.0f, 0.0f);
		float w = 4.0f, h = 6.0f, d = 2.0f;
		LibMath::Matrix3x3 rot;

		LibMath::Prism p(center, w, h, d, rot);

		CHECK(p.getCenter().getX() == 0.0f);
		CHECK(p.getCenter().getY() == 0.0f);
		CHECK(p.getCenter().getZ() == 0.0f);
		CHECK(p.getWidth() == w);
		CHECK(p.getHeight() == h);
		CHECK(p.getDepth() == d);
		CHECK(p.extentX() == w / 2.0f);
		CHECK(p.extentY() == h / 2.0f);
		CHECK(p.extentZ() == d / 2.0f);
	}
}

TEST_CASE("Sphere", "[.all][geometry3D][sphere]")
{
	SECTION("Instantiation")
	{
		LibMath::Point3D center(0.0f, 0.0f, 0.0f);
		float radius = 3.5f;
		LibMath::Sphere s(center, radius);

		CHECK(s.getCenter().getX() == 0.0f);
		CHECK(s.getCenter().getY() == 0.0f);
		CHECK(s.getCenter().getZ() == 0.0f);
		CHECK(s.getRadius() == 3.5f);

		LibMath::Sphere copy(s);
		CHECK(copy.getCenter().getX() == 0.0f);
		CHECK(copy.getCenter().getY() == 0.0f);
		CHECK(copy.getCenter().getZ() == 0.0f);
		CHECK(copy.getRadius() == 3.5f);
	}
}

TEST_CASE("Capsule", "[.all][geometry3D][capsule]")
{
	SECTION("Instantiation")
	{
		LibMath::Point3D a(1.0f, 0.0f, 0.0f);
		LibMath::Point3D b(0.0f, 1.0f, 0.0f);
		float r = 2.0f;

		LibMath::Capsule c(a, b, r);
		CHECK(c.getStart().getX() == 1.0f);
		CHECK(c.getStart().getY() == .0f);
		CHECK(c.getStart().getZ() == .0f);
		CHECK(c.getEnd().getX() == .0f);
		CHECK(c.getEnd().getY() == 1.0f);
		CHECK(c.getEnd().getZ() == .0f);
		CHECK(c.getRadius() == 2.0f);

		LibMath::Capsule copy(c);
		CHECK(copy.getStart().getX() == 1.0f);
		CHECK(copy.getStart().getY() == .0f);
		CHECK(copy.getStart().getZ() == .0f);
		CHECK(copy.getEnd().getX() == .0f);
		CHECK(copy.getEnd().getY() == 1.0f);
		CHECK(copy.getEnd().getZ() == .0f);
		CHECK(copy.getRadius() == 2.0f);
	}
}



// 3D collisions tests
TEST_CASE("Collision3D", "[.all][collision][point][sphere]")
{
	SECTION("Functionality")
	{
		LibMath::Point3D point(0.0f, 0.0f, 0.0f);
		LibMath::Sphere sphere(LibMath::Point3D(0.0f, 0.0f, 0.0f), 5.0f);

		CHECK(LibMath::collisionPointSphere(point, sphere));

		LibMath::Point3D point2(10.0f, 0.0f, 0.0f);
		LibMath::Sphere sphere2(LibMath::Point3D(0.0f, 0.0f, 0.0f), 5.0f);

		CHECK_FALSE(LibMath::collisionPointSphere(point2, sphere2));
	}
}

TEST_CASE("Collision3D", "[.all][collision][ray][sphere]")
{
	SECTION("Functionality")
	{
		LibMath::Line3D ray(LibMath::Point3D(0.0f, 0.0f, -10.0f), LibMath::Vector3(0.0f, 0.0f, 1.0f));
		LibMath::Sphere sphere(LibMath::Point3D(0.0f, 0.0f, 0.0f), 5.0f);

		CHECK(LibMath::collisionRaySphere(ray, sphere));

		LibMath::Line3D ray2(LibMath::Point3D(10.0f, 0.0f, -10.0f), LibMath::Vector3(0.0f, 0.0f, 1.0f));
		LibMath::Sphere sphere2(LibMath::Point3D(0.0f, 0.0f, 0.0f), 5.0f);

		CHECK_FALSE(LibMath::collisionRaySphere(ray2, sphere2));
	}
}

TEST_CASE("Collision3D", "[.all][collision][sphere]")
{
	SECTION("Functionality")
	{
		LibMath::Sphere s1(LibMath::Point3D(0.0f, 0.0f, 0.0f), 3.0f);
		LibMath::Sphere s2(LibMath::Point3D(5.0f, 0.0f, 0.0f), 3.0f);
		LibMath::Sphere s3(LibMath::Point3D(10.0f, 0.0f, 0.0f), 2.0f);

		CHECK(LibMath::collisionTwoSphere(s1, s2));
		CHECK_FALSE(LibMath::collisionTwoSphere(s1, s3));
	}
}

TEST_CASE("Collision3D", "[.all][collision][plane][sphere]")
{
	SECTION("Functionality")
	{
		LibMath::Plane plane(LibMath::Vector3(0.0f, 1.0f, 0.0f), 0.0f);
		LibMath::Sphere sphere(LibMath::Point3D(0.0f, 2.0f, 0.0f), 3.0f);

		CHECK(LibMath::collisionPlaneSphere(plane, sphere));

		LibMath::Sphere sphere2(LibMath::Point3D(0.0f, 5.0f, 0.0f), 3.0f);

		CHECK_FALSE(LibMath::collisionPlaneSphere(plane, sphere2));
	}
}



TEST_CASE("Collision3D", "[.all][collision][point][capsule]")
{
	SECTION("Functionality")
	{
		LibMath::Point3D point(0.0f, 1.0f, 0.0f);
		LibMath::Capsule capsule(LibMath::Point3D(0.0f, 0.0f, 0.0f), LibMath::Point3D(0.0f, 5.0f, 0.0f), 1.0f);

		CHECK(LibMath::collisionPointCapsule(point, capsule));

		LibMath::Point3D point2(0.0f, 7.0f, 0.0f);

		CHECK_FALSE(LibMath::collisionPointCapsule(point2, capsule));
	}
}

TEST_CASE("Collision3D", "[.all][collision][ray][capsule]")
{
	SECTION("Functionality")
	{
		LibMath::Line3D ray(LibMath::Point3D(0.0f, 1.0f, -5.0f), LibMath::Vector3(0.0f, 0.0f, 1.0f));
		LibMath::Capsule capsule(LibMath::Point3D(0.0f, 0.0f, 0.0f), LibMath::Point3D(0.0f, 5.0f, 0.0f), 1.0f);

		CHECK(LibMath::collisionRayCapsule(ray, capsule));

		LibMath::Line3D ray2(LibMath::Point3D(2.0f, 1.0f, -5.0f), LibMath::Vector3(0.0f, 0.0f, 1.0f));

		CHECK_FALSE(LibMath::collisionRayCapsule(ray2, capsule));
	}
}

TEST_CASE("Collision3D", "[.all][collision][plane][capsule]")
{
	SECTION("Functionality")
	{
		LibMath::Plane plane(LibMath::Vector3(0.0f, 1.0f, 0.0f), 0.0f);
		LibMath::Capsule capsule(LibMath::Point3D(0.0f, 1.0f, 0.0f), LibMath::Point3D(0.0f, 4.0f, 0.0f), 1.0f);

		CHECK(LibMath::collisionPlaneCapsule(plane, capsule));

		LibMath::Capsule capsule2(LibMath::Point3D(0.0f, 5.0f, 0.0f), LibMath::Point3D(0.0f, 10.0f, 0.0f), 1.0f);

		CHECK_FALSE(LibMath::collisionPlaneCapsule(plane, capsule2));
	}
}

TEST_CASE("Collision3D", "[.all][collision][sphere][capsule]")
{
	SECTION("Functionality")
	{
		LibMath::Sphere sphere(LibMath::Point3D(0.0f, 1.0f, 0.0f), 1.0f);
		LibMath::Capsule capsule(LibMath::Point3D(0.0f, 0.0f, 0.0f), LibMath::Point3D(0.0f, 3.0f, 0.0f), 1.0f);

		CHECK(LibMath::collisionSphereCapsule(sphere, capsule));

		LibMath::Sphere sphere2(LibMath::Point3D(0.0f, 10.0f, 0.0f), 1.0f);

		CHECK_FALSE(LibMath::collisionSphereCapsule(sphere2, capsule));
	}
}

TEST_CASE("Collision3D", "[.all][collision][capsule]")
{
	SECTION("Functionality")
	{
		LibMath::Capsule capsule1(LibMath::Point3D(0.0f, 0.0f, 0.0f), LibMath::Point3D(0.0f, 3.0f, 0.0f), 1.0f);
		LibMath::Capsule capsule2(LibMath::Point3D(0.0f, 2.0f, 0.0f), LibMath::Point3D(0.0f, 5.0f, 0.0f), 1.0f);

		CHECK(LibMath::collisionTwoCapsule(capsule1, capsule2));

		LibMath::Capsule capsule3(LibMath::Point3D(0.0f, 10.0f, 0.0f), LibMath::Point3D(0.0f, 15.0f, 0.0f), 1.0f);

		CHECK_FALSE(LibMath::collisionTwoCapsule(capsule1, capsule3));
	}
}



TEST_CASE("Collision3D", "[.all][collision][line][plane]")
{
	SECTION("Functionality")
	{
		LibMath::Line3D line(LibMath::Point3D(0.0f, -1.0f, 0.0f), LibMath::Vector3(0.0f, 1.0f, 0.0f));
		LibMath::Plane plane(LibMath::Vector3(0.0f, 1.0f, 0.0f), 0.0f);

		CHECK(LibMath::collisionLinePlane(line, plane));

		LibMath::Line3D line2(LibMath::Point3D(0.0f, 1.0f, 0.0f), LibMath::Vector3(1.0f, 0.0f, 0.0f));
		LibMath::Plane plane2(LibMath::Vector3(0.0f, 1.0f, 0.0f), 0.0f);

		CHECK_FALSE(LibMath::collisionLinePlane(line2, plane2));
	}
}

TEST_CASE("Collision3D", "[.all][collision][plane]")
{
	SECTION("Functionality")
	{
		LibMath::Plane plane1(LibMath::Vector3(0.0f, 1.0f, 0.0f), 1.0f);
		LibMath::Plane plane2(LibMath::Vector3(0.0f, 1.0f, 0.0f), 0.0f);

		CHECK_FALSE(LibMath::collisionTwoPlane(plane1, plane2));

		LibMath::Plane plane3(LibMath::Vector3(0.0f, 1.0f, 0.0f), 5.0f);
		LibMath::Plane plane4(LibMath::Vector3(1.0f, 0.0f, 0.0f), 0.0f);

		CHECK(LibMath::collisionTwoPlane(plane3, plane4));
	}
}



TEST_CASE("Collision3D", "[.all][collision][point][prism]")
{
	SECTION("Functionality")
	{
		LibMath::Prism prism(LibMath::Point3D(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, 10.0f);
		LibMath::Point3D point(0.0f, 0.0f, 0.0f);

		CHECK(LibMath::collisionPointPrism(point, prism));

		LibMath::Point3D point2(20.0f, 20.0f, 20.0f);

		CHECK_FALSE(LibMath::collisionPointPrism(point2, prism));
	}
}

TEST_CASE("Collision3D", "[.all][collision][ray][prism]")
{
	SECTION("Functionality")
	{
		LibMath::Prism prism(LibMath::Point3D(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, 10.0f);
		LibMath::Line3D ray(LibMath::Point3D(0.0f, 0.0f, -20.0f), LibMath::Vector3(0.0f, 0.0f, 1.0f));

		CHECK(LibMath::collisionRayPrism(ray, prism));

		LibMath::Line3D ray2(LibMath::Point3D(20.0f, 20.0f, -20.0f), LibMath::Vector3(0.0f, 0.0f, 1.0f));

		CHECK_FALSE(LibMath::collisionRayPrism(ray2, prism));
	}
}
