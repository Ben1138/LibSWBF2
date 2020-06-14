#pragma once
#include "req.h"
#include "Types\Vector4.h"
#include "Chunks\LVL\wrld\inst.h"

namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Chunks::LVL::wrld::inst;
	using Types::Vector3;
	using Types::Vector4;

	class Level;

	class LIBSWBF2_API Instance
	{
	public:
		Instance() = default;
		~Instance() = default;

	private:
		inst* p_Instance;

	public:
		static bool FromChunk(Level* mainContainer, inst* instanceChunk, Instance& out);

		String GetType() const;
		String GetName() const;
		Vector3 GetPosition() const;
		Vector4 GetRotation() const;
	};
}