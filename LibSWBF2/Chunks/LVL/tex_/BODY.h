#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Enums.h"
#include "FMT_.INFO.h"

#ifdef _WIN32
namespace DirectX { class ScratchImage; }
#else
namespace DXTexCrossPlat { class CrossPlatImage; }
#endif


namespace LibSWBF2::Chunks::LVL::LVL_texture
{
	struct LIBSWBF2_API BODY : public GenericChunk<"BODY"_m>
	{
	private:

#ifdef _WIN32
		DirectX::ScratchImage* p_Image = nullptr;
#else
		DXTexCrossPlat::CrossPlatImage* p_Image = nullptr;		
#endif

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		bool GetImageData(ETextureFormat format, uint16_t& width, uint16_t& height, const uint8_t*& data);

		~BODY();
	};
}