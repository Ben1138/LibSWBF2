#include "stdafx.h"
#include "MSH.h"

namespace LibSWBF2NET::Mesh
{
	MSH::MSH()
	{
		msh = NativeMSH::Create();
	}

	MSH::~MSH()
	{
		this->!MSH();
	}

	MSH::!MSH()
	{
		if (msh != nullptr)
		{
			NativeMSH::Destroy(msh);
		}
	}

	bool MSH::WriteToFile(String^ Path)
	{
		return msh->WriteToFile(MarshalString(Path));
	}

	bool MSH::ReadFromFile(String^ Path)
	{
		return msh->ReadFromFile(MarshalString(Path));
	}

	int MSH::ShadowVolume::get()
	{
		return msh->m_ShadowVolume.m_ShadowVolume;
	}
}