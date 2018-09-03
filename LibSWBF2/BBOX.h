#pragma once
#include "BaseChunk.h"
#include "Vector4.h"

namespace LibSWBF2::Chunks::MSH
{
	using Types::Vector3;
	using Types::Vector4;

	struct BBOX : public BaseChunk
	{
		BBOX();
		~BBOX();

		void RefreshSize() override;
		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

	private:
		Vector4 Quaternion;
		Vector3 Center;
		Vector3 Extent;
		float_t SphereRadius;
	};
}