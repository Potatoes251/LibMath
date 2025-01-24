#include <LibMath/Colision.h>
#include <LibMath/Geometry.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

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
		CHECK(rectangleDefault.getRotation() == 0.f);
		CHECK(rectangleDefault.getCenter().getX() == 0.f);
		CHECK(rectangleDefault.getCenter().getY() == 0.f);

		// Parameterized constructor without rotation
		LibMath::Point2D center(2.0f, 3.0f);
		float width = 4.0f;
		float height = 5.0f;

		LibMath::Rectangle rectangle(center, width, height);
		CHECK(rectangle.getWidth() == 4.0f);
		CHECK(rectangle.getHeight() == 5.0f);
		CHECK(rectangle.getRotation() == 0.f);
		CHECK(rectangle.getCenter().getX() == 2.0f);
		CHECK(rectangle.getCenter().getY() == 3.0f);

		// Parameterized constructor with rotation
		float rotation = 45.0f;
		LibMath::Rectangle rotatedRectangle(center, width, height, rotation);
		CHECK(rotatedRectangle.getWidth() == 4.0f);
		CHECK(rotatedRectangle.getHeight() == 5.0f);
		CHECK(rotatedRectangle.getRotation() == 45.0f);
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
		// Functionality test: check radius and center position
		LibMath::Point2D center(1.0f, 1.0f);
		float radius = 10.0f;
		LibMath::Circle circle(center, radius);

		CHECK(circle.getRadius() == 10.0f);
		CHECK(circle.getCenter().getX() == 1.0f);
		CHECK(circle.getCenter().getY() == 1.0f);
	}
}
