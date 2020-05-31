#include "stdafx.h"
#include "TERR.h"
#include "Exceptions.h"
#include <algorithm>
#include <vector>

namespace LibSWBF2::Chunks::Terrain
{
	TERR* TERR::Create()
	{
		return new TERR();
	}

	void TERR::Destroy(TERR* terrain)
	{
		delete terrain;
	}

	void TERR::WriteToStream(FileWriter& stream)
	{
		throw std::runtime_error("Not implemented!");
	}

	void TERR::ReadFromStream(FileReader& stream)
	{
		ChunkHeader TerrHeader = stream.ReadChunkHeader(false);

		if (!TerrHeader == HeaderNames::TERR)
		{
			LOG("Wrong File Format!", ELogType::Warning);
			return;
		}

#pragma region Header
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
		stream.SkipBytes(4);

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
		stream.SkipBytes(64);

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
		stream.SkipBytes(4);

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
		{
			TextureLayers[i].DiffuseName = stream.ReadString(32);
			TextureLayers[i].DetailName = stream.ReadString(32);
		}

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
			WaterLayers[i].WaterHeight = stream.ReadFloat();
			stream.SkipBytes(sizeof(float_t)); // just ignore second height

			/*
				Type: byte[8]
				Size 8 Bytes
				Unknown
			*/
			stream.SkipBytes(8);

			/*
				Type: float[2]
				Size: 8 Bytes
				UV animation velocity
			*/
			WaterLayers[i].UVAnimationVelocity.ReadFromStream(stream);

			/*
				Type: float[2]
				Size: 8 Bytes
				UV animation repeat
			*/
			WaterLayers[i].UVAnimationRepeat.ReadFromStream(stream);

			/*
				Type: byte[4]
				Size: 4 Bytes
				RGBA color values
			*/
			for (int j = 0; j < 4; j++)
				WaterLayers[i].RGBA[j] = stream.ReadByte();

			/*
				Type: char[32]
				Size: 32 Bytes
				Water texture name
			*/
			WaterLayers[i].TextureName = stream.ReadString(32);
		}

		/*
			Type: char[16][32]
			Size: 512 Bytes
			Road decal texture names
		*/
		for (int i = 0; i < 16; i++)
			RoadDecalTextureNames[i] = stream.ReadString(32);

		/*
			Type: long int
			Size: 4 Bytes
			4x4 terrain blocks covered by decals (?)
		*/
		stream.SkipBytes(4);

		/*
			Type: byte[8]
			Size: 8 Bytes
			Unknown
		*/
		stream.SkipBytes(8);

#pragma endregion Header

#pragma region Blocks
		///*
		//	Type: signed short
		//	Size: MapSize * MapSize * 2
		//	Height value for every point on the grid. This value will be multiplied with the map scale multiplier
		//*/
		//for (uint32_t x = 0; x < MapSize; x++)
		//	for (uint32_t y = 0; y < MapSize; y++)
		//		Heights[x][y] = stream.ReadUInt16();

		///*
		//	Type: byte [4]
		//	Size: MapSize * MapSize * 4
		//	Color values for every point on the grid. 4 bytes (from 0 to 255) corresponding to the RGBA channels
		//*/
		//for (uint32_t x = 0; x < MapSize; x++)
		//	for (uint32_t y = 0; y < MapSize; y++)
		//		for (int i = 0; i < 4; i++)
		//			Color[x][y][i] = stream.ReadByte();

		///*
		//	Type: byte [4]
		//	Size: MapSize * MapSize * 4
		//	Color values for every point on the grid. 4 bytes (from 0 to 255) corresponding to the RGBA channels
		//*/
		//for (uint32_t x = 0; x < MapSize; x++)
		//	for (uint32_t y = 0; y < MapSize; y++)
		//		for (int i = 0; i < 4; i++)
		//			Color2[x][y][i] = stream.ReadByte();

		///*
		//	Type: byte [16]
		//	Size: MapSize * MapSize * 16
		//	One byte (0-255) for each TextureLayer indicating the transparency of the corresponding texture layer
		//*/
		//for (uint32_t x = 0; x < MapSize; x++)
		//	for (uint32_t y = 0; y < MapSize; y++)
		//		for (int i = 0; i < 16; i++)
		//			Texture[x][y][i] = stream.ReadByte();

		///*
		//	Type: byte [2]
		//	Size: MapSize * MapSize * 2
		//	Last used blend heights for every block, possibly lower-left and upper-right values of the blend tool
		//*/
		//for (uint32_t x = 0; x < MapSize; x++)
		//	for (uint32_t y = 0; y < MapSize; y++)
		//		for (int i = 0; i < 2; i++)
		//			BlendHeights1[x][y][i] = stream.ReadByte();

		///*
		//	Type: byte [2]
		//	Size: MapSize * MapSize * 2
		//	Last used blend heights for every block, possibly lower-left and upper-right values of the blend tool
		//*/
		//for (uint32_t x = 0; x < MapSize; x++)
		//	for (uint32_t y = 0; y < MapSize; y++)
		//		for (int i = 0; i < 2; i++)
		//			BlendHeights2[x][y][i] = stream.ReadByte();

#pragma endregion Blocks
		// .....
	}

	bool TERR::WriteToFile(const string& Path)
	{
		// TODO: implement
		LOG("Writing TERR files not implemented yet!", ELogType::Warning);
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
			catch (InvalidChunkException& e)
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
}