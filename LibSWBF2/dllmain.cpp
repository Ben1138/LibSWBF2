#include "pch.h"

#ifdef WIN32
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
#ifdef LOOKUP_CSV_PATH
        LibSWBF2::FNV::ReadLookupTable();
#endif // LOOKUP_CSV_PATH
        break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
#ifdef LOOKUP_CSV_PATH
        LibSWBF2::FNV::ReleaseLookupTable();
#endif // LOOKUP_CSV_PATH
        break;
    }
    return TRUE;
}

#endif