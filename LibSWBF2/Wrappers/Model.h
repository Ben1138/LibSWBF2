#pragma once
#include "req.h"
#include "Segment.h"
#include "Chunks\LVL\modl\LVL.modl.h"

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Chunks::LVL::modl::modl;
	using Chunks::LVL::modl::segm;
	class Level;

	class LIBSWBF2_API Model
	{
	public:
		Model() = default;
		~Model() = default;

	private:
		modl* p_Model;
		List<Segment> m_Segments;

	public:
		static bool FromChunk(Level* mainContainer, modl* modelChunk, Model& out);

		String GetName() const;
		const List<Segment>& GetSegments() const;
	};
}