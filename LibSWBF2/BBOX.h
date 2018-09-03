#pragma once
#include "BaseChunk.h"
#include "Vector4.h"

namespace LibSWBF2::Chunks::MSH
{
	using LibSWBF2::Types::Vector2;
	using LibSWBF2::Types::Vector3;
	using LibSWBF2::Types::Vector4;

	struct BBOX : public BaseChunk
	{
		BBOX();
		~BBOX();

		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

	private:
		Vector4 Quaternion;
		Vector3 Center;
		Vector3 Extent;
		float_t SphereRadius;
	};
}