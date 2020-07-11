#pragma once
#include "Chunks/LVL/scr_/scr_.h"
#include "Types/Enums.h"

namespace LibSWBF2::Wrappers
{
	using Chunks::LVL::script::scr_;
	using LibSWBF2::Types::String;

	class LIBSWBF2_API Script
	{
	public:
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