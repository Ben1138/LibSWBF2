#pragma once
#include "Chunks/LVL/Locl/Locl.h"
#include "Types/List.h"

namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Chunks::LVL::Localization::Locl;
	using LibSWBF2::Types::String;
	using LibSWBF2::Types::List;

	class LIBSWBF2_API Localization
	{
	private:
		friend class Level;
		friend class List<Localization>;

		Localization();
		~Localization();

	private:
		Locl* p_Locl;
		class LocalizationMaps* m_LocalizationMaps;

	public:
		static bool FromChunk(Locl* loclChunk, Localization& out);

		String GetName() const;

		// count is number of wide chars, NOT number of bytes!
		bool GetLocalizedWideString(const String& path, uint16_t*& chars, uint32_t& count) const;
	};
}