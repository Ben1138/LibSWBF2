#include "stdafx.h"
#include "GenericChunk.h"
#include "Exceptions.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Logging/Logger.h"
#include "LVL/tex_/tex_.h"
#include "LVL/modl/LVL.modl.h"
#include "LVL/wrld/wrld.h"
#include "LVL/tern/tern.h"
#include "LVL/scr_/scr_.h"
#include "LVL/zaa_/zaa_.h"
#include "LVL/lvl_.h"

namespace LibSWBF2::Chunks
{
	GenericBaseChunk::~GenericBaseChunk()
	{
		for (size_t i = 0; i < m_Children.Size(); ++i)
		{
			delete m_Children[i];
		}
	}

	template<uint32_t Header>
	void GenericChunk<Header>::Check(FileReader& stream)
	{
		// check for correct header
		ChunkHeader expected;
		expected.m_Magic = Header;
		if (Header != 0 && m_Header != expected)
		{
			LOG_ERROR("Expected '{}' but got '{}'", expected, m_Header);
			throw InvalidHeaderException(m_Header);
		}

		// check if current "chunk" exceeds parents data size
		GenericBaseChunk* parent = GetParent();
		if (parent != nullptr && (stream.GetPosition() + m_Size) > (parent->GetDataPosition() + parent->GetDataSize()))
		{
			throw InvalidSizeException(m_Size);
		}
	}

	template<uint32_t Header>
	void GenericChunk<Header>::RefreshSize()
	{
		throw LibException("Not implemented!");
	}

	template<uint32_t Header>
	void GenericChunk<Header>::WriteToStream(FileWriter& stream)
	{
		throw LibException("Not implemented!");
	}

	void GenericBaseChunk::ReadGenerics(FileReader& stream)
	{
		while (ThereIsAnother(stream))
		{
			ChunkHeader nextHead = stream.ReadChunkHeader(true);
			if (IsKnownHeader(nextHead))
			//if (IsValidHeader(nextHead))
			{
				GenericBaseChunk* chunk = nullptr;
				try
				{
					if (nextHead == "NAME"_h)
					{
						STR<"NAME"_m>* name;
						READ_CHILD(stream, name);
						chunk = name;
					}
					else if (nextHead == "PRNT"_h)
					{
						// TODO: is PRNT really always just a string?
						STR<"PRNT"_m>* name;
						READ_CHILD(stream, name);
						chunk = name;
					}
					else if (nextHead == "tex_"_h)
					{
						LVL::texture::tex_* name;
						READ_CHILD(stream, name);
						chunk = name;
					}
					else if (nextHead == "modl"_h)
					{
						LVL::modl::modl* model;
						READ_CHILD(stream, model);
						chunk = model;
					}
					else if (nextHead == "lvl_"_h)
					{
						LVL::lvl_* subLVL;
						READ_CHILD(stream, subLVL);
						chunk = subLVL;
					}
					else if (nextHead == "wrld"_h)
					{
						LVL::wrld::wrld* world;
						READ_CHILD(stream, world);
						chunk = world;
					}
					else if (nextHead == "tern"_h)
					{
						LVL::terrain::tern* terrain;
						READ_CHILD(stream, terrain);
						chunk = terrain;
					}
					else if (nextHead == "scr_"_h)
					{
						LVL::script::scr_* script;
						READ_CHILD(stream, script);
						chunk = script;
					}
					else if (nextHead == "zaa_"_h)
					{
						LVL::animation::zaa_* zaabin;
						READ_CHILD(stream, zaabin);
						chunk = zaabin;
					}
					else
					{
						GenericChunkNC* generic;
						READ_CHILD(stream, generic);
						chunk = generic;
					}

					LOG_INFO("Adding Child '{}' to '{}'", chunk->GetHeader(), m_Header);
				}
				catch (InvalidSizeException&)
				{
					delete chunk;
					chunk = nullptr;

					LOG_ERROR("Skipping invalid Chunk: '{}' at pos: {}", nextHead, stream.GetPosition());
					break;
				}
			}
			else
			{
				break;
			}
		}
	}

	template<uint32_t Header>
	void GenericChunk<Header>::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);
		ReadGenerics(stream);
		BaseChunk::EnsureEnd(stream);
	}

	String GenericBaseChunk::GetHeaderName() const
	{
		return m_Header.ToString();
	}

	GenericBaseChunk* GenericBaseChunk::GetParent() const
	{
		return m_Parent;
	}

	const List<GenericBaseChunk*>& GenericBaseChunk::GetChildren() const
	{
		return m_Children;
	}

	String GenericBaseChunk::ToString()
	{
		return "No Info";
	}
}

// ============================================================
// ============== Explicit Chunk instantiations ===============
// ============================================================

namespace LibSWBF2::Chunks
{
	template LIBSWBF2_API struct GenericChunk<0>;
	template LIBSWBF2_API struct GenericChunk<"ucfb"_m>;
	template LIBSWBF2_API struct GenericChunk<"LVL_"_m>;
	template LIBSWBF2_API struct GenericChunk<"INFO"_m>;
	template LIBSWBF2_API struct GenericChunk<"TYPE"_m>;
	template LIBSWBF2_API struct GenericChunk<"BODY"_m>;
	template LIBSWBF2_API struct GenericChunk<"FACE"_m>;
	template LIBSWBF2_API struct GenericChunk<"FMT_"_m>;
	template LIBSWBF2_API struct GenericChunk<"tex_"_m>;
	template LIBSWBF2_API struct GenericChunk<"modl"_m>;
	template LIBSWBF2_API struct GenericChunk<"segm"_m>;
	template LIBSWBF2_API struct GenericChunk<"MTRL"_m>;
	template LIBSWBF2_API struct GenericChunk<"tern"_m>;
	template LIBSWBF2_API struct GenericChunk<"PCHS"_m>;
	template LIBSWBF2_API struct GenericChunk<"PTCH"_m>;
	template LIBSWBF2_API struct GenericChunk<"VBUF"_m>;
	template LIBSWBF2_API struct GenericChunk<"IBUF"_m>;
	template LIBSWBF2_API struct GenericChunk<"LTEX"_m>;
	template LIBSWBF2_API struct GenericChunk<"scr_"_m>;
	template LIBSWBF2_API struct GenericChunk<"zaa_"_m>;
	template LIBSWBF2_API struct GenericChunk<"BIN_"_m>;
	template LIBSWBF2_API struct GenericChunk<"SMNA_"_m>;

	// string chunks (see STR.cpp)
	template LIBSWBF2_API struct GenericChunk<"NAME"_m>;
	template LIBSWBF2_API struct GenericChunk<"TNAM"_m>;
	template LIBSWBF2_API struct GenericChunk<"SNAM"_m>;
	template LIBSWBF2_API struct GenericChunk<"TX0D"_m>;
	template LIBSWBF2_API struct GenericChunk<"TX1D"_m>;
	template LIBSWBF2_API struct GenericChunk<"TX2D"_m>;
	template LIBSWBF2_API struct GenericChunk<"TX3D"_m>;
	template LIBSWBF2_API struct GenericChunk<"PRNT"_m>;
	template LIBSWBF2_API struct GenericChunk<"NODE"_m>;
	template LIBSWBF2_API struct GenericChunk<"RTYP"_m>;
	template LIBSWBF2_API struct GenericChunk<"BNAM"_m>;
	template LIBSWBF2_API struct GenericChunk<"DTLX"_m>;
}