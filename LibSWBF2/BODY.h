#pragma once
#include "GenericChunk.h"
#include "FMT_.INFO.h"

// forward declare to avoid including the DirectX header
namespace DirectX { struct ScratchImage; }

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_EXP BODY : public GenericChunk
	{
	private:
		DirectX::ScratchImage* p_Image = nullptr;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		// always delivers format R8 G8 B8 A8
		void GetImageData(uint16_t& width, uint16_t& height, uint8_t*& data);
	};
}