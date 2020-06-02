#include "stdafx.h"
#include "GenericChunk.h"
#include "Exceptions.h"
#include "LVL\tex_\tex_.h"
#include "LVL\modl\LVL.modl.h"

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
	void GenericChunk<Header>::RefreshSize()
	{
		throw std::runtime_error("Not implemented!");
	}

	template<uint32_t Header>
	void GenericChunk<Header>::WriteToStream(FileWriter& stream)
	{
		throw std::runtime_error("Not implemented!");
	}

	template<uint32_t Header>
	void GenericChunk<Header>::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		// check for correct header
		ChunkHeader expected;
		expected.m_Magic = Header;
		if (Header != 0 && m_Header != expected)
		{
			LOG("Expected '" + expected.ToString() + "' but got '" + m_Header.ToString() + "'", ELogType::Error);
			throw InvalidHeaderException(m_Header);
		}

		// check if current "chunk" exceeds parents data size
		GenericBaseChunk* parent = GetParent();
		if (parent != nullptr && (stream.GetPosition() + m_Size) > (parent->GetDataPosition() + parent->GetDataSize()))
		{
			throw InvalidSizeException(m_Size);
		}

		while (stream.GetFileSize() - stream.GetPosition() >= 4 && PositionInChunk(stream.GetPosition()))
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
					else if (nextHead == "tex_"_h)
					{
						LVL::tex_* name;
						READ_CHILD(stream, name);
						chunk = name;
					}
					else if (nextHead == "modl"_h)
					{
						LVL::modl::modl* model;
						READ_CHILD(stream, model);
						chunk = model;
					}
					else
					{
						GenericChunkNC* generic;
						READ_CHILD(stream, generic);
						chunk = generic;
					}

					LOG(string("Adding Child '") + chunk->GetHeader().ToString() + "' to '" + m_Header.ToString() + "'", ELogType::Info);
				}
				catch (InvalidSizeException& e)
				{
					e; // avoid C4101 warning

					if (chunk != nullptr)
					{
						delete chunk;
					}

					LOG("Skipping invalid Chunk: '" + nextHead.ToString() + "' at pos: " + std::to_string(stream.GetPosition()), ELogType::Error);
					break;
				}
			}
			else
			{
				break;
			}
		}

		BaseChunk::EnsureEnd(stream);
	}

	String GenericBaseChunk::GetHeaderName() const
	{
		return m_Header.ToString().c_str();
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
// ============== Explicit CHunk instantiations ===============
// ============================================================

namespace LibSWBF2::Chunks
{
	template LIBSWBF2_EXP struct GenericChunk<0>;
	template LIBSWBF2_EXP struct GenericChunk<"ucfb"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"LVL_"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"INFO"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"BODY"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"FACE"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"FMT_"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"tex_"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"modl"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"segm"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"MTRL"_m>;

	// string chunks (see STR.cpp)
	template LIBSWBF2_EXP struct GenericChunk<"NAME"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"TX0D"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"TX1D"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"TX2D"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"TX3D"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"PRNT"_m>;
	template LIBSWBF2_EXP struct GenericChunk<"NODE"_m>;
}