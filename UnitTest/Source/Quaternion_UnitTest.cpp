#include <LibMath/Quaternion.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#define CHECK_QUATERNION(quaternion, quaternionGlm) \
						CHECK(quaternion.m_x == Catch::Approx(quaternionGlm.x)); \
						CHECK(quaternion.m_y == Catch::Approx(quaternionGlm.y)); \
						CHECK(quaternion.m_z == Catch::Approx(quaternionGlm.z)); \
						CHECK(quaternion.m_w == Catch::Approx(quaternionGlm.w));

#define CHECK_VECTOR3(vector, vectorGlm) \
						CHECK(vector.m_x == Catch::Approx(vectorGlm.x)); \
						CHECK(vector.m_y == Catch::Approx(vectorGlm.y)); \
						CHECK(vector.m_z == Catch::Approx(vectorGlm.z))


TEST_CASE("Quaternion", "[.all][Quaternion]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			[[maybe_unused]] LibMath::Quaternion temp;
		}

		// default constructor
		LibMath::Quaternion empty;
		glm::quat emptyGlm{};
		CHECK_QUATERNION(empty, emptyGlm);

		// param constructor
		// glm takes w first I take w last
		LibMath::Quaternion allParam{ 2.5f, .5f, 2.f, 1.f };
		glm::quat allParamGlm{ 1.f, 2.5f, .5f, 2.f };
		CHECK_QUATERNION(allParam, allParamGlm);

		// copy constructor
		LibMath::Quaternion copy{ allParam };
		glm::quat copyGlm{ allParamGlm };
		CHECK_QUATERNION(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_QUATERNION(empty, emptyGlm);

		glm::quat identityGlm{ 1.f, 0, 0, 0 };;
		CHECK_QUATERNION(LibMath::Quaternion::identity(), identityGlm);

		// axis and angle initializer
		float angleGlm = glm::radians(90.0f);
		glm::vec3 axisGlm(0.0f, 1.0f, 0.0f);
		glm::quat rotationGlm = glm::angleAxis(angleGlm, glm::normalize(axisGlm));
		
		LibMath::Radian angle(g_Pi / 2);
		LibMath::Vector3 axis(0.0f, 1.0f, 0.0f);
		LibMath::Quaternion rotation{ angle, axis };

		CHECK_QUATERNION(rotation, rotationGlm);

		angleGlm = glm::radians(0.f);
		axisGlm = glm::vec3(12.0f, 1.0f, 0.0f);
		rotationGlm = glm::angleAxis(angleGlm, glm::normalize(axisGlm));

		angle = LibMath::Radian(0);
		axis = LibMath::Vector3(12.0f, 1.0f, 0.0f);
		rotation = LibMath::Quaternion{ angle, axis };

		CHECK_QUATERNION(rotation, rotationGlm);

		// OpenGL compatibility
		CHECK(sizeof LibMath::Quaternion == sizeof glm::quat);
		CHECK(memcmp(&allParam, &allParamGlm, sizeof allParam) == 0);
	}

	SECTION("Arithmetic")
	{
		LibMath::Quaternion q1{ 1.0f, 2.0f, 3.0f, 4.0f };
		LibMath::Quaternion q2{ 2.0f, 4.0f, 6.0f, 8.0f };
		float scalar = 2.0f;

		glm::quat glmQ1{ 4.0f, 1.0f, 2.0f, 3.0f };
		glm::quat glmQ2{ 8.0f, 2.0f, 4.0f, 6.0f };
		float glmScalar = 2.0f;

		{// Addition

			LibMath::Quaternion resultAdd = q1 + q2;
			glm::quat glmResultAdd = glmQ1 + glmQ2;
			CHECK_QUATERNION(resultAdd, glmResultAdd);			
		}

		{// float multiplication

			LibMath::Quaternion resultMul = q1 * scalar;
			glm::quat glmResultMul = glmQ1 * glmScalar;
			CHECK_QUATERNION(resultMul, glmResultMul);
		}

		{// quaternion multiplication

			LibMath::Quaternion resultMul = q1 * q2;
			glm::quat glmResultMul = glmQ1 * glmQ2;
			CHECK_QUATERNION(resultMul, glmResultMul);
		}
	}

	SECTION("Accessor")
	{
		float const x = 2.5f;
		float const y = .5f;
		float const z = 2.f;
		float const w = 1.f;
		LibMath::Quaternion quaternion{ x, y, z, w };

		{
			LibMath::Quaternion const& quaternionConst = quaternion;
			CHECK(quaternionConst[0] == x);
			CHECK(quaternionConst[1] == y);
			CHECK(quaternionConst[2] == z);
			CHECK(quaternionConst[3] == w);
		}

		{
			quaternion[0] += 1.f;
			quaternion[1] += 1.f;
			quaternion[2] += 1.f;
			quaternion[3] += 1.f;
			CHECK(quaternion[0] == x + 1.f);
			CHECK(quaternion[1] == y + 1.f);
			CHECK(quaternion[2] == z + 1.f);
			CHECK(quaternion[3] == w + 1.f);
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		LibMath::Quaternion self{ 2.5f, .5f, 2.f, 1.f };
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(LibMath::Quaternion{ 2.5f, .5f, 2.f, 1.f } == LibMath::Quaternion{ 2.5f, .5f, 2.f, 1.f });
		CHECK_FALSE(LibMath::Quaternion{ 2.5f, .5f, 2.f, 1.f } != LibMath::Quaternion{ 2.5f, .5f, 2.f, 1.f });

		// trying to find copy/paste mistake
		LibMath::Quaternion twos{ 2.f, 2.f, 2.f, 2.f };
		CHECK_FALSE(LibMath::Quaternion{ .5f, 2.f, 2.f, 2.f } == twos);
		CHECK_FALSE(LibMath::Quaternion{ 2.f, .5f, 2.f, 2.f } == twos);
		CHECK_FALSE(LibMath::Quaternion{ 2.f, 2.f, .5f, 2.f } == twos);
		CHECK_FALSE(LibMath::Quaternion{ 2.f, 2.f, 2.f, .5f } == twos);
		CHECK(LibMath::Quaternion{ .5f, 2.f, 2.f, 2.f } != twos);
		CHECK(LibMath::Quaternion{ 2.f, .5f, 2.f, 2.f } != twos);
		CHECK(LibMath::Quaternion{ 2.f, 2.f, .5f, 2.f } != twos);
		CHECK(LibMath::Quaternion{ 2.f, 2.f, 2.f, .5f } != twos);
		CHECK_FALSE(twos == LibMath::Quaternion{ .5f, 2.f, 2.f, 2.f });
		CHECK_FALSE(twos == LibMath::Quaternion{ 2.f, .5f, 2.f, 2.f });
		CHECK_FALSE(twos == LibMath::Quaternion{ 2.f, 2.f, .5f, 2.f });
		CHECK_FALSE(twos == LibMath::Quaternion{ 2.f, 2.f, 2.f, .5f });
		CHECK(twos != LibMath::Quaternion{ .5f, 2.f, 2.f, 2.f });
		CHECK(twos != LibMath::Quaternion{ 2.f, .5f, 2.f, 2.f });
		CHECK(twos != LibMath::Quaternion{ 2.f, 2.f, .5f, 2.f });
		CHECK(twos != LibMath::Quaternion{ 2.f, 2.f, 2.f, .5f });
	}

	SECTION("Functionality")
	{
		LibMath::Quaternion const base{ 2.5f, .5f, 2.f, 1.f };
		LibMath::Quaternion const other{ 3.75f, 3.f, .75f, 1.f };

		glm::quat const baseGlm{ 1.f, 2.5f, .5f, 2.f };
		glm::quat const otherGlm{ 1.f, 3.75f, 3.f, .75f };

		{// Magnitude
			{
				float magnitude = base.magnitude();

				float magnitudeGlm = glm::length(baseGlm);

				CHECK(magnitude == Catch::Approx(magnitudeGlm));
			}

			{
				float magnitudeSquare = base.magnitudeSquared();

				float magnitudeSquareGlm = glm::length2(baseGlm);

				CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
			}
		}

		{// Unit
			{
				LibMath::Quaternion unit = base;

				CHECK_FALSE(unit.isUnit());
				CHECK(unit.normalize().isUnit());
				CHECK(LibMath::Quaternion::identity().isUnit());
			}
		}

		{// Normalize
			LibMath::Quaternion normalize = base;
			normalize.normalize();

			glm::quat expected = baseGlm;

			CHECK_QUATERNION(normalize, glm::normalize(expected));
		}
		
		{// Conjugate
			LibMath::Quaternion conjugate = base;
			conjugate.conjugate();

			glm::quat expected = baseGlm;

			CHECK_QUATERNION(conjugate, glm::conjugate(expected));
		}
		
		{// Inverse
			LibMath::Quaternion inverse = base;
			inverse.inverse();

			glm::quat expected = baseGlm;

			CHECK_QUATERNION(inverse, glm::inverse(expected));
		}

		{// Rotate
			LibMath::Quaternion rotation = base;
			LibMath::Vector3 point{ 1.f,2.f,3.f };

			glm::quat expected = baseGlm;
			glm::vec3 pointGlm{ 1.f,2.f,3.f };

			CHECK_VECTOR3(rotation.normalize().rotate(point), rotate(glm::normalize(expected), pointGlm));
		}


		{// Slerp
			constexpr float		alpha = .5f;

			LibMath::Quaternion start = base;
			LibMath::Quaternion end = other;
			
			LibMath::Quaternion slerp = LibMath::Quaternion::slerp(start.normalize(), end.normalize(), alpha);

			glm::quat startGlm = baseGlm;
			glm::quat endGlm = otherGlm;

			glm::quat slerpGlm = glm::slerp(glm::normalize(startGlm), glm::normalize(endGlm), alpha);

			CHECK_QUATERNION(slerp, slerpGlm);
		}
	}
}