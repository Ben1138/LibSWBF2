// THis file should NEVER be included in exposed headers!
#pragma once
#include "Types\Vector4.h"
#include "Types\Matrix3x3.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat3x3.hpp>


namespace LibSWBF2
{
	using Types::Vector3;
	using Types::Vector4;
	using Types::Matrix3x3;

	glm::vec3 ToGLM(const Vector3& vector);
	Vector3 ToLib(const glm::vec3 vector);
	glm::mat3 ToGLM(const Matrix3x3& matrix);
	Vector4 ToLib(const glm::quat& quaternion);
}