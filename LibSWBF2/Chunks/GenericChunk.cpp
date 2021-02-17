#include "stdafx.h"
#include "GenericChunk.h"
#include "BaseChunk.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Logging/Logger.h"

#include "STR.h"

#include "LVL/tex_/tex_.h"
#include "LVL/modl/LVL.modl.h"
#include "LVL/gmod/gmod.h"
#include "LVL/wrld/wrld.h"
#include "LVL/wrld/SIZE.h"
#include "LVL/wrld/XFRM.h"
#include "LVL/tern/tern.h"
#include "LVL/scr_/scr_.h"
#include "LVL/zaa_/zaa_.h"
#include "LVL/skel/skel.h"
#include "LVL/sound/emo_.h"
#include "LVL/sound/_pad.h"
#include "LVL/Locl/Locl.h"
#include "LVL/lvl_.h"
#include "LVL/LVL.h"
#include "LVL/common/GenericClass.h"
#include "LVL/config/ConfigChunk.h"

#include "LVL/coll/coll.h"
#include "LVL/prim/prim.h"


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
			THROW("Expected '{}' but got '{}'", expected, m_Header);
		}

		// check if current "chunk" exceeds parents data size
		GenericBaseChunk* parent = GetParent();
		if (parent != nullptr && (stream.GetPosition() + m_Size) > (parent->GetDataPosition() + parent->GetDataSize()))
		{
			THROW("Current chunk size {:#x} exceeds parent data size!", m_Size);
		}
	}

	template<uint32_t Header>
	void GenericChunk<Header>::RefreshSize()
	{
		THROW("Not implemented!");
	}

	template<uint32_t Header>
	void GenericChunk<Header>::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
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
					// Special case: lvl_ might not be loaded!
					// See lvl_.cpp for more information
					if (nextHead == "lvl_"_h)
					{
						LVL::lvl_* subLVL;
						READ_CHILD(stream, subLVL);
						chunk = subLVL;
					}

					else if (nextHead == "gmod"_h)
					{
						LVL::gmod::gmod* lodInfo;
						READ_CHILD(stream, lodInfo);
						chunk = lodInfo;
					}

					else if (nextHead == "NAME"_h)
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
					else if (nextHead == "skel"_h)
					{
						LVL::skel::skel* skeleton;
						READ_CHILD(stream, skeleton);
						chunk = skeleton;
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
					else if (nextHead == "emo_"_h)
					{
						LVL::sound::emo_* unknown;
						READ_CHILD(stream, unknown);
						chunk = unknown;
					}
					else if (nextHead == "_pad"_h)
					{
						LVL::sound::_pad* unknown;
						READ_CHILD(stream, unknown);
						chunk = unknown;
					}
					else if (nextHead == "lght"_h)
					{
						LVL::config::lght* lighting;
						READ_CHILD(stream, lighting);
						chunk = lighting;
					}
					else if (nextHead == "sky_"_h)
					{
						LVL::config::sky_* skyDome;
						READ_CHILD(stream, skyDome);
						chunk = skyDome;	
					}
					else if (nextHead == "fx__"_h)
					{
						LVL::config::fx__* fx;
						READ_CHILD(stream, fx);
						chunk = fx;	
					}
					else if (nextHead == "bnd_"_h)
					{
						LVL::config::bnd_* boundary;
						READ_CHILD(stream, boundary);
						chunk = boundary;	
					}
					else if (nextHead == "prp_"_h)
					{
						LVL::config::prp_* idk;
						READ_CHILD(stream, idk);
						chunk = idk;	
					}
					else if (nextHead == "path"_h)
					{
						LVL::config::path* path;
						READ_CHILD(stream, path);
						chunk = path;	
					}
					else if (nextHead == "comb"_h)
					{
						LVL::config::comb* combo;
						READ_CHILD(stream, combo);
						chunk = combo;	
					}
					else if (nextHead == "Locl"_h)
					{
						LVL::Localization::Locl* localizeChunk;
						READ_CHILD(stream, localizeChunk);
						chunk = localizeChunk;
					}
					else if (nextHead == "entc"_h)
					{
						LVL::common::entc* entityClass;
						READ_CHILD(stream, entityClass);
						chunk = entityClass;
					}
					else if (nextHead == "ordc"_h)
					{
						LVL::common::ordc* ordenanceClass;
						READ_CHILD(stream, ordenanceClass);
						chunk = ordenanceClass;
					}
					else if (nextHead == "wpnc"_h)
					{
						LVL::common::wpnc* weaponClass;
						READ_CHILD(stream, weaponClass);
						chunk = weaponClass;
					}
					else if (nextHead == "expc"_h)
					{
						LVL::common::expc* explosionClass;
						READ_CHILD(stream, explosionClass);
						chunk = explosionClass;
					}
					else if (nextHead == "coll"_h)
					{
						LVL::coll::coll* collisionMesh;
						READ_CHILD(stream, collisionMesh);
						chunk = collisionMesh;
					}					
					else if (nextHead == "prim"_h)
					{
						LVL::prim::prim* collisionPrimitives;
						READ_CHILD(stream, collisionPrimitives);
						chunk = collisionPrimitives;
					}
					else
					{
						GenericChunkNC* generic;
						READ_CHILD(stream, generic);
						chunk = generic;
					}

					LOG_INFO("Adding Child '{}' to '{}'", chunk->GetHeader(), m_Header);
				}
				catch (LibException& e)
				{
					delete chunk;
					chunk = nullptr;

					LOG_WARN(e.what());
					//LOG_WARN("Skipping invalid Chunk: '{}' at pos: {:#x}", nextHead, stream.GetPosition() - 8);
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
	template struct LIBSWBF2_API GenericChunk<0>;
	template struct LIBSWBF2_API GenericChunk<"ucfb"_m>;
	template struct LIBSWBF2_API GenericChunk<"LVL_"_m>;
	template struct LIBSWBF2_API GenericChunk<"INFO"_m>;
	template struct LIBSWBF2_API GenericChunk<"TYPE"_m>;
	template struct LIBSWBF2_API GenericChunk<"BODY"_m>;
	template struct LIBSWBF2_API GenericChunk<"FACE"_m>;
	template struct LIBSWBF2_API GenericChunk<"FMT_"_m>;
	template struct LIBSWBF2_API GenericChunk<"tex_"_m>;
	template struct LIBSWBF2_API GenericChunk<"modl"_m>;
	template struct LIBSWBF2_API GenericChunk<"gmod"_m>;
	template struct LIBSWBF2_API GenericChunk<"segm"_m>;
	template struct LIBSWBF2_API GenericChunk<"MTRL"_m>;
	template struct LIBSWBF2_API GenericChunk<"tern"_m>;
	template struct LIBSWBF2_API GenericChunk<"PCHS"_m>;
	template struct LIBSWBF2_API GenericChunk<"PTCH"_m>;
	template struct LIBSWBF2_API GenericChunk<"VBUF"_m>;
	template struct LIBSWBF2_API GenericChunk<"IBUF"_m>;
	template struct LIBSWBF2_API GenericChunk<"LTEX"_m>;
	template struct LIBSWBF2_API GenericChunk<"scr_"_m>;
	template struct LIBSWBF2_API GenericChunk<"skel"_m>;
	template struct LIBSWBF2_API GenericChunk<"SKIN"_m>;
	template struct LIBSWBF2_API GenericChunk<"BMAP"_m>;
	template struct LIBSWBF2_API GenericChunk<"emo_"_m>;
	template struct LIBSWBF2_API GenericChunk<"_pad"_m>;
	template struct LIBSWBF2_API GenericChunk<"XFRM"_m>;
	template struct LIBSWBF2_API GenericChunk<"inst"_m>;
	template struct LIBSWBF2_API GenericChunk<"DTEX"_m>;
	template struct LIBSWBF2_API GenericChunk<"Locl"_m>;
	template struct LIBSWBF2_API GenericChunk<"lvl_"_m>;
	
	template struct LIBSWBF2_API GenericChunk<"wrld"_m>;
	template struct LIBSWBF2_API GenericChunk<"regn"_m>;
	template struct LIBSWBF2_API GenericChunk<"anmg"_m>;
	template struct LIBSWBF2_API GenericChunk<"anim"_m>;
	template struct LIBSWBF2_API GenericChunk<"POSK"_m>;
	template struct LIBSWBF2_API GenericChunk<"ROTK"_m>;
	template struct LIBSWBF2_API GenericChunk<"ANIM"_m>;
	template struct LIBSWBF2_API GenericChunk<"SIZE"_m>;
	template struct LIBSWBF2_API GenericChunk<"Name"_m>;
	template struct LIBSWBF2_API GenericChunk<"DATA"_m>;
	template struct LIBSWBF2_API GenericChunk<"SCOP"_m>;
	template struct LIBSWBF2_API GenericChunk<"BASE"_m>;
	template struct LIBSWBF2_API GenericChunk<"PROP"_m>;

	// string chunks (see STR.cpp)
	template struct LIBSWBF2_API GenericChunk<"NAME"_m>;
	template struct LIBSWBF2_API GenericChunk<"TNAM"_m>;
	template struct LIBSWBF2_API GenericChunk<"SNAM"_m>;
	template struct LIBSWBF2_API GenericChunk<"TX0D"_m>;
	template struct LIBSWBF2_API GenericChunk<"TX1D"_m>;
	template struct LIBSWBF2_API GenericChunk<"TX2D"_m>;
	template struct LIBSWBF2_API GenericChunk<"TX3D"_m>;
	template struct LIBSWBF2_API GenericChunk<"PRNT"_m>;
	template struct LIBSWBF2_API GenericChunk<"NODE"_m>;
	template struct LIBSWBF2_API GenericChunk<"RTYP"_m>;
	template struct LIBSWBF2_API GenericChunk<"BNAM"_m>;
	template struct LIBSWBF2_API GenericChunk<"DTLX"_m>;

	// odf class types (see common/GenericCLass.cpp)
	template struct LIBSWBF2_API GenericChunk<"entc"_m>;
	template struct LIBSWBF2_API GenericChunk<"ordc"_m>;
	template struct LIBSWBF2_API GenericChunk<"wpnc"_m>;
	template struct LIBSWBF2_API GenericChunk<"expc"_m>;

	// configs
	template struct LIBSWBF2_API GenericChunk<"lght"_m>;
	template struct LIBSWBF2_API GenericChunk<"fx__"_m>;
	template struct LIBSWBF2_API GenericChunk<"sky_"_m>;
	template struct LIBSWBF2_API GenericChunk<"bnd_"_m>;
	template struct LIBSWBF2_API GenericChunk<"prp_"_m>;
	template struct LIBSWBF2_API GenericChunk<"path"_m>;
	template struct LIBSWBF2_API GenericChunk<"comb"_m>;

	// collision
	template struct LIBSWBF2_API GenericChunk<"coll"_m>;
	template struct LIBSWBF2_API GenericChunk<"POSI"_m>;
	template struct LIBSWBF2_API GenericChunk<"TREE"_m>;
	template struct LIBSWBF2_API GenericChunk<"LEAF"_m>;
	template struct LIBSWBF2_API GenericChunk<"prim"_m>;
	template struct LIBSWBF2_API GenericChunk<"MASK"_m>;

	//animation
	template struct LIBSWBF2_API GenericChunk<"zaa_"_m>;
	template struct LIBSWBF2_API GenericChunk<"BIN_"_m>;
	template struct LIBSWBF2_API GenericChunk<"MINA"_m>;
	template struct LIBSWBF2_API GenericChunk<"TNJA"_m>;
	template struct LIBSWBF2_API GenericChunk<"TADA"_m>;

}

