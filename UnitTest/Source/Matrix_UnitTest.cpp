#include <LibMath/Matrix/Matrix2.h>
#include <LibMath/Matrix/Matrix3.h>

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
}