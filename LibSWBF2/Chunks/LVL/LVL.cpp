#include "stdafx.h"
#include "LVL.h"
#include "InternalHelpers.h"
#include "Hashing.h"
#include "FileReader.h"
#include "Chunks/HeaderNames.h"
#include <sstream>

namespace LibSWBF2::Chunks::LVL
{
	LVL* LVL::Create()
	{
		return new LVL();
	}

	void LVL::Destroy(LVL* lvl)
	{
		delete lvl;
	}

	void LVL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		size_t pos = stream.GetPosition();

		ChunkHeader next1 = stream.ReadChunkHeader(false);	// either next chunk header OR unknown value
		uint32_t	next2 = stream.ReadUInt32();			// either next chunk length OR size left
		ChunkHeader	next3 = stream.ReadChunkHeader(true);	// either some data / header OR "emo_" header

		// we assume to be in a Sound LVL file if there's no next chunk immediately
		// (unknown chunk header) AND after reading size left there's a "emo_" chunk
		m_IsSoundLVL = !IsKnownHeader(next1) && next3 == "emo_"_h;

		if (m_IsSoundLVL)
		{
			m_NameHash = next1.m_Magic;	// let's pretend we read a uint32 in the first place...
			m_SizeLeft = next2;
		}
		else
		{
			// all other LVL types (AFAIK)
			stream.SetPosition(pos);
		}

		ReadGenerics(stream);
		BaseChunk::EnsureEnd(stream);
	}

	bool LVL::ReadFromFile(String Path, const List<String>* subLVLsToLoad)
	{
		m_SubLVLsToLoad.Clear();

		// Loading a LVL file can be accompanied by additional parameters.
		// These parameters usually describe what sub LVLs to load (at least
		// I did not found no other purpose as I'm writing this), all other
		// sub LVL will be ignored.
		// If not a single parameter is specified, currently ALL sub LVL are loaded!
		if (subLVLsToLoad != nullptr)
		{
			for (size_t i = 0; i < subLVLsToLoad->Size(); ++i)
			{
				m_SubLVLsToLoad.Add(FNV::Hash((*subLVLsToLoad)[i]));
			}
		}
		
		// There seems to be another pattern to be used aswell, where
		// parameters are just concatenated to the path using ';' as delimiter
		std::vector<std::string> params;
		std::istringstream stream(Path.Buffer());
		std::string nextParam;
		for (bool first = true; std::getline(stream, nextParam, ';'); first = false)
		{
			if (first)
			{
				// first parameter is the actual path
				Path = nextParam.c_str();
			}
			else
			{
				// arguments
				params.push_back(nextParam);
			}
		}

		if (params.size() > 0)
		{
			for (std::string param : params)
			{
				m_SubLVLsToLoad.Add(FNV::Hash(param.c_str()));
			}
		}

		// Debug purposes only. Should be removed at some point
		if (params.size() > 1)
		{
			LOG_WARN("LVL Path contains more than one parameter! This is not expected... Research is needed!");

			std::string str;
			for (std::string param : params)
			{
				str += "\t" + param + "\n";
			}
			LOG_WARN("LVL Path parameters are: \n{}", str);
		}

		bool success = BaseChunk::ReadFromFile(Path);
		m_SubLVLsToLoad.Clear();
		return success;
	}

	String LVL::ToString()
	{
		std::string result = fmt::format("Sound LVL: {}", m_IsSoundLVL ? "Yes" : "No");
		if (m_IsSoundLVL)
		{
			String name;
			if (!FNV::Lookup(m_NameHash, name))
				name = std::to_string(m_NameHash).c_str();

			result += "\n" + fmt::format(
				"Name: {}\n"
				"Size Left: {}\n",
				name,
				m_SizeLeft
			);
		}
		return result.c_str();
	}
}