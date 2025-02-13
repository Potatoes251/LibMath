#include <LibMath/Matrix.h>
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

	SECTION("Functionality")
	{
		{// transpose
			LibMath::Matrix2x2 matrix(
				2, 8,
				0, 6);
			matrix.transpose();
			LibMath::Matrix2x2 transposedMatrix(
				2, 0,
				8, 6);

			CHECK(transposedMatrix == matrix);
		}

		{// determinant
			LibMath::Matrix2x2 matrix(
				1, 9,
				6, 9);
			float determinant = matrix.determinant();

			CHECK(determinant == -45.f);
		}

		{// minor
			LibMath::Matrix2x2 matrix(
				1, 1,
				0, 9);
			matrix.minors();

			LibMath::Matrix2x2 minorMatrix(
				9, 0,
				1, 1);

			CHECK(minorMatrix == matrix);
		}

		{// cofactor
			LibMath::Matrix2x2 matrix(
				2, 0,
				1, 3);
			matrix.cofactors();

			LibMath::Matrix2x2 cofactorMatrix(
				3, -1,
				0, 2);

			CHECK(cofactorMatrix == matrix);
		}

		{// adjugate
			LibMath::Matrix2x2 matrix(
				0, 7,
				0, 6);
			matrix.adjugate();

			LibMath::Matrix2x2 adjugateMatrix(
				6, -7,
				0, 0);

			CHECK(adjugateMatrix == matrix);
		}

		{// inverse
			LibMath::Matrix2x2 matrix(
				1, 9,
				5, 4);
			matrix.inverse();

			LibMath::Matrix2x2 inverseMatrix(
				-4.0f / 41.0f, 9.0f / 41.0f,
				5.0f / 41.0f, -1.0f / 41.0f);

			CHECK(inverseMatrix == matrix);
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

			// Expected scale matrix
			LibMath::Matrix3x3 expectedMatrix(
				4, 0, 0,
				0, 2, 0,
				0, 0, 1
			);

			CHECK(scale == expectedMatrix);
		}

		{// rotationX

			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix3x3 rotation = LibMath::Matrix3x3::createRotationX(angle);

			LibMath::Matrix3x3 expected(
				1, 0, 0,
				0, 0, -1,
				0, 1, 0
			);

			CHECK(rotation == expected);
		}

		{// rotationY

			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix3x3 rotation = LibMath::Matrix3x3::createRotationY(angle);

			LibMath::Matrix3x3 expected(
				0, 0, 1,
				0, 1, 0,
				-1, 0, 0
			);

			CHECK(rotation == expected);
		}

		{// rotationZ

			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix3x3 rotation = LibMath::Matrix3x3::createRotationZ(angle);

			LibMath::Matrix3x3 expected(
				0, -1, 0,
				1, 0, 0,
				0, 0, 1
			);

			CHECK(rotation == expected);
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

	SECTION("Functionality")
	{
		{// getMinor
			LibMath::Matrix3x3 matrix(
				7, -2, 3,
				0, 5, -1,
				4, 8, 6);
			LibMath::Matrix2x2 minor(
				0, -1,
				4, 6);

			CHECK(minor == matrix.getMinor(0,1));
		}

		{// transpose
			LibMath::Matrix3x3 matrix(
				7, -2, 3,
				0, 5, -1,
				4, 8, 6);
			matrix.transpose();
			LibMath::Matrix3x3 transposedMatrix(
				7, 0, 4,
				-2, 5, 8,
				3, -1, 6);

			CHECK(transposedMatrix == matrix);
		}

		{// determinant
			LibMath::Matrix3x3 matrix(
				7, -2, 3,
				0, 5, -1,
				4, 8, 6);
			float determinant = matrix.determinant();

			CHECK(determinant == 214.f);
		}

		{// minor
			LibMath::Matrix3x3 matrix(
				7, -2, 3,
				0, 5, -1,
				4, 8, 6);
			matrix.minors();

			LibMath::Matrix3x3 minorMatrix(
				38, 4, -20,
				-36, 30, 64,
				-13, -7, 35);
			
			CHECK(minorMatrix == matrix);
		}

		{// cofactor
			LibMath::Matrix3x3 matrix(
				7, -2, 3,
				0, 5, -1,
				4, 8, 6);
			matrix.cofactors();

			LibMath::Matrix3x3 cofactorMatrix(
				38, -4, -20,
				36, 30, -64,
				-13, 7, 35);

			CHECK(cofactorMatrix == matrix);
		}

		{// adjugate
			LibMath::Matrix3x3 matrix(
				7, -2, 3,
				0, 5, -1,
				4, 8, 6);
			matrix.adjugate();

			LibMath::Matrix3x3 adjugateMatrix(
				38, 36, -13,
				-4, 30, 7,
				-20, -64, 35);

			CHECK(adjugateMatrix == matrix);
		}

		{// inverse
			LibMath::Matrix3x3 matrix(
				7, -2, 3,
				0, 5, -1,
				4, 8, 6);
			matrix.inverse();

			LibMath::Matrix3x3 inverseMatrix(
				38.f / 214.f, 36.f / 214.f, -13.f / 214.f,
				-4.f / 214.f, 30.f / 214.f, 7.f / 214.f,
				-20.f / 214.f, -64.f / 214.f, 35.f / 214.f);

			CHECK(inverseMatrix == matrix);
		}
	}
}

TEST_CASE("Matrix4", "[.all][matrix][matrix4]")
{
	SECTION("Instantiation")
	{
		{
			[[maybe_unused]] LibMath::Matrix4 temp;
		}

		LibMath::Matrix4 empty;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				CHECK(empty[i][j] == 0);
			}
		}

		LibMath::Matrix4 diagonal(5);
		LibMath::Matrix4 components(
			5, 0, 0, 0,
			0, 5, 0, 0,
			0, 0, 5, 0,
			0, 0, 0, 5);

		CHECK(diagonal == components);

		LibMath::Matrix4 copy = components;

		CHECK(copy == components);

		LibMath::Matrix4 identity;
		identity.identity();
		LibMath::Matrix4 diagonals(1);

		CHECK(identity == diagonals);
	}

	SECTION("Arithmetic")
	{
		LibMath::Matrix4 matrix1(
			3, 1, 4, 1, 
			5, 9, 2, 6, 
			5, 3, 5, 8,
			9, 7, 9, 3);

		LibMath::Matrix4 matrix2(
			2, 7, 1, 8,
			2, 8, 1, 8,
			2, 8, 4, 5,
			9, 0, 4, 5);


		{// sum
			LibMath::Matrix4 sum = matrix1 + matrix2;
			LibMath::Matrix4 expectedSum(
				5, 8, 5, 9,
				7, 17, 3, 14,
				7, 11, 9, 13,
				18, 7, 13, 8);

			CHECK(sum == expectedSum);
		}

		{// matrix product
			LibMath::Matrix4 product = matrix1 * matrix2;
			LibMath::Matrix4 expectedProduct(
				25, 61, 24, 57,
				86, 123, 46,152,
				98, 99, 60, 129,
				77, 191, 64, 188);

			CHECK(product == expectedProduct);
		}

		{// matrix float product
			LibMath::Matrix4 floatProduct = matrix1 * 2;
			LibMath::Matrix4 expectedFloatProduct(
				6, 2, 8, 2,
				10, 18, 4, 12,
				10, 6, 10, 16,
				18, 14, 18, 6);

			CHECK(floatProduct == expectedFloatProduct);
		}
	}

	SECTION("Transformation")
	{
		{// translation
			LibMath::Vector3 translationVec(4, 2, 3);
			LibMath::Matrix4 translationMatrix = LibMath::Matrix4::createTranslation(translationVec);

			// Expected translation matrix
			LibMath::Matrix4 expectedMatrix(
				1, 0, 0, 4,
				0, 1, 0, 2,
				0, 0, 1, 3,
				0, 0, 0, 1);

			CHECK(translationMatrix == expectedMatrix);
		}

		{// scale

			LibMath::Vector3 scaleVec(4, 2, 3);
			LibMath::Matrix4 scale;
			scale.createScale(scaleVec);

			// Expected scale matrix
			LibMath::Matrix4 expectedMatrix(
				4, 0, 0, 0,
				0, 2, 0, 0,
				0, 0, 3, 0,
				0, 0, 0, 1);

			CHECK(scale == expectedMatrix);
		}

		{// rotation

			LibMath::Vector3 axis(0, 0, 1);
			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix4 rotation = LibMath::Matrix4::createRotation(axis, angle);

			LibMath::Matrix4 expected(
				0, -1, 0, 0,
				1, 0, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			);

			CHECK(rotation == expected);
		}

		{// rotationX

			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix4 rotation = LibMath::Matrix4::createRotationX(angle);

			LibMath::Matrix4 expected(
				1, 0, 0, 0,
				0, 0, -1, 0,
				0, 1, 0, 0,
				0, 0, 0, 1);

			CHECK(rotation == expected);
		}

		{// rotationY

			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix4 rotation = LibMath::Matrix4::createRotationY(angle);

			LibMath::Matrix4 expected(
				0, 0, 1, 0,
				0, 1, 0, 0,
				-1, 0, 0, 0,
				0, 0, 0, 1);

			CHECK(rotation == expected);
		}

		{// rotationZ

			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix4 rotation = LibMath::Matrix4::createRotationZ(angle);

			LibMath::Matrix4 expected(
				0, -1, 0, 0,
				1, 0, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			CHECK(rotation == expected);
		}

		{// transform (translation, rotation, scale)

			LibMath::Vector3 position(1, 2, 3);
			LibMath::Vector3 axis(0, 0, 1);
			LibMath::Radian angle(g_Pi / 2);
			LibMath::Vector3 scale(2, 2, 2);

			LibMath::Matrix4 transform = LibMath::Matrix4::createTransform(position, axis, angle, scale);

			LibMath::Matrix4 expected(
				0, -2, 0, 1,
				2, 0, 0, 2,
				0, 0, 2, 3,
				0, 0, 0, 1
			);

			CHECK(transform == expected);
		}
	}
}