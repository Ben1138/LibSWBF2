#pragma once
#include "req.h"
#include "Types/Color.h"
#include "Types/LibString.h"
#include "Chunks/LVL/tern/tern.h"

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using Types::Vector3;
	using Types::Color;
	using Chunks::LVL::terrain::tern;
	class Level;

	class LIBSWBF2_API Terrain
	{
	public:
		Terrain() = default;
		~Terrain() = default;

	private:
		tern* p_Terrain;

		// the whole terrain, stiched together from all the patches
		List<Vector3> m_Positions;
		List<Vector3> m_Normals;
		List<Color> m_Colors;

	public:
		static bool FromChunk(Level* mainContainer, tern* terrainChunk, Terrain& out);

		String GetName() const;

		// count is number of vectors, NOT number of bytes!
		void GetVertexBuffer(uint32_t& count, Vector3*& vertexBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetNormalBuffer(uint32_t& count, Vector3*& normalBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetColorBuffer(uint32_t& count, Color*& colorBuffer) const;
	};
}