#include "pch.h"
#include "HeaderNames.h"
#include "Types/LibString.h"
#include "Hashing.h"
#include <set>
#include <array>
#include <map>
#include <string>

namespace LibSWBF2
{
	const std::map<ChunkHeader, std::string> KNOWN_SOUND_HEADERS = 
	{
		{"StreamList"_fnvh, 	"StreamList"},
		{"Stream"_fnvh, 		"Stream"},
		{"Info"_fnvh, 			"Info"},
		{"SoundBankList"_fnvh, 	"SoundBankList"},
	};

	const std::set<ChunkHeader> KNOWN_GENERIC_HEADERS =
	{
		"HEDR"_h, "SHVO"_h, "MSH2"_h, "SINF"_h, "NAME"_h, "FRAM"_h, "BBOX"_h, "CAMR"_h,
		"DATA"_h, "MATL"_h, "MATD"_h, "ATRB"_h, "TX0D"_h, "TX1D"_h, "TX2D"_h, "TX3D"_h,
		"MODL"_h, "MTYP"_h, "MNDX"_h, "PRNT"_h, "FLGS"_h, "TRAN"_h, "GEOM"_h, "SEGM"_h,
		"SHDW"_h, "MATI"_h, "POSL"_h, "CLRL"_h, "CLRB"_h, "WGHT"_h, "NRML"_h, "UV0L"_h,
		"NDXL"_h, "NDXT"_h, "STRP"_h, "CLTH"_h, "CPOS"_h, "CUV0"_h, "FIDX"_h, "FWGT"_h,
		"CMSH"_h, "SPRS"_h, "CPRS"_h, "BPRS"_h, "COLL"_h, "ENVL"_h, "SWCI"_h, "BLN2"_h,
		"SKL2"_h, "ANM2"_h, "CYCL"_h, "KFR3"_h, "CL1L"_h, "TERR"_h, "LVL_"_h, "lvl_"_h,
		"ucfb"_h, "mcfg"_h, "INFO"_h, "BODY"_h, "SCOP"_h, "XFRM"_h, "VRTX"_h, "SKY_"_h,
		"RTYP"_h, "TNAM"_h, "VBUF"_h, "IBUF"_h, "DXT1"_h, "DXT3"_h, "MTRL"_h, "PROP"_h,
		"BNAM"_h, "NODE"_h, "LEAF"_h, "GSHD"_h, "LOWD"_h, "BASE"_h, "TYPE"_h, "SPHR"_h,
		"ARCS"_h, "path"_h, "port"_h, "comb"_h, "sanm"_h, "hud_"_h, "gmod"_h, "plnp"_h,
		"SHDV"_h, "SHDI"_h, "LPTC"_h, "LUMI"_h, "PCHS"_h, "PTCH"_h, "FLAG"_h, "MASK"_h,
		"ROTN"_h, "COMN"_h, "HEXP"_h, "HGT8"_h, "LTEX"_h, "SCAL"_h, "AXIS"_h, "SNAM"_h,
		"BARR"_h, "DTEX"_h, "DTLX"_h, "PLNS"_h, "CUTR"_h, "FOLG"_h, "SIZE"_h, "CUTS"_h,
		"POSI"_h, "CSHD"_h, "TREE"_h, "LOWR"_h, "DCAL"_h, "tex_"_h, "FMT_"_h, "FACE"_h,
		"wpnc"_h, "entc"_h, "ordc"_h, "expc"_h, "fx__"_h, "wrld"_h, "sky_"_h, "bnd_"_h,
		"lght"_h, "plan"_h, "PATH"_h, "tern"_h, "modl"_h, "segm"_h, "skel"_h, "coll"_h,
		"prim"_h, "Locl"_h, "scr_"_h, "SHDR"_h, "LOD0"_h, "font"_h, "zaa_"_h, "zaf_"_h,
		"prp_"_h, "bnd_"_h, "regn"_h, "BARR"_h, "GRGR"_h, "shdw"_h, "Hint"_h, "inst"_h,
		"BIN_"_h, "FFAZ"_h, "SREV"_h, "EZIS"_h, "SLTM"_h, "LTAM"_h, "STSJ"_h, "SNKS"_h,
		"NIKS"_h, "LEKS"_h, "TNOJ"_h, "SYXP"_h, "SDHS"_h, "SMNA"_h, "MINA"_h, "TNJA"_h,
		"TADA"_h, "emo_"_h, "_pad"_h, "snd_"_h
	};

	bool ChunkHeader::operator==(const ChunkHeader other) const
	{
		return m_Magic == other.m_Magic;
	}

	bool ChunkHeader::operator!=(const ChunkHeader other) const
	{
		return m_Magic != other.m_Magic;
	}

	bool ChunkHeader::operator<(const ChunkHeader other) const
	{
		return m_Magic < other.m_Magic;
	}

	bool ChunkHeader::operator>(const ChunkHeader other) const
	{
		return m_Magic > other.m_Magic;
	}

	Types::String ChunkHeader::ToString() const
	{
		auto soundLookup = KNOWN_SOUND_HEADERS.find(*this);
		if (soundLookup != KNOWN_SOUND_HEADERS.end())
		{
			return soundLookup -> second.c_str();
		}

		if (!IsValidHeader(*this))
		{
			std::string tstResult = fmt::format("0x{0:x}", m_Magic);
			return tstResult.c_str();
		}
		else 
		{
			std::string result;
			result += m_Name[0];
			result += m_Name[1];
			result += m_Name[2];
			result += m_Name[3];
			return result.c_str();
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

		return
			checkChar(hedr.m_Name[0]) &&
			checkChar(hedr.m_Name[1]) &&
			checkChar(hedr.m_Name[2]) &&
			checkChar(hedr.m_Name[3]);
	}

	bool IsKnownHeader(const ChunkHeader hedr)
	{
		return (KNOWN_GENERIC_HEADERS.find(hedr) != KNOWN_GENERIC_HEADERS.end()) || (KNOWN_SOUND_HEADERS.find(hedr) != KNOWN_SOUND_HEADERS.end());
	}
}