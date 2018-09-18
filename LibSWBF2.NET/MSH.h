#pragma once
#include "ManagedObject.h"

namespace LibSWBF2NET::Mesh
{
	typedef LibSWBF2::Chunks::Mesh::MSH NativeMSH;

	public ref class MSH : ManagedObject<NativeMSH>
	{
	public:
		MSH();

		property int ShadowVolume
		{
			int get()
			{
				return GetInstance()->m_SHVO.GetShadowVolume();
			}
		}
	};
}