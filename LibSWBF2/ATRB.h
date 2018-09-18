#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	// Avoid C2365 (enum value redefinition) by
	// Putting them into different sub-namespaces
	namespace RenderFlags
	{
		// Bitmap flags
		enum ERenderFlags : uint8_t
		{
			Emissive = 1,
			Glow = 2,
			SingleSidedTransparency = 4,
			DoubleSidedTransparency = 8,
			HardEdgedTransparency = 16,
			PerPixelLighting = 32,
			Additive = 64,
			Specular = 128
		};
	}

	namespace RenderType
	{
		// Single value
		enum ERenderType : uint8_t
		{
			Normal = 0,
			Glow = 1,
			Lightmap = 2,
			Scrolling = 3,
			Specular = 4,
			Glossmap = 5,
			Chrome = 6,
			Animated = 7,
			Ice = 8,
			Sky = 9,
			Water = 10,
			Detail = 11,
			Scroll2 = 12,
			Rotate = 13,
			GlowRotate = 14,
			PlanarReflection = 15,
			GlowScroll = 16,
			GlowScroll2 = 17,
			CurvedReflection = 18,
			NormalMapFade = 19,
			NormalMapInverseFade = 20,
			IceReflection = 21,
			IceRefraction = 22,
			Emboss = 23,
			Wireframe = 24,
			Energy = 25,
			Afterburner = 26,
			Bumpmap = 27,
			BumpmapAndGlossmap = 28,
			Teleportal = 29,
			Multistate = 30,
			Shield = 31
		};
	}

	using RenderFlags::ERenderFlags;
	using RenderType::ERenderType;

	struct ATRB : public BaseChunk
	{
		ATRB();
		~ATRB();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		ERenderFlags m_RenderFlags;
		ERenderType m_RenderType;
		uint8_t m_Data0;		// what are these for ??
		uint8_t m_Data1;
	};
}