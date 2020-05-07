#include "stdafx.h"
#include "HeaderNames.h"
#include <set>

namespace LibSWBF2::Chunks::HeaderNames
{
	string GetHeaderString(const ChunkHeader& hedr)
	{
		if (hedr == 0)
		{
			return "EMPTY";
		}
		else
		{
			// just passing the hedr address will result 
			// in an arbitrary string length, we need to
			// zero terminate it
			char arr[5];
			arr[4] = 0;
			memcpy(arr, &hedr, 4);
			return string(arr);
		}
	}

	bool IsValidHeader(const ChunkHeader hedr)
	{
		auto checkChar = [](char c)
		{
			return
				(c >= 48 && c <= 57) ||		// is a number
				(c >= 65 && c <= 90) ||		// is an uppercase letter
				(c >= 97 && c <= 122) ||	// is an lowercase letter
				(c == 95);					// is an underscore _
		};

		char* raw = (char*)&hedr;
		return
			checkChar(raw[0]) &&
			checkChar(raw[1]) &&
			checkChar(raw[2]) &&
			checkChar(raw[3]);
	}

	bool IsKnownHeader(const ChunkHeader hedr)
	{
		return
			// MSH / LVL
			hedr == HEDR ||
			hedr == SHVO ||
			hedr == MSH2 ||
			hedr == SINF ||
			hedr == NAME ||
			hedr == FRAM ||
			hedr == BBOX ||
			hedr == CAMR ||
			hedr == DATA ||
			hedr == MATL ||
			hedr == MATD ||
			hedr == ATRB ||
			hedr == TX0D ||
			hedr == TX1D ||
			hedr == TX2D ||
			hedr == TX3D ||
			hedr == MODL ||
			hedr == MTYP ||
			hedr == MNDX ||
			hedr == PRNT ||
			hedr == FLGS ||
			hedr == TRAN ||
			hedr == GEOM ||
			hedr == SEGM ||
			hedr == SHDW ||
			hedr == MATI ||
			hedr == POSL ||
			hedr == CLRL ||
			hedr == CLRB ||
			hedr == WGHT ||
			hedr == NRML ||
			hedr == UV0L ||
			hedr == NDXL ||
			hedr == NDXT ||
			hedr == STRP ||
			hedr == CLTH ||
			hedr == CPOS ||
			hedr == CUV0 ||
			hedr == FIDX ||
			hedr == FWGT ||
			hedr == CMSH ||
			hedr == SPRS ||
			hedr == CPRS ||
			hedr == BPRS ||
			hedr == COLL ||
			hedr == ENVL ||
			hedr == SWCI ||
			hedr == BLN2 ||
			hedr == SKL2 ||
			hedr == ANM2 ||
			hedr == CYCL ||
			hedr == KFR3 ||
			hedr == CL1L ||

			// Terrain
			hedr == TERR ||

			// LVL
			hedr == LVL_ ||
			hedr == ucfb ||
			hedr == mcfg ||
			hedr == scr_ ||
			hedr == INFO ||
			hedr == BODY ||
			hedr == SCOP ||
			hedr == skel ||
			hedr == XFRM ||
			hedr == VRTX ||
			hedr == SKY_ ||
			hedr == RTYP ||
			hedr == TNAM ||
			hedr == VBUF ||
			hedr == IBUF ||
			hedr == DXT1 ||
			hedr == DXT3 ||
			hedr == MTRL ||
			hedr == PROP ||
			hedr == BNAM ||
			hedr == NODE ||
			hedr == LEAF ||
			hedr == GSHD ||
			hedr == LOWD ||
			hedr == FMT_ ||
			hedr == FACE ||
			hedr == TYPE ||
			hedr == SPHR ||
			hedr == gmod ||

			// LVL - odf
			hedr == wpnc ||
			hedr == entc ||
			hedr == ordc ||
			hedr == expc ||

			// LVL - msh
			hedr == modl;
	}
}