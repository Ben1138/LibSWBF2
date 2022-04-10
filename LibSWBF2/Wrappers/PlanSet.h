#pragma once
#include "req.h"

#include "Types/LibString.h"
#include "Types/List.h"
#include "Types/Planning.h"


namespace LibSWBF2::Chunks::plan
{
	struct plan;
}


namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using Types::Hub;
	using Types::Connection;

	class Level;

	class LIBSWBF2_API PlanSet
	{
	typedef LibSWBF2::Chunks::plan::plan plan;

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