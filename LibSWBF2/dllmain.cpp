#include "stdafx.h"

#ifdef _WIN32


#include "Hashing.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        LibSWBF2::FNV::ReadLookupTable();
        break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        LibSWBF2::FNV::ReleaseLookupTable();
        break;
    }
    return TRUE;
}

#endif