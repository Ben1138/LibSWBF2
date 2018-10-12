#pragma once
#include "ManagedObject.h"

namespace LibSWBF2NET::Mesh
{
	typedef LibSWBF2::Chunks::Mesh::MSH NativeMSH;

	public ref class MSH
	{
	private:
		NativeMSH* msh;

	public:
		MSH();
		~MSH();
		!MSH();

		bool WriteToFile(String^ Path);
		bool ReadFromFile(String^ Path);
		property int ShadowVolume { int get(); };
	};
}