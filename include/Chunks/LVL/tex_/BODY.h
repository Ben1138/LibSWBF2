#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Enums.h"
#include "DirectX/DXTexCrossPlat.h"

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
		mutable DXTexCrossPlat::CrossPlatImage* p_Image = nullptr;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		bool GetImageData(ETextureFormat format, uint16_t& width, uint16_t& height, const uint8_t*& data) const;

		~BODY();
	};
}