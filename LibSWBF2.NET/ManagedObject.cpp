#include "stdafx.h"
#include "ManagedObject.h"

using namespace Runtime::InteropServices;

namespace LibSWBF2NET
{

	std::string MarshalString(String^ managed)
	{
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(managed)).ToPointer();
		std::string str = std::string(chars);
		Marshal::FreeHGlobal(IntPtr((void*)chars));
		return str;
	}

	String^ MarshalString(std::string unmanaged)
	{
		return gcnew String(unmanaged.c_str());
	}
}