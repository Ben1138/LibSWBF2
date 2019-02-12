#include "stdafx.h"
#include "TERR.h"
#include <algorithm>

namespace LibSWBF2::Chunks::Terrain
{
	void TERR::WriteToStream(FileWriter& stream)
	{

	}

	void TERR::ReadFromStream(FileReader& stream)
	{
		ChunkHeader TerrHeader = stream.ReadChunkHeader(false);

		if (!TerrHeader == HeaderNames::TERR)
		{
			LOG("Wrong File Format!", ELogType::Warning);
			return;
		}

		/*
			Type: long int
			Size: 4 Bytes
			.TER file version number (21 for SWBF, 22 for SWBFII)
		*/
		FileVersion = stream.ReadUInt32();

		/*
			Type: short int[4]
			Size: 8 Bytes
			Terrain extents
			Example: -8, -8, 8, 8 for a 16x16 map
		*/
		for (int i = 0; i < 4; i++)
			TerrainExtents[i] = stream.ReadUInt16();

		/*
			Type: long int
			Size: 4 Bytes
			Unknown
		*/
		unk1 = stream.ReadUInt32();

		/*
			Type: float [16]
			Size: 64 Bytes
			Tile-range for each texture layer
			0.031 (1/32): the texture spans 32 meters. This is stored as 1/X of the value in ZeroEditor
		*/
		for (int i = 0; i < 16; i++)
			TileRange[i] = stream.ReadFloat();

		/*
			Type: byte [16]
			Size: 16 Bytes
			Mapping for each texture-layer. 0 is normal
		*/
		for (int i = 0; i < 16; i++)
			TextureLayerMapping[i] = stream.ReadByte();

		/*
			Type: byte [64]
			Size: 64 Bytes
			Unknown
		*/
		for (int i = 0; i < 64; i++)
			unk2[i] = stream.ReadByte();

		/*
			Type: float
			Size: 4 Bytes
			Map height multiplier
		*/
		MapHeightMultiplier = stream.ReadFloat();

		/*
			Type: float
			Size: 4 Bytes
			Grid-scale. Distance between points
		*/
		GridScale = stream.ReadFloat();

		/*
			Type: long int
			Size: 4 Bytes
			Unknown
		*/
		unk3 = stream.ReadUInt32();

		/*
			Type: long int
			Size: 4 Bytes
			Full map size stored in the .TER file. The same or bigger than the map extents
		*/
		MapSize = stream.ReadUInt32();

		/*
			Type: long int
			Size: 4 Bytes
			Terrain options set in the editor as mask. Allows toggling of certain features (i.e. for space maps)
			0 — None
			1 — Terrain
			2 — Water
			4 — Foliage
		*/
		TerrainOptions = stream.ReadUInt32();

		/*
			Type: byte
			Size: 1 Byte
			Unknown - Only present in SWBF2
		*/
		if (FileVersion == 22)
			stream.ReadByte();

		/*
			Type: TextureLayer[16]
			Size: 1024 Bytes
			TextureLayer:
			-Type: char[32]
			--Size 32 Bytes
			--Diffuse texture name
			-Type: char[32]
			--Size 32 Bytes
			--Detail texture name
		*/
		for (int i = 0; i < 16; i++)
			TextureLayers[i] = TextureLayer(stream.ReadString(32).~String, stream.ReadString(32).~String);

		/*
			Type: WaterLayer[16]
			Size: 1088 Bytes
			WaterLayer
		*/
		for (int i = 0; i < 16; i++)
		{
			/*
				Type: float[2]
				Size 8 Bytes
				Water height value (twice)
			*/
			float_t WaterHeight[2];
			for (int i = 0; i < 2; i++)
				WaterHeight[i] = stream.ReadFloat();

			/*
				Type: byte[8]
				Size 8 Bytes
				Unknown
			*/
			uint8_t unk[8];
			for (int i = 0; i < 8; i++)
				unk[i] = stream.ReadByte();

			/*
				Type: float[2]
				Size: 8 Bytes
				UV animation velocity
			*/
			float_t UVAnimationVelocity[2];
			for (int i = 0; i < 2; i++)
				UVAnimationVelocity[i] = stream.ReadFloat();

			/*
				Type: float[2]
				Size: 8 Bytes
				UV animation repeat
			*/
			float_t UVAnimationRepeat[2];
			for (int i = 0; i < 2; i++)
				UVAnimationRepeat[i] = stream.ReadFloat();

			/*
				Type: byte[4]
				Size: 4 Bytes
				RGBA color values
			*/
			uint8_t RGBA[4];
			for (int i = 0; i < 4; i++)
				RGBA[i] = stream.ReadByte();

			/*
				Type: char[32]
				Size: 32 Bytes
				Water texture name
			*/
			string TextureName = stream.ReadString(32).~String;

			WaterLayers[i] = WaterLayer(WaterHeight, unk, UVAnimationVelocity, UVAnimationRepeat, RGBA, TextureName);
		}

		/*
			Type: char[16][32]
			Size: 512 Bytes
			Road decal texture names
		*/
		for (int i = 0; i < 16; i++)
			strcpy(RoadDecalTextureNames[i], stream.ReadString(32).~String.c_str());

		/*
			Type: long int
			Size: 4 Bytes
			4x4 terrain blocks covered by decals (?)
		*/
		unk4 = stream.ReadUInt32();
		
		/*
			Type: byte[8]
			Size: 8 Bytes
			Unknown
		*/
		for (int i = 0; i < 8; i++)
			unk5[i] = stream.ReadByte();

		// .....
	}

	bool TERR::WriteToFile(const string& Path)
	{
		// TODO: implement
		return false;
	}

	bool TERR::ReadFromFile(const string& Path)
	{
		FileReader reader;
		if (reader.Open(Path))
		{
			try
			{
				ReadFromStream(reader);
				reader.Close();
			}
			catch (int& e)
			{
				e; // avoid C4101 warning
				LOG("Aborting read process...", ELogType::Error);
				return false;
			}
			LOG("Successfully finished reading process!", ELogType::Info);
			return true;
		}
		LOG("Could not open File " + Path + "! Non existent?", ELogType::Warning);
		return false;
	}

	TextureLayer::TextureLayer(string DiffuseName, string DetailName)
	{
		strcpy(this->DiffuseName, DiffuseName.c_str());
		strcpy(this->DetailName, DetailName.c_str());
	}

	WaterLayer::WaterLayer(float_t WaterHeight[], uint8_t unk[], float_t UVAnimationVelocity[], float_t UVAnimationRepeat[], uint8_t RGBA[], string TextureName)
	{
		std::copy(WaterHeight, WaterHeight, this->WaterHeight);
		std::copy(unk, unk, this->unk);
		std::copy(UVAnimationVelocity, UVAnimationVelocity, this->UVAnimationVelocity);
		std::copy(UVAnimationRepeat, UVAnimationRepeat, this->UVAnimationRepeat);
		std::copy(RGBA, RGBA, this->RGBA);
		strcpy(this->TextureName, TextureName.c_str());
	}
}