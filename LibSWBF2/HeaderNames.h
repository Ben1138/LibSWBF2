#pragma once
#include "stdafx.h"

namespace LibSWBF2::Chunks::HeaderNames
{
	constexpr int32_t HeaderToInt(const char* str)
	{
		return *(int32_t*)str;
	}

	static string IntToHeader(const int32_t& hedr)
	{
		return string((char*)&hedr);
	}

	const int32_t HEDR = HeaderToInt("HEDR");
	const int32_t SHVO = HeaderToInt("SHVO");
	const int32_t MSH2 = HeaderToInt("MSH2");
	const int32_t SINF = HeaderToInt("SINF");
	const int32_t NAME = HeaderToInt("NAME");
	const int32_t FRAM = HeaderToInt("FRAM");
	const int32_t BBOX = HeaderToInt("BBOX");
	const int32_t CAMR = HeaderToInt("CAMR");
	const int32_t DATA = HeaderToInt("DATA");
	const int32_t MATL = HeaderToInt("MATL");
	const int32_t MATD = HeaderToInt("MATD");
	const int32_t ATRB = HeaderToInt("ATRB");
	const int32_t TX0D = HeaderToInt("TX0D");
	const int32_t TX1D = HeaderToInt("TX1D");
	const int32_t MODL = HeaderToInt("MODL");
	const int32_t MTYP = HeaderToInt("MTYP");
	const int32_t MNDX = HeaderToInt("MNDX");
	const int32_t PRNT = HeaderToInt("PRNT");
	const int32_t FLGS = HeaderToInt("FLGS");
	const int32_t TRAN = HeaderToInt("TRAN");
	const int32_t GEOM = HeaderToInt("GEOM");
	const int32_t SEGM = HeaderToInt("SEGM");
	const int32_t SHDW = HeaderToInt("SHDW");
	const int32_t MATI = HeaderToInt("MATI");
	const int32_t POSL = HeaderToInt("POSL");
	const int32_t CLRL = HeaderToInt("CLRL");
	const int32_t CLRB = HeaderToInt("CLRB");
	const int32_t WGHT = HeaderToInt("WGHT");
	const int32_t NRML = HeaderToInt("NRML");
	const int32_t UV0L = HeaderToInt("UV0L");
	const int32_t NDXL = HeaderToInt("NDXL");
	const int32_t NDXT = HeaderToInt("NDXT");
	const int32_t STRP = HeaderToInt("STRP");
	const int32_t CLTH = HeaderToInt("CLTH");
	const int32_t CPOS = HeaderToInt("CPOS");
	const int32_t CUV0 = HeaderToInt("CUV0");
	const int32_t FIDX = HeaderToInt("FIDX");
	const int32_t FWGT = HeaderToInt("FWGT");
	const int32_t CMSH = HeaderToInt("CMSH");
	const int32_t SPRS = HeaderToInt("SPRS");
	const int32_t CPRS = HeaderToInt("CPRS");
	const int32_t BPRS = HeaderToInt("BPRS");
	const int32_t COLL = HeaderToInt("COLL");
	const int32_t ENVL = HeaderToInt("ENVL");
	const int32_t SWCI = HeaderToInt("SWCI");
	const int32_t BLN2 = HeaderToInt("BLN2");
	const int32_t SKL2 = HeaderToInt("SKL2");
	const int32_t ANM2 = HeaderToInt("ANM2");
	const int32_t CYCL = HeaderToInt("CYCL");
	const int32_t KFR3 = HeaderToInt("KFR3");
	const int32_t CL1L = HeaderToInt("CL1L");
}