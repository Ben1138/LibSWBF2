#pragma once

#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::plan
{
	struct LIBSWBF2_API PLAN_INFO : public GenericChunk<"INFO"_m>
	{
	public:
		uint16_t m_iHubCount;
		uint16_t m_iConnectionCount;

		void ReadFromStream(FileReader& stream) override;
	};

	struct LIBSWBF2_API NODE : public GenericChunk<"NODE"_m>
	{
	public:
		struct Hub
		{
			LibSWBF2::Types::String name;
			Vector3 position;
			float_t radius;
		};

		NODE(uint16_t count);

		uint16_t m_iCount;
		std::vector<Hub> m_aHubs;

		void ReadFromStream(FileReader& stream) override;
	};

	struct LIBSWBF2_API ARCS : public GenericChunk<"ARCS"_m>
	{
	public:
		struct Connection
		{
			LibSWBF2::Types::String name;
			uint8_t start;
			uint8_t end;
			uint32_t flag_one;
			uint32_t flag_two;
		};

		ARCS(uint16_t count);

		uint16_t m_iCount;
		std::vector<Connection> m_aConnections;

		void ReadFromStream(FileReader& stream) override;
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