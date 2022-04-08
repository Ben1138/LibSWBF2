#pragma once
#include "req.h"

#include "Types/LibString.h"
#include "Types/List.h"


namespace LibSWBF2::Chunks::LVL::plan
{
	struct plan;
}


namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;

	class LIBSWBF2_API PlanSet
	{
	typedef LibSWBF2::Chunks::LVL::plan::plan plan;

	private:
		friend Level;
		friend List<PlanSet>;

		PlanSet() = default;
		~PlanSet() = default;

		plan* p_Plan;


	public:
		static bool FromChunk(plan* planChunk, PlanSet& out);

		const List<Hub>& GetHubs() const;
		const List<Connection>& GetConnections() const;
	};
}