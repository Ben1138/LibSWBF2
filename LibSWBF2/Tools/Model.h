#pragma once
#include "req.h"
#include "Segment.h"
#include "Chunks\LVL\modl\LVL.modl.h"

namespace LibSWBF2::Tools
{
	using Types::List;
	using Chunks::LVL::modl::modl;
	using Chunks::LVL::modl::segm;
	class Level;

	class LIBSWBF2_EXP Model
	{
	private:
		Model(modl* modelChunk);
		~Model();

	private:
		modl* p_Model;
		List<Segment*> m_Segments;

	public:
		static Model* FromChunk(Level* mainContainer, modl* modelChunk);
		static void Destroy(Model* model);

		String GetName() const;
		const List<Segment*>& GetSegments() const;
	};
}