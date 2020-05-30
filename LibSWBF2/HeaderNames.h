#pragma once
#include "stdafx.h"
#include <set>

namespace LibSWBF2::Chunks::HeaderNames
{
	constexpr ChunkHeader GetHeaderValue(const char* str)
	{
		return *(ChunkHeader*)str;
	}

	string GetHeaderString(const ChunkHeader& hedr);
	bool IsValidHeader(const ChunkHeader hedr);
	bool IsKnownHeader(const ChunkHeader hedr);

	const ChunkHeader EMPTY = 0;

	// MSH / LVL
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

	// Terrain
	const ChunkHeader TERR = GetHeaderValue("TERR");

	// LVL
	const ChunkHeader LVL_ = GetHeaderValue("LVL_");
	const ChunkHeader ucfb = GetHeaderValue("ucfb");
	const ChunkHeader mcfg = GetHeaderValue("mcfg");
	const ChunkHeader scr_ = GetHeaderValue("scr_");
	const ChunkHeader INFO = GetHeaderValue("INFO");
	const ChunkHeader BODY = GetHeaderValue("BODY");
	const ChunkHeader SCOP = GetHeaderValue("SCOP");
	const ChunkHeader skel = GetHeaderValue("skel");
	const ChunkHeader XFRM = GetHeaderValue("XFRM");
	const ChunkHeader VRTX = GetHeaderValue("VRTX");
	const ChunkHeader SKY_ = GetHeaderValue("SKY_");
	const ChunkHeader RTYP = GetHeaderValue("RTYP");
	const ChunkHeader TNAM = GetHeaderValue("TNAM");
	const ChunkHeader VBUF = GetHeaderValue("VBUF");
	const ChunkHeader IBUF = GetHeaderValue("IBUF");
	const ChunkHeader DXT1 = GetHeaderValue("DXT1");
	const ChunkHeader DXT3 = GetHeaderValue("DXT3");
	const ChunkHeader MTRL = GetHeaderValue("MTRL");
	const ChunkHeader PROP = GetHeaderValue("PROP");
	const ChunkHeader BNAM = GetHeaderValue("BNAM");
	const ChunkHeader NODE = GetHeaderValue("NODE");
	const ChunkHeader LEAF = GetHeaderValue("LEAF");
	const ChunkHeader GSHD = GetHeaderValue("GSHD");
	const ChunkHeader LOWD = GetHeaderValue("LOWD");
	const ChunkHeader TYPE = GetHeaderValue("TYPE");
	const ChunkHeader SPHR = GetHeaderValue("SPHR");
	const ChunkHeader gmod = GetHeaderValue("gmod");

	// LVL - texture
	const ChunkHeader tex_ = GetHeaderValue("tex_");
	const ChunkHeader FMT_ = GetHeaderValue("FMT_");
	const ChunkHeader FACE = GetHeaderValue("FACE");

	// LVL - odf
	const ChunkHeader wpnc = GetHeaderValue("wpnc");
	const ChunkHeader entc = GetHeaderValue("entc");
	const ChunkHeader ordc = GetHeaderValue("ordc");
	const ChunkHeader expc = GetHeaderValue("expc");

	// LVL - msh
	const ChunkHeader modl = GetHeaderValue("modl");
}

#define ASSERT_HEADER(a, b) if (a != b) LOG("Expected '"+LibSWBF2::Chunks::HeaderNames::GetHeaderString(b)+"' but got '"+LibSWBF2::Chunks::HeaderNames::GetHeaderString(a)+"'", ELogType::Error);