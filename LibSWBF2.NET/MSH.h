#pragma once
#include "ManagedObject.h"

namespace LibSWBF2NET::Mesh
{
	typedef LibSWBF2::Chunks::Mesh::MSH NativeMSH;

	public ref class MSH : ManagedObject<NativeMSH>
	{
	public:
		MSH();

		bool WriteToFile(String^ Path)
		{
			return GetInstance()->WriteToFile(MarshalString(Path));
		}

		bool ReadFromFile(String^ Path)
		{
			return GetInstance()->ReadFromFile(MarshalString(Path));
		}

		property int ShadowVolume
		{
			int get()
			{
				return GetInstance()->m_SHVO.GetShadowVolume();
			}
		}
	};
}