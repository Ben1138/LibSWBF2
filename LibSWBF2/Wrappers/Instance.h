#pragma once
#include "req.h"
#include "Types/Vector4.h"
#include "Types/List.h"
#include "Chunks/LVL/wrld/inst.h"

namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Chunks::LVL::wrld::inst;
	using Types::Vector3;
	using Types::Vector4;
	using Types::List;

	class Level;
	class World;

	class LIBSWBF2_API Instance
	{
	private:
		friend World;
		friend List<Instance>;

		Instance() = default;
		~Instance() = default;

	private:
		inst* p_Instance;

	public:
		static bool FromChunk(Level* mainContainer, inst* instanceChunk, Instance& out);

		Types::String GetType() const;
		Types::String GetName() const;
		Vector3 GetPosition() const;
		Vector4 GetRotation() const;
	};
}