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

		for (int i = 0; i < indexBuffer.Size() - 2; i++)
		{
			if (indexBuffer[i]   != indexBuffer[i+1] && //Check for degenerate tris
				indexBuffer[i+1] != indexBuffer[i+2] && //
				indexBuffer[i]   != indexBuffer[i+2])	//
			{
				if (i % 2 == 0) //swap clockwiseness 
				{
					result.Add(indexBuffer[i]   + offset);
					result.Add(indexBuffer[i+1] + offset);
					result.Add(indexBuffer[i+2] + offset);
				} 
				else 
				{
					result.Add(indexBuffer[i+1] + offset);
					result.Add(indexBuffer[i]   + offset);
					result.Add(indexBuffer[i+2] + offset);
				}
			}
		}

		return result;
	}


	Vector4 MatrixToQuaternion(const Matrix3x3& matrix)
	{
		glm::mat3 mat = ToGLM(matrix);
		glm::quat quat = glm::quat(mat);
		return ToLib(quat);
	}

	std::string ToLower(String name)
	{
		std::string result = name.Buffer();
		std::transform(result.begin(), result.end(), result.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return result;
	}
}