#pragma once
#include "HeaderNames.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Logger.h"
#include "Color.h"
#include "Vector4.h"
#include "List.h"
#include "LibString.h"

namespace LibSWBF2::Chunks::Terrain
{
	using Logging::Logger;
	using Logging::ELogType;
	using Types::Color;
	using Types::Vector2;
	using Types::Vector3;
	using Types::Vector4;
	using LibSWBF2::Types::List;
	using LibSWBF2::Types::String;

	struct TERR
	{
		TERR() = default;
		~TERR() = default;

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);
		bool WriteToFile(const string& Path);
		bool ReadFromFile(const string& Path);

		#pragma region Header
		uint32_t FileVersion;
		uint16_t TerrainExtents[4];
		uint32_t unk1;
		float_t TileRange[16];
		uint8_t TextureLayerMapping[16];
		uint8_t unk2[64];
		float_t MapHeightMultiplier;
		float_t GridScale;
		uint32_t unk3;
		uint32_t MapSize;
		uint32_t TerrainOptions;
		TextureLayer TextureLayers[16];
		WaterLayer WaterLayers[16];
		char RoadDecalTextureNames[16][32];
		uint32_t unk4;
		uint8_t unk5[8];
		#pragma endregion Header

		#pragma region Blocks
		List<List<uint16_t>> Heights;
		List<List<uint8_t[4]>> Color;
		List<List<uint8_t[4]>> Color2;
		List<List<uint8_t[16]>> Texture;

		List<List<uint8_t[2]>> BlendHeights1;
		List<List<uint8_t[2]>> BlendHeights2;
		#pragma endregion Blocks
	};

	struct TextureLayer
	{
		char DiffuseName[32];
		char DetailName[32];

		TextureLayer(string DiffuseName, string DetailName);
	};

	struct WaterLayer
	{
		float_t WaterHeight[2];
		uint8_t unk[8];
		float_t UVAnimationVelocity[2];
		float_t UVAnimationRepeat[2];
		uint8_t RGBA[4];
		char TextureName[32];

		WaterLayer(float_t WaterHeight[], uint8_t unk[], float_t UVAnimationVelocity[], float_t UVAnimationRepeat[], uint8_t RGBA[], string TextureName);
	};
}