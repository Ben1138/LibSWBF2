#include "pch.h"
#include "PlanSet.h"

#include "Chunks/LVL/plan/plan.h"


namespace LibSWBF2::Wrappers
{
	bool PlanSet::FromChunk(plan* planChunk, PlanSet& out)
	{
		if (planChunk == nullptr)
		{
			LOG_ERROR("Given planChunk was NULL!");
			return false;
		}

		out.p_Plan = planChunk;

		return true;
	}

	const List<Hub>& PlanSet::GetHubs() const
	{
		return p_Plan->m_pNode->m_aHubs;
	}

	const List<Connection>& PlanSet::GetConnections() const
	{
		return p_Plan->m_pArcs->m_aConnections;
	}
}