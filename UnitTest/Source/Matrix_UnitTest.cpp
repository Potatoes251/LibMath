#include <LibMath/Matrix/Matrix2.h>
#include <LibMath/Matrix/Matrix3.h>
#include <LibMath/Trigonometry.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

TEST_CASE("Matrix2", "[.all][matrix][matrix2]")
{
	SECTION("Instantiation")
	{
		{
			[[maybe_unused]] LibMath::Matrix2x2 temp;
		}

		LibMath::Matrix2x2 empty;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				CHECK(empty[i][j] == 0);
			}
		}

		LibMath::Matrix2x2 diagonal(5);
		LibMath::Matrix2x2 components(
			5, 0,
			0, 5);

		CHECK(diagonal == components);

		LibMath::Matrix2x2 copy = components;

		CHECK(copy == components);

		LibMath::Matrix2x2 identity;
		identity.identity();
		LibMath::Matrix2x2 diagonals(1);

		CHECK(identity == diagonals);
	}

	SECTION("Arithmetic")
	{
		LibMath::Matrix2x2 matrix1(
			3, 1,
			1, 5);

		LibMath::Matrix2x2 matrix2(
			3, 5,
			9, 7);

		{// sum
			LibMath::Matrix2x2 sum = matrix1 + matrix2;
			LibMath::Matrix2x2 expectedSum(
				6, 6,
				10, 12);

			CHECK(sum == expectedSum);
		}
		
		{// matrix product
			LibMath::Matrix2x2 product = matrix1 * matrix2;
			LibMath::Matrix2x2 expectedProduct(
				18, 22,
				48, 40);

			CHECK(product == expectedProduct);
		}

		{// matrix vector product
			LibMath::Vector2 vector(2, 1);
			LibMath::Vector2 product = matrix1 * vector;
			LibMath::Vector2 expectedProduct(7, 7);

			CHECK(product == expectedProduct);
		}
		
		{// matrix float product
			LibMath::Matrix2x2 floatProduct = matrix1 * 2;
			LibMath::Matrix2x2 expectedFloatProduct(
				6, 2,
				2, 10);

			CHECK(floatProduct == expectedFloatProduct);
		}
	}
	SECTION("Transformation")
	{
		{// Rotation
			LibMath::Point2D rotationPoint(0, 0);
			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix2x2 rotation = LibMath::Matrix2x2::createRotation(angle);

			LibMath::Matrix2x2 expected(
				cos(angle), -sin(angle),
				sin(angle), cos(angle));

			CHECK(rotation == expected);
		}

		{// Scale
			LibMath::Vector2 scaleVec(4, 2);
			LibMath::Matrix2x2 scale;
			scale.createScale(scaleVec);

			LibMath::Matrix2x2 expectedMatrix(
				4, 0,
				0, 2
			);

			CHECK(scale == expectedMatrix);
		}

		{// Transform
			LibMath::Radian angle(g_Pi / 4);
			LibMath::Vector2 scale(4.0f, 2.0f);

			LibMath::Matrix2x2 transformMatrix = LibMath::Matrix2x2::createTransform(angle, scale);

			LibMath::Matrix2x2 expectedMatrix;
			expectedMatrix[0][0] = scale[0] * cos(angle);
			expectedMatrix[0][1] = scale[1] * -sin(angle);
			expectedMatrix[1][0] = scale[0] * sin(angle);
			expectedMatrix[1][1] = scale[1] * cos(angle);

			CHECK(transformMatrix == expectedMatrix);
		}
	}
}

TEST_CASE("Matrix3", "[.all][matrix][matrix3]")
{
	SECTION("Instantiation")
	{
		{
			[[maybe_unused]] LibMath::Matrix3x3 temp;
		}

		LibMath::Matrix3x3 empty;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				CHECK(empty[i][j] == 0);
			}
		}

		LibMath::Matrix3x3 diagonal(5);
		LibMath::Matrix3x3 components(
			5, 0, 0,
			0, 5, 0,
			0, 0, 5);

		CHECK(diagonal == components);

		LibMath::Matrix3x3 copy = components;

		CHECK(copy == components);

		LibMath::Matrix3x3 identity;
		identity.identity();
		LibMath::Matrix3x3 diagonals(1);

		CHECK(identity == diagonals);
	}

	SECTION("Arithmetic")
	{
		LibMath::Matrix3x3 matrix1(
			3, 1, 4,
			1, 5, 9,
			2, 6, 5);

		LibMath::Matrix3x3 matrix2(
			3, 5, 8,
			9, 7, 9,
			3, 2, 3);

		{// sum
			LibMath::Matrix3x3 sum = matrix1 + matrix2;
			LibMath::Matrix3x3 expectedSum(
				6, 6, 12,
				10, 12, 18,
				5, 8, 8);

			CHECK(sum == expectedSum);
		}
		
		{// matrix product
			LibMath::Matrix3x3 product = matrix1 * matrix2;
			LibMath::Matrix3x3 expectedProduct(
				30, 30, 45,
				75, 58, 80,
				75, 62, 85);

			CHECK(product == expectedProduct);
		}
		
		{// matrix float product
			LibMath::Matrix3x3 floatProduct = matrix1 * 2;
			LibMath::Matrix3x3 expectedFloatProduct(
				6, 2, 8,
				2, 10, 18,
				4, 12, 10);

			CHECK(floatProduct == expectedFloatProduct);
		}
	}


	SECTION("Transformation")
	{

		{// translation
			LibMath::Vector2 translationVec(4, 2);
			LibMath::Matrix3x3 translationMatrix = LibMath::Matrix3x3::createTranslation(translationVec);

			// Expected translation matrix
			LibMath::Matrix3x3 expectedMatrix(
				1, 0, 4,
				0, 1, 2,
				0, 0, 1);

			CHECK(translationMatrix == expectedMatrix);
		}

		{// rotation

			LibMath::Point2D rotationPoint(0, 0);
			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix3x3 rotation = LibMath::Matrix3x3::createRotation(rotationPoint, angle);

			LibMath::Matrix3x3 expected(
				0, -1, 0,
				1, 0, 0,
				0, 0, 1
			);

			CHECK(rotation == expected);
		}

		{// scale

			LibMath::Vector2 scaleVec(4, 2);
			LibMath::Matrix3x3 scale;
			scale.createScale(scaleVec);

			// Expected rotation matrix for 90 degrees
			LibMath::Matrix3x3 expectedMatrix(
				4, 0, 0,
				0, 2, 0,
				0, 0, 1
			);

			CHECK(scale == expectedMatrix);
		}

		{// transform
			LibMath::Vector2 translation(3.14f, 3.14f);
			LibMath::Radian angle(g_Pi / 4);
			LibMath::Vector2 scale(4.0f, 2.0f);

			LibMath::Matrix3x3 transformMatrix = LibMath::Matrix3x3::createTransform(translation, angle, scale);

			LibMath::Matrix3x3 expectedMatrix;
			expectedMatrix[0][0] = scale[0] * cos(angle);
			expectedMatrix[0][1] = scale[1] * -sin(angle);
			expectedMatrix[0][2] = translation[0];
			expectedMatrix[1][0] = scale[0] * sin(angle);
			expectedMatrix[1][1] = scale[1] * cos(angle);
			expectedMatrix[1][2] = translation[1];
			expectedMatrix[2][0] = 0;
			expectedMatrix[2][1] = 0;
			expectedMatrix[2][2] = 1;

			CHECK(transformMatrix == expectedMatrix);
		}
	}
}