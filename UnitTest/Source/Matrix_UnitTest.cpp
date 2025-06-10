#include <LibMath/Matrix.h>
#include <LibMath/Trigonometry.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/Matrix.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>


#define CHECK_MATRIX2(libMathMat, glmMat) \
    for (int col = 0; col < 2; col++) { \
        for (int row = 0; row < 2; row++) { \
            CHECK(libMathMat[row][col] == Catch::Approx(glmMat[row][col]).margin(1e-6f)); \
        } \
    }

TEST_CASE("Matrix2", "[.all][matrix][matrix2]")
{
	SECTION("Instantiation")
	{
		{
			[[maybe_unused]] LibMath::Matrix2x2 temp;
		}

		LibMath::Matrix2x2 empty;
		glm::mat2 emptyGlm(0);
		CHECK_MATRIX2(empty, emptyGlm);

		LibMath::Matrix2x2 diagonal(5);
		glm::mat2 diagonalGlm(5);
		CHECK_MATRIX2(diagonal, diagonalGlm);

		LibMath::Matrix2x2 components(
			5, 0,
			0, 5);
		glm::mat2 componentsGlm(
			5, 0,
			0, 5);

		CHECK_MATRIX2(components, componentsGlm);

		LibMath::Matrix2x2 copy = components;
		glm::mat2 copyGlm = componentsGlm;

		CHECK_MATRIX2(copy, copyGlm);

		LibMath::Matrix2x2 identity;
		identity.identity();
		glm::mat2 identityGlm = glm::mat2(1.0f);

		CHECK_MATRIX2(identity, identityGlm);

		// OpenGL compatibility
		CHECK(sizeof LibMath::Matrix2x2 == sizeof glm::mat2);
		CHECK(memcmp(&components, &componentsGlm, sizeof components) == 0);
	}

	SECTION("Arithmetic")
	{
		LibMath::Matrix2x2 matA{
				1.0f, 2.0f, 
				3.0f, 4.0f
		};

		glm::mat2 matAGlm{
			{1.0f, 2.0f},
			{3.0f, 4.0f}
 		};

		LibMath::Matrix2x2 matB{
			4.0f, 3.0f, 
			2.0f, 1.0f
		};

		glm::mat2 matBGlm{
			{4.0f, 3.0f},
			{2.0f, 1.0f}
		};

		{// sum
			LibMath::Matrix2x2 sum = matA + matB;
			glm::mat2 resultGlm = matAGlm + matBGlm;

			CHECK_MATRIX2(sum, resultGlm);
		}

		{// matrix product

			LibMath::Matrix2x2 result = matA * matB;
			glm::mat2 resultGlm = matAGlm * matBGlm;

			CHECK_MATRIX2(result, resultGlm);
		}

		{// matrix float product
			LibMath::Matrix2x2 floatProduct = matA * 2.f;
			glm::mat2 resultGlm = matAGlm * 2.f;

			CHECK_MATRIX2(floatProduct, resultGlm);
		}
	}

	SECTION("Transformation")
	{
		{// Rotation
			LibMath::Point2D rotationPoint(0, 0);
			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix2x2 rotation = LibMath::Matrix2x2::createRotation(angle);

			LibMath::Matrix2x2 expected(
				cos(angle), sin(angle),
				-sin(angle), cos(angle));

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
			expectedMatrix[0][1] = scale[1] * sin(angle);
			expectedMatrix[1][0] = scale[0] * -sin(angle);
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



#define CHECK_MATRIX3(libMathMat, glmMat) \
    for (int col = 0; col < 3; col++) { \
        for (int row = 0; row < 3; row++) { \
            CHECK(libMathMat[col][row] == Catch::Approx(glmMat[col][row]).margin(1e-6f)); \
        } \
    }

TEST_CASE("Matrix3", "[.all][matrix][matrix3]")
{
	SECTION("Instantiation")
	{
		{
			[[maybe_unused]] LibMath::Matrix3x3 temp;
		}

		LibMath::Matrix3x3 empty;
		glm::mat3 emptyGlm(0);
		CHECK_MATRIX3(empty, emptyGlm);

		LibMath::Matrix3x3 diagonal(5);
		glm::mat3 diagonalGlm(5);
		CHECK_MATRIX3(diagonal, diagonalGlm);

		LibMath::Matrix3x3 components(
			5, 0, 0,
			0, 5, 0,
			0, 0, 5);
		glm::mat3 componentsGlm(
			5, 0, 0,
			0, 5, 0,
			0, 0, 5);

		CHECK_MATRIX3(components, componentsGlm);

		LibMath::Matrix3x3 copy = components;
		glm::mat3 copyGlm = componentsGlm;

		CHECK_MATRIX3(copy, copyGlm);

		LibMath::Matrix3x3 identity;
		identity.identity();
		glm::mat3 identityGlm = glm::mat3(1.0f);

		CHECK_MATRIX3(identity, identityGlm);

		// OpenGL compatibility
		CHECK(sizeof LibMath::Matrix3x3 == sizeof glm::mat3);
		CHECK(memcmp(&components, &componentsGlm, sizeof components) == 0);
	}

	SECTION("Accessor")
	{
		LibMath::Matrix3x3 mat{
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
		};

		// Const accessor
		{
			CHECK(mat[0][0] == 1.0f);
			CHECK(mat[0][1] == 2.0f);
			CHECK(mat[0][2] == 3.0f);
			CHECK(mat[1][0] == 4.0f);
			CHECK(mat[1][1] == 5.0f);
			CHECK(mat[1][2] == 6.0f);
			CHECK(mat[2][0] == 7.0f);
			CHECK(mat[2][1] == 8.0f);
			CHECK(mat[2][2] == 9.0f);
		}

		// Mutator accessor
		{
			mat[0][0] += 10.0f;
			mat[1][1] += 10.0f;
			mat[2][2] += 10.0f;

			CHECK(mat[0][0] == 11.0f);
			CHECK(mat[1][1] == 15.0f);
			CHECK(mat[2][2] == 19.0f);
		}
	}

	SECTION("Arithmetic")
	{
		LibMath::Matrix3x3 matA{
				1.0f, 2.0f, 3.0f, 
				4.0f, 5.0f, 6.0f, 
				7.0f, 8.0f, 9.0f
		};

		glm::mat3 matAGlm{
			{1.0f, 2.0f, 3.0f},
			{4.0f, 5.0f, 6.0f},
			{7.0f, 8.0f, 9.0f},
		};

		LibMath::Matrix3x3 matB{
			9.0f, 8.0f, 7.0f, 
			6.0f, 5.0f, 4.0f, 
			3.0f, 2.0f, 1.0f
		};

		glm::mat3 matBGlm{
			{9.0f, 8.0f, 7.0f},
			{6.0f, 5.0f,4.0f},
			{3.0f, 2.0f, 1.0f}
		};

		LibMath::Vector3 vec{ 0,1,2 };

		glm::vec3 vecGlm{ 0,1,2 };

		{// sum
			LibMath::Matrix3x3 sum = matA + matB;
			glm::mat3 resultGlm = matAGlm + matBGlm;

			CHECK_MATRIX3(sum, resultGlm);
		}

		{// matrix product

			LibMath::Matrix3x3 result = matA * matB;
			glm::mat3 resultGlm = matAGlm * matBGlm;

			CHECK_MATRIX3(result, resultGlm);
		}

		// matrix-vector product
		{
			LibMath::Vector3 result = matA * vec;
			glm::vec3 resultGlm = matAGlm * vecGlm;

			CHECK(result.m_x == Catch::Approx(resultGlm.x));
			CHECK(result.m_y == Catch::Approx(resultGlm.y));
			CHECK(result.m_z == Catch::Approx(resultGlm.z));
		}

		{// matrix float product
			LibMath::Matrix3x3 floatProduct = matA * 2.f;
			glm::mat3 resultGlm = matAGlm * 2.f;

			CHECK_MATRIX3(floatProduct, resultGlm);
		}
	}

	SECTION("Transformation")
	{

		{// translation
			LibMath::Vector2 translationVec(4, 2);
			LibMath::Matrix3x3 translationMatrix = LibMath::Matrix3x3::createTranslation(translationVec);

			// Expected translation matrix
			LibMath::Matrix3x3 expectedMatrix(
				1, 0, 0,
				0, 1, 0,
				4, 2, 1);

			CHECK(translationMatrix == expectedMatrix);
		}

		{// rotation

			LibMath::Point2D rotationPoint(0, 0);
			LibMath::Radian angle(g_Pi / 2);
			LibMath::Matrix3x3 rotation = LibMath::Matrix3x3::createRotation(rotationPoint, angle);

			LibMath::Matrix3x3 expected(
				0, 1, 0,
				-1, 0, 0,
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
				0, 0, 1,
				0, -1, 0
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
			expectedMatrix[0][0] = scale[0] * cos(angle);    // col 0, row 0
			expectedMatrix[0][1] = scale[0] * sin(angle);   // col 0, row 1
			expectedMatrix[0][2] = 0.0f;                           // col 0, row 2

			expectedMatrix[1][0] = scale[1] * -sin(angle);    // col 1, row 0
			expectedMatrix[1][1] = scale[1] * cos(angle);    // col 1, row 1
			expectedMatrix[1][2] = 0.0f;                           // col 1, row 2

			expectedMatrix[2][0] = translation[0];                 // col 2, row 0
			expectedMatrix[2][1] = translation[1];                 // col 2, row 1
			expectedMatrix[2][2] = 1.0f;                           // col 2, row 2

			CHECK(transformMatrix == expectedMatrix);
		}
	}

	SECTION("Functionality")
	{
		LibMath::Matrix3x3 mat{
				1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f,
				7.0f, 8.0f, 90.0f
		};

		glm::mat3 matGlm{
			{1.0f, 2.0f, 3.0f},
			{4.0f, 5.0f, 6.0f},
			{7.0f, 8.0f, 90.0f},
		};

		{// getMinor
			LibMath::Matrix3x3 matrix(
				7, -2, 3,
				0, 5, -1,
				4, 8, 6);
			LibMath::Matrix2x2 minor(
				0, -1,
				4, 6);

			CHECK(minor == matrix.getMinor(1,0));
		}

		{// transpose
			LibMath::Matrix3x3 transposeMatrix = mat;
			mat.transpose();

			glm::mat3 transposeglm = glm::transpose(matGlm);
			CHECK_MATRIX3(mat, transposeglm);
		}

		{// determinant
			float determinant = mat.determinant();
			float determinantGlm = glm::determinant(matGlm);

			CHECK(determinant == determinantGlm);
		}

		
		{// Minors
			LibMath::Matrix3x3 matCopy = mat;
			matCopy.minors();

			LibMath::Matrix3x3 expectedMinors(
				402.0f, 318.0f, -3.0f,
				156.0f, 69.0f, -6.0f,
				-3.0f, -6.0f, -3.0f
			);

			CHECK(matCopy == expectedMinors);
		}

		{// Cofactors
			LibMath::Matrix3x3 matCopy = mat;
			matCopy.cofactors();

			LibMath::Matrix3x3 expectedCofactors(
				402.0f, -318.0f, -3.0f,
				-156.0f, 69.0f, 6.0f,
				-3.0f, 6.0f, -3.0f
			);

			CHECK(matCopy == expectedCofactors);
		}

		{// adjugate
			LibMath::Matrix3x3 matrix(
				3, 0, 2,
				2, 0, -2,
				0, 1, 1);

			LibMath::Matrix3x3 adjugate = matrix;
			adjugate.adjugate();

			glm::mat3 glmMat(
				{ 3, 0, 2 },
				{ 2, 0, -2 },
				{ 0, 1, 1 });
			glm::mat3 glmAdjugate = glm::transpose(glm::inverse(glmMat) * glm::determinant(glmMat));

			CHECK_MATRIX3(adjugate, glmAdjugate);
		}

		{// inverse
			LibMath::Matrix3x3 inverseMatrix = mat;
			inverseMatrix.inverse();

			glm::mat3 inverseglm = glm::inverse(matGlm);

			CHECK_MATRIX3(inverseMatrix, inverseglm);
		}
	}
}



#define CHECK_MATRIX4(libMathMat, glmMat) \
    for (int col = 0; col < 4; col++) { \
        for (int row = 0; row < 4; row++) { \
            CHECK(libMathMat[col][row] == Catch::Approx(glmMat[col][row]).margin(1e-6f)); \
        } \
    }

TEST_CASE("Matrix4", "[.all][matrix][matrix4]")
{
	SECTION("Instantiation")
	{
		{
			[[maybe_unused]] LibMath::Matrix4 temp;
		}

		LibMath::Matrix4 empty;
		glm::mat4 emptyGlm(0);
		CHECK_MATRIX4(empty, emptyGlm);

		LibMath::Matrix4 diagonal(5);
		glm::mat4 diagonalGlm(5);
		CHECK_MATRIX4(diagonal, diagonalGlm);

		LibMath::Matrix4 components(
			5, 0, 0, 1,
			0, 5, 0, 0,
			0, 0, 5, 0,
			0, 0, 0, 5);
		glm::mat4 componentsGlm(
			5, 0, 0, 1,
			0, 5, 0, 0,
			0, 0, 5, 0,
			0, 0, 0, 5);

		CHECK_MATRIX4(components, componentsGlm);

		LibMath::Matrix4 copy = components;
		glm::mat4 copyGlm = componentsGlm;

		CHECK_MATRIX4(copy, copyGlm);

		LibMath::Matrix4 identity;
		identity.identity();
		glm::mat4 identityGlm = glm::mat4(1.0f);

		CHECK_MATRIX4(identity, identityGlm);

		// OpenGL compatibility
		CHECK(sizeof LibMath::Matrix4 == sizeof glm::mat4);
		CHECK(memcmp(&components, &componentsGlm, sizeof components) == 0);
	}

	SECTION("Arithmetic")
	{
		LibMath::Matrix4 matA{
				1.0f, 2.0f, 3.0f, 4.0f,
				5.0f, 6.0f, 7.0f, 8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
		};

		glm::mat4 matAGlm{
			{1.0f, 2.0f, 3.0f, 4.0f},
			{5.0f, 6.0f, 7.0f, 8.0f},
			{9.0f, 10.0f, 11.0f, 12.0f},
			{13.0f, 14.0f, 15.0f, 16.0f}
		};

		LibMath::Matrix4 matB{
			16.0f, 15.0f, 14.0f, 13.0f,
			12.0f, 11.0f, 10.0f, 9.0f,
			8.0f, 7.0f, 6.0f, 5.0f,
			4.0f, 3.0f, 2.0f, 1.0f
		};

		glm::mat4 matBGlm{
			{16.0f, 15.0f, 14.0f, 13.0f},
			{12.0f, 11.0f, 10.0f, 9.0f},
			{8.0f, 7.0f, 6.0f, 5.0f},
			{4.0f, 3.0f, 2.0f, 1.0f}
		};

		LibMath::Vector4 vec{ 0,1,2,3 };

		glm::vec4 vecGlm{ 0,1,2,3 };

		{// sum
			LibMath::Matrix4 sum = matA + matB;
			glm::mat4 resultGlm = matAGlm + matBGlm;

			CHECK_MATRIX4(sum, resultGlm);
		}

		{// matrix product

			LibMath::Matrix4 result = matA * matB;
			glm::mat4 resultGlm = matAGlm * matBGlm;

			CHECK_MATRIX4(result, resultGlm);
		}

		// matrix-vector product
		{
			LibMath::Vector4 result = matA * vec;
			glm::vec4 resultGlm = matAGlm * vecGlm;

			CHECK(result.m_x == Catch::Approx(resultGlm.x));
			CHECK(result.m_y == Catch::Approx(resultGlm.y));
			CHECK(result.m_z == Catch::Approx(resultGlm.z));
			CHECK(result.m_w == Catch::Approx(resultGlm.w));
		}

		{// matrix float product
			LibMath::Matrix4 floatProduct = matA * 2.f;
			glm::mat4 resultGlm = matAGlm * 2.f;

			CHECK_MATRIX4(floatProduct, resultGlm);
		}
	}

	SECTION("Transformation")
	{
		{// translation
			LibMath::Vector3 translationVec(4.0f, 2.0f, 3.0f);
			LibMath::Matrix4 translationMatrix = LibMath::Matrix4::createTranslation(translationVec);

			glm::vec3 translationVecGlm(4.0f, 2.0f, 3.0f);
			glm::mat4 translationMatrixGlm = glm::translate(glm::mat4(1.0f), translationVecGlm);

			CHECK_MATRIX4(translationMatrix, translationMatrixGlm);
		}

		{// scale

			LibMath::Vector3 scaleVec(4.0f, 2.0f, 3.0f);
			LibMath::Matrix4 scaleMatrix;
			scaleMatrix = scaleMatrix.createScale(scaleVec);

			glm::vec3 scaleVecGlm(4.0f, 2.0f, 3.0f);
			glm::mat4 scaleMatrixGlm = glm::scale(glm::mat4(1.0f), scaleVecGlm);

			CHECK_MATRIX4(scaleMatrix, scaleMatrixGlm);
		}

		{// rotation

			LibMath::Vector3 axis(1.0f, 0.0f, 0.0f);
			LibMath::Radian angle(90.0f);

			LibMath::Matrix4 rotation = LibMath::Matrix4::createRotation(axis, angle);

			glm::vec3 axisGlm(1.0f, 0.0f, 0.0f);
			constexpr float angleGlm = 90.f;

			glm::mat4 rotationGlm = glm::rotate(glm::mat4(1.0f), angleGlm, axisGlm);

			CHECK_MATRIX4(rotation, rotationGlm);
		}

		{// rotationX

			LibMath::Radian angle(g_Pi / 2);

			LibMath::Matrix4 rotation = LibMath::Matrix4::createRotationX(angle);

			glm::mat4 rotationGlm = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			CHECK_MATRIX4(rotation, rotationGlm);
		}

		{// rotationY

			LibMath::Radian angle(g_Pi / 2);

			LibMath::Matrix4 rotation = LibMath::Matrix4::createRotationY(angle);

			glm::mat4 rotationGlm = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(.0f, 1.0f, .0f));

			CHECK_MATRIX4(rotation, rotationGlm);
		}

		{// rotationZ

			LibMath::Radian angle(g_Pi / 2);

			LibMath::Matrix4 rotation = LibMath::Matrix4::createRotationZ(angle);

			glm::mat4 rotationGlm = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(.0f, .0f, 1.0f));

			CHECK_MATRIX4(rotation, rotationGlm);
		}

		{// transform (translation, rotation, scale)

			LibMath::Vector3 position(2.0f, 3.0f, 4.0f);

			LibMath::Vector3 axis(0.0f, 1.0f, 0.0f);
			LibMath::Radian angle(g_Pi / 2);

			LibMath::Vector3 scale(2.0f, 2.0f, 2.0f);

			LibMath::Matrix4 transform = LibMath::Matrix4::createTransform(position, axis, angle, scale);

			glm::mat4 glmTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 3.0f, 4.0f));
			glm::mat4 glmRotate = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 glmScale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));

			glm::mat4 glmTransform = glmTranslate * glmRotate * glmScale;

			CHECK_MATRIX4(transform, glmTransform);
		}
	}

	SECTION("Functionality")
	{
		LibMath::Matrix4 mat{
				10.0f, 2.0f, 3.0f, 45.0f,
				5.0f, 6.0f, 7.0f, 8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 17.0f
		};

		glm::mat4 matGlm{
			10.0f, 2.0f, 3.0f, 45.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 17.0f
		};


		{// transpose
			LibMath::Matrix4 transposeMatrix = mat;
			mat.transpose();

			glm::mat4 transposeglm = glm::transpose(matGlm);
			CHECK_MATRIX4(mat, transposeglm);
		}

		{// determinant
			float determinant = mat.determinant();
			float determinantGlm = glm::determinant(matGlm);
			
			CHECK(determinant == determinantGlm);
		}

		{// inverse
			LibMath::Matrix4 inverseMatrix = mat;
			inverseMatrix.inverse();
			
			glm::mat4 inverseGlm = glm::inverse(matGlm);

			CHECK_MATRIX4(inverseMatrix, inverseGlm);
		}

		{

			float fov = 45.0f;  // Field of view in degrees
			float aspectRatio = 16.0f / 9.0f;  // Aspect ratio
			float near = 0.1f;  // Near plane
			float far = 100.0f;  // Far plane

			// LibMath perspective matrix
			LibMath::Matrix4 perspective = LibMath::Matrix4::perspective(fov, aspectRatio, near, far);

			// GLM perspective matrix
			glm::mat4 perspectiveGlm = glm::perspective(glm::radians(fov), aspectRatio, near, far);

			CHECK_MATRIX4(perspective, perspectiveGlm);
					
		}
	}
}