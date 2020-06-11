#include "stdafx.h"
#include "Instance.h"
#include "Logging\Logger.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Tools
{
	using Logging::ELogType;

	bool Instance::FromChunk(Level* mainContainer, inst* instanceChunk, Instance& out)
	{
		if (mainContainer == nullptr)
		{
			LOG("Given mainContainer was NULL!", ELogType::Error);
			return false;
		}
		if (instanceChunk == nullptr)
		{
			LOG("Given instanceChunk was NULL!", ELogType::Error);
			return false;
		}

		out.p_Instance = instanceChunk;
		return true;
	}

	String Instance::GetType() const
	{
		return p_Instance->p_Info->p_Type->m_Text;
	}

	String Instance::GetName() const
	{
		return p_Instance->p_Info->p_Name->m_Text;
	}

	Vector3 Instance::GetPosition() const
	{
		return p_Instance->p_Info->p_XFRM->m_Position;
	}

	Vector4 Instance::GetRotation() const
	{
		glm::mat3 matrix = ToGLM(p_Instance->p_Info->p_XFRM->m_RotationMatrix);
		glm::quat quat = glm::quat(matrix);

		// return the quaternion as defined in wld or lyr files
		quat = glm::quat(quat.x, quat.y, quat.z, quat.w);

		return ToLib(quat);
	}
}