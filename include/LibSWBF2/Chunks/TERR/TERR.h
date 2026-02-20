#pragma once
#include <LibSWBF2/Chunks/HeaderNames.h>
#include <LibSWBF2/Types/List.h>
#include <LibSWBF2/Types/LibString.h>
#include <LibSWBF2/Types/Vector2.h>

namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Chunks::LVL::terrain
{
	using LibSWBF2::Types::List;
	using LibSWBF2::Types::Vector2;
	using LibSWBF2::Types::String;

	// TODO: Move to Types into a dedicated header file
	struct LIBSWBF2_API TextureLayer
	{
		String DiffuseName;
		String DetailName;
	};

	// TODO: Move to Types into a dedicated header file
	struct LIBSWBF2_API WaterLayer
	{
		float WaterHeight;
		Vector2 UVAnimationVelocity;
		Vector2 UVAnimationRepeat;
		uint8_t RGBA[4]; // TODO: Introduce new Color32 type and use here
		String TextureName;
	};

	struct LIBSWBF2_API TERR
	{
		static TERR* Create();
		static void Destroy(TERR* terrain);

	protected:
		TERR() = default;
		~TERR() = default;

	public:
		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);
		bool WriteToFile(const String& Path);
		bool ReadFromFile(const String& Path);

#pragma region Header
		uint32_t FileVersion;
		uint16_t TerrainExtents[4];
		float TileRange[16];
		uint8_t TextureLayerMapping[16];
		float MapHeightMultiplier;
		float GridScale;
		uint32_t MapSize;
		uint32_t TerrainOptions;
		TextureLayer TextureLayers[16];
		WaterLayer WaterLayers[16];
		String RoadDecalTextureNames[16];
#pragma endregion Header

#pragma region Blocks
		//List<List<uint16_t>> Heights;
		//List<List<uint8_t[4]>> Color4u8;
		//List<List<uint8_t[4]>> Color2;
		//List<List<uint8_t[16]>> Texture;

		//List<List<uint8_t[2]>> BlendHeights1;
		//List<List<uint8_t[2]>> BlendHeights2;
#pragma endregion Blocks
	};
}