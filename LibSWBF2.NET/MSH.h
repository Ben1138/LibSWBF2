#pragma once
#include "ManagedObject.h"

namespace LibSWBF2NET::Chunks::Mesh
{
	typedef LibSWBF2::Chunks::Mesh::MSH NativeMSH;

	public ref class MSH : ManagedObject<NativeMSH>
	{
		MSH();
	};
}