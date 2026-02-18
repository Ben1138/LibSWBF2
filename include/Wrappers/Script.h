#pragma once
#include "Types/Enums.h"
#include "Types/List.h"

namespace LibSWBF2::Chunks::LVL::script
{
	struct scr_;
}


namespace LibSWBF2::Wrappers
{
	using Chunks::LVL::script::scr_;
	using LibSWBF2::Types::String;
	using LibSWBF2::Types::List;

	class Level;

	class LIBSWBF2_API Script
	{
	private:
		friend Level;
		friend List<Script>;

		Script() = default;
		~Script() = default;

	private:
		scr_* p_Script;

	public:
		static bool FromChunk(scr_* scriptChunk, Script& out);

		String GetName() const;
		bool GetData(const uint8_t*& data, size_t& size) const;
	};
}