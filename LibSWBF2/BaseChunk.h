#pragma once
#include "stdafx.h"

namespace LibSWBF2
{
	namespace HeaderNames
	{
		constexpr int32_t str2int(const char* str)
		{
			return *(int32_t*)str;
		}

		string int2str(const int32_t& hedr)
		{
			return string((char*)&hedr);
		}

		static const int32_t HEDR = str2int("HEDR");
		static const int32_t SHVO = str2int("SHVO");
		static const int32_t MSH2 = str2int("MSH2");
		static const int32_t SINF = str2int("SINF");
		static const int32_t NAME = str2int("NAME");
		static const int32_t FRAM = str2int("FRAM");
		static const int32_t BBOX = str2int("BBOX");
		static const int32_t CAMR = str2int("CAMR");
		static const int32_t NAME = str2int("NAME");
		static const int32_t DATA = str2int("DATA");
		static const int32_t MATL = str2int("MATL");
		static const int32_t MATD = str2int("MATD");
		static const int32_t ATRB = str2int("ATRB");
		static const int32_t TX0D = str2int("TX0D");
		static const int32_t TX1D = str2int("TX1D");
		static const int32_t MODL = str2int("MODL");
		static const int32_t MTYP = str2int("MTYP");
		static const int32_t MNDX = str2int("MNDX");
		static const int32_t PRNT = str2int("PRNT");
		static const int32_t FLGS = str2int("FLGS");
		static const int32_t TRAN = str2int("TRAN");
		static const int32_t GEOM = str2int("GEOM");
		static const int32_t SEGM = str2int("SEGM");
		static const int32_t SHDW = str2int("SHDW");
		static const int32_t MATI = str2int("MATI");
		static const int32_t POSL = str2int("POSL");
		static const int32_t CLRL = str2int("CLRL");
		static const int32_t CLRB = str2int("CLRB");
		static const int32_t WGHT = str2int("WGHT");
		static const int32_t NRML = str2int("NRML");
		static const int32_t UV0L = str2int("UV0L");
		static const int32_t NDXL = str2int("NDXL");
		static const int32_t NDXT = str2int("NDXT");
		static const int32_t STRP = str2int("STRP");
		static const int32_t CLTH = str2int("CLTH");
		static const int32_t CPOS = str2int("CPOS");
		static const int32_t CUV0 = str2int("CUV0");
		static const int32_t FIDX = str2int("FIDX");
		static const int32_t FWGT = str2int("FWGT");
		static const int32_t CMSH = str2int("CMSH");
		static const int32_t SPRS = str2int("SPRS");
		static const int32_t CPRS = str2int("CPRS");
		static const int32_t BPRS = str2int("BPRS");
		static const int32_t COLL = str2int("COLL");
		static const int32_t ENVL = str2int("ENVL");
		static const int32_t SWCI = str2int("SWCI");
		static const int32_t BLN2 = str2int("BLN2");
		static const int32_t SKL2 = str2int("SKL2");
		static const int32_t ANM2 = str2int("ANM2");
		static const int32_t CYCL = str2int("CYCL");
		static const int32_t KFR3 = str2int("KFR3");
		static const int32_t CL1L = str2int("CL1L");
	}

	struct BaseChunk
	{
		BaseChunk();
		~BaseChunk();

		static int32_t PeekHeader(ifstream& stream);

		virtual void WriteToStream(ofstream& stream);
		virtual void ReadFromStream(ifstream& stream);

		int32_t GetHeader();
		int32_t GetSize();

	private:
		// since these variables are critical
		// we should keep them private
		int32_t Header;
		int32_t Size;
	};
}