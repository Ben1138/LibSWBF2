#pragma once
#include "stdafx.h"

namespace LibSWBF2::Chunks::HeaderNames
{
	constexpr ChunkHeader GetHeaderValue(const char* str)
	{
		return *(ChunkHeader*)str;
	}

	static string GetHeaderString(const ChunkHeader& hedr)
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

	const ChunkHeader HEDR = GetHeaderValue("HEDR");
	const ChunkHeader SHVO = GetHeaderValue("SHVO");
	const ChunkHeader MSH2 = GetHeaderValue("MSH2");
	const ChunkHeader SINF = GetHeaderValue("SINF");
	const ChunkHeader NAME = GetHeaderValue("NAME");
	const ChunkHeader FRAM = GetHeaderValue("FRAM");
	const ChunkHeader BBOX = GetHeaderValue("BBOX");
	const ChunkHeader CAMR = GetHeaderValue("CAMR");
	const ChunkHeader DATA = GetHeaderValue("DATA");
	const ChunkHeader MATL = GetHeaderValue("MATL");
	const ChunkHeader MATD = GetHeaderValue("MATD");
	const ChunkHeader ATRB = GetHeaderValue("ATRB");
	const ChunkHeader TX0D = GetHeaderValue("TX0D");
	const ChunkHeader TX1D = GetHeaderValue("TX1D");
	const ChunkHeader TX2D = GetHeaderValue("TX2D");
	const ChunkHeader TX3D = GetHeaderValue("TX3D");
	const ChunkHeader MODL = GetHeaderValue("MODL");
	const ChunkHeader MTYP = GetHeaderValue("MTYP");
	const ChunkHeader MNDX = GetHeaderValue("MNDX");
	const ChunkHeader PRNT = GetHeaderValue("PRNT");
	const ChunkHeader FLGS = GetHeaderValue("FLGS");
	const ChunkHeader TRAN = GetHeaderValue("TRAN");
	const ChunkHeader GEOM = GetHeaderValue("GEOM");
	const ChunkHeader SEGM = GetHeaderValue("SEGM");
	const ChunkHeader SHDW = GetHeaderValue("SHDW");
	const ChunkHeader MATI = GetHeaderValue("MATI");
	const ChunkHeader POSL = GetHeaderValue("POSL");
	const ChunkHeader CLRL = GetHeaderValue("CLRL");
	const ChunkHeader CLRB = GetHeaderValue("CLRB");
	const ChunkHeader WGHT = GetHeaderValue("WGHT");
	const ChunkHeader NRML = GetHeaderValue("NRML");
	const ChunkHeader UV0L = GetHeaderValue("UV0L");
	const ChunkHeader NDXL = GetHeaderValue("NDXL");
	const ChunkHeader NDXT = GetHeaderValue("NDXT");
	const ChunkHeader STRP = GetHeaderValue("STRP");
	const ChunkHeader CLTH = GetHeaderValue("CLTH");
	const ChunkHeader CPOS = GetHeaderValue("CPOS");
	const ChunkHeader CUV0 = GetHeaderValue("CUV0");
	const ChunkHeader FIDX = GetHeaderValue("FIDX");
	const ChunkHeader FWGT = GetHeaderValue("FWGT");
	const ChunkHeader CMSH = GetHeaderValue("CMSH");
	const ChunkHeader SPRS = GetHeaderValue("SPRS");
	const ChunkHeader CPRS = GetHeaderValue("CPRS");
	const ChunkHeader BPRS = GetHeaderValue("BPRS");
	const ChunkHeader COLL = GetHeaderValue("COLL");
	const ChunkHeader ENVL = GetHeaderValue("ENVL");
	const ChunkHeader SWCI = GetHeaderValue("SWCI");
	const ChunkHeader BLN2 = GetHeaderValue("BLN2");
	const ChunkHeader SKL2 = GetHeaderValue("SKL2");
	const ChunkHeader ANM2 = GetHeaderValue("ANM2");
	const ChunkHeader CYCL = GetHeaderValue("CYCL");
	const ChunkHeader KFR3 = GetHeaderValue("KFR3");
	const ChunkHeader CL1L = GetHeaderValue("CL1L");
}