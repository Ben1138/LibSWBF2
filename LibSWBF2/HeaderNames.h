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
	const ChunkHeader lvl_ = GetHeaderValue("lvl_");
	const ChunkHeader ucfb = GetHeaderValue("ucfb");
	const ChunkHeader mcfg = GetHeaderValue("mcfg");
	const ChunkHeader INFO = GetHeaderValue("INFO");
	const ChunkHeader BODY = GetHeaderValue("BODY");
	const ChunkHeader SCOP = GetHeaderValue("SCOP");
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
	const ChunkHeader BASE = GetHeaderValue("BASE");
	const ChunkHeader TYPE = GetHeaderValue("TYPE");
	const ChunkHeader SPHR = GetHeaderValue("SPHR");
	const ChunkHeader ARCS = GetHeaderValue("ARCS");
	const ChunkHeader path = GetHeaderValue("path");
	const ChunkHeader port = GetHeaderValue("port");
	const ChunkHeader comb = GetHeaderValue("comb");
	const ChunkHeader sanm = GetHeaderValue("sanm");
	const ChunkHeader hud_ = GetHeaderValue("hud_");
	const ChunkHeader gmod = GetHeaderValue("gmod");
	const ChunkHeader plnp = GetHeaderValue("plnp");
	const ChunkHeader SHDV = GetHeaderValue("SHDV");
	const ChunkHeader SHDI = GetHeaderValue("SHDI");
	const ChunkHeader LPTC = GetHeaderValue("LPTC");
	const ChunkHeader LUMI = GetHeaderValue("LUMI");
	const ChunkHeader PCHS = GetHeaderValue("PCHS");
	const ChunkHeader PTCH = GetHeaderValue("PTCH");
	const ChunkHeader FLAG = GetHeaderValue("FLAG");
	const ChunkHeader MASK = GetHeaderValue("MASK");
	const ChunkHeader ROTN = GetHeaderValue("ROTN");
	const ChunkHeader COMN = GetHeaderValue("COMN");
	const ChunkHeader HEXP = GetHeaderValue("HEXP");
	const ChunkHeader HGT8 = GetHeaderValue("HGT8");
	const ChunkHeader LTEX = GetHeaderValue("LTEX");
	const ChunkHeader SCAL = GetHeaderValue("SCAL");
	const ChunkHeader AXIS = GetHeaderValue("AXIS");
	const ChunkHeader SNAM = GetHeaderValue("SNAM");
	const ChunkHeader BARR = GetHeaderValue("BARR");
	const ChunkHeader DTEX = GetHeaderValue("DTEX");
	const ChunkHeader DTLX = GetHeaderValue("DTLX");
	const ChunkHeader PLNS = GetHeaderValue("PLNS");
	const ChunkHeader CUTR = GetHeaderValue("CUTR");
	const ChunkHeader FOLG = GetHeaderValue("FOLG");
	const ChunkHeader SIZE = GetHeaderValue("SIZE");
	const ChunkHeader CUTS = GetHeaderValue("CUTS");
	const ChunkHeader POSI = GetHeaderValue("POSI");
	const ChunkHeader CSHD = GetHeaderValue("CSHD");
	const ChunkHeader TREE = GetHeaderValue("TREE");
	const ChunkHeader LOWR = GetHeaderValue("LOWR");
	const ChunkHeader DCAL = GetHeaderValue("DCAL");

	// LVL - texture
	const ChunkHeader tex_ = GetHeaderValue("tex_");
	const ChunkHeader FMT_ = GetHeaderValue("FMT_");
	const ChunkHeader FACE = GetHeaderValue("FACE");

	// LVL - odf
	const ChunkHeader wpnc = GetHeaderValue("wpnc");
	const ChunkHeader entc = GetHeaderValue("entc");
	const ChunkHeader ordc = GetHeaderValue("ordc");
	const ChunkHeader expc = GetHeaderValue("expc");

	// LVL - effects (fx)
	const ChunkHeader fx__ = GetHeaderValue("fx__");

	// LVL - world
	const ChunkHeader wrld = GetHeaderValue("wrld");
	const ChunkHeader sky_ = GetHeaderValue("sky_");
	const ChunkHeader bnd_ = GetHeaderValue("bnd_");
	const ChunkHeader lght = GetHeaderValue("lght");
	const ChunkHeader plan = GetHeaderValue("plan");
	const ChunkHeader PATH = GetHeaderValue("PATH");
	const ChunkHeader tern = GetHeaderValue("tern");

	// LVL - model
	const ChunkHeader modl = GetHeaderValue("modl");
	const ChunkHeader segm = GetHeaderValue("segm");
	const ChunkHeader skel = GetHeaderValue("skel");
	const ChunkHeader coll = GetHeaderValue("coll");
	const ChunkHeader prim = GetHeaderValue("prim");
	const ChunkHeader Locl = GetHeaderValue("Locl");
	const ChunkHeader scr_ = GetHeaderValue("scr_");
	const ChunkHeader SHDR = GetHeaderValue("SHDR");
	const ChunkHeader LOD0 = GetHeaderValue("LOD0");
	const ChunkHeader font = GetHeaderValue("font");
	const ChunkHeader zaa_ = GetHeaderValue("zaa_");
	const ChunkHeader zaf_ = GetHeaderValue("zaf_");
}

#define ASSERT_HEADER(a, b) if (a != b) LOG("Expected '"+LibSWBF2::Chunks::HeaderNames::GetHeaderString(b)+"' but got '"+LibSWBF2::Chunks::HeaderNames::GetHeaderString(a)+"'", ELogType::Error);