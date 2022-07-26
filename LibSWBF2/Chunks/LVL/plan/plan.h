#pragma once

#include "Chunks/GenericChunk.h"

#include "Types/Planning.h"


using LibSWBF2::Types::String;
using LibSWBF2::Types::Hub;
using LibSWBF2::Types::Connection;


namespace LibSWBF2::Chunks::plan
{

	struct LIBSWBF2_API PLAN_INFO : public GenericChunk<"INFO"_m>
	{
	public:
		uint16_t m_iHubCount;
		uint16_t m_iConnectionCount;

		void ReadFromStream(FileReader& stream) override;
		String ToString() const override;
	};

	struct LIBSWBF2_API NODE : public GenericChunk<"NODE"_m>
	{
	public:

		NODE(uint16_t count);

		uint16_t m_iCount;
		Types::List<Hub> m_aHubs;

		void ReadFromStream(FileReader& stream) override;
		String ToString() const override;

	};

	struct LIBSWBF2_API ARCS : public GenericChunk<"ARCS"_m>
	{
	public:
		ARCS(uint16_t count);

		uint16_t m_iCount;
		Types::List<Connection> m_aConnections;

		void ReadFromStream(FileReader& stream) override;
		String ToString() const override;
	};

	struct LIBSWBF2_API plan : public GenericChunk<"plan"_m>
	{
		PLAN_INFO* m_pInfo;
		NODE* m_pNode;
		ARCS* m_pArcs;

		void ReadFromStream(FileReader& stream) override;
	};

	struct LIBSWBF2_API PLNS : public GenericChunk<"PLNS"_m> { };
}