#include "stdafx.h"
#include "InternalHelpers.h"

namespace LibSWBF2
{
	Vector2 ToLib(const glm::vec2 vector)
	{
		return Vector2(vector.x, vector.y);
	}

	glm::vec3 ToGLM(const Vector3& vector)
	{
		return glm::vec3(vector.m_X, vector.m_Y, vector.m_Z);
	}

	Vector3 ToLib(const glm::vec3 vector)
	{
		return Vector3(vector.x, vector.y, vector.z);
	}

	glm::mat3 ToGLM(const Matrix3x3& matrix)
	{
		return glm::mat3(
			matrix.matrix[0][0], matrix.matrix[0][1], matrix.matrix[0][2],
			matrix.matrix[1][0], matrix.matrix[1][1], matrix.matrix[1][2],
			matrix.matrix[2][0], matrix.matrix[2][1], matrix.matrix[2][2]
		);
		//return glm::mat3(
		//	matrix.matrix[0][0], matrix.matrix[1][0], matrix.matrix[2][0],
		//	matrix.matrix[0][1], matrix.matrix[1][1], matrix.matrix[2][1],
		//	matrix.matrix[0][2], matrix.matrix[1][2], matrix.matrix[2][2]
		//);
	}

	Vector4 ToLib(const glm::quat& quaternion)
	{
		return Vector4(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
	}

	List<uint32_t> TriangleStripToTriangleList(List<uint16_t> indexBuffer, uint32_t offset)
	{
		List<uint32_t> result;

		uint8_t triCount = 0;
		size_t numIndices = indexBuffer.Size();
		for (size_t i = 0; i < numIndices; ++i)
		{
			if (triCount == 3)
			{
				i -= 2;
				triCount = 0;
			}

			result.Add(indexBuffer[i] + offset);
			triCount++;
		}

		//after conversion to Triangle List, indices are listed CW CCW CW CCW, so let's flip them
		bool flip = false;
		size_t numTriangles = result.Size();
		for (size_t i = 0; i < numTriangles; i += 3)
		{
			if (flip)
			{
				std::swap(result[i], result[i + 2]);
			}
			flip = !flip;
		}

		return result;
	}
}