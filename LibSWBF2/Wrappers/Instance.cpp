#include "stdafx.h"
#include "Instance.h"
#include "Types/LibString.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Wrappers
{
	bool Instance::FromChunk(Level* mainContainer, inst* instanceChunk, Instance& out)
	{
		if (mainContainer == nullptr)
		{
			LOG_ERROR("Given mainContainer was NULL!");
			return false;
		}
		if (instanceChunk == nullptr)
		{
			LOG_ERROR("Given instanceChunk was NULL!");
			return false;
		}

		out.p_Instance = instanceChunk;
		return true;
	}

	Types::String Instance::GetType() const
	{
		return p_Instance->p_Info->p_Type->m_Text;
	}

	Types::String Instance::GetName() const
	{
		return p_Instance->p_Info->p_Name->m_Text;
	}

	Vector3 Instance::GetPosition() const
	{
		return p_Instance->p_Info->p_XFRM->m_Position;
	}

	Vector4 Instance::GetRotation() const
	{
		return MatrixToQuaternion(p_Instance->p_Info->p_XFRM->m_RotationMatrix);
	}
}