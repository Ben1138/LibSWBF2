#pragma once
#include "req.h"
#include "Types/Color.h"
#include "Types/LibString.h"
#include "Chunks/LVL/tern/tern.h"

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using Types::Vector2;
	using Types::Vector3;
	using Types::Color;
	using Chunks::LVL::terrain::tern;
	
	class Level;

	class LIBSWBF2_API Terrain
	{
	private:
		friend Level;
		friend List<Terrain>;

		Terrain();
		~Terrain();

	private:
		tern* p_Terrain;

		// the whole terrain, stiched together from all the patches
		List<Vector3> m_Positions;
		List<Vector3> m_Normals;
		List<Vector2> m_TexCoords;
		List<Color> m_Colors;

		mutable float_t* p_HeightMap;
		mutable uint8_t* p_BlendMap;

	public:
		static bool FromChunk(tern* terrainChunk, Terrain& out);

		String GetName() const;

		// count is number of indices, NOT number of bytes!
		bool GetIndexBuffer(ETopology requestedTopology, uint32_t& count, uint32_t*& indexBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetVertexBuffer(uint32_t& count, Vector3*& vertexBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetNormalBuffer(uint32_t& count, Vector3*& normalBuffer) const;

		// count is number of colors, NOT number of bytes!
		void GetColorBuffer(uint32_t& count, Color*& colorBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetUVBuffer(uint32_t& count, Vector2*& uvBuffer) const;

		void GetHeightMap(uint32_t& dim, uint32_t& dimScale, float_t*& heightData) const;

		void GetBlendMap(uint32_t& dim, uint32_t& numLayers, uint8_t*& imgData) const;

		void GetHeightBounds(float_t& floor, float_t& ceiling) const;
 
		// Texture name for each terrain layer. Usually 16 layers
		const List<String>& GetLayerTextures() const;
	};
}