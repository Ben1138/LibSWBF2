#include "stdafx.h"
#include "Script.h"
#include "InternalHelpers.h"

#include "Chunks/LVL/scr_/scr_.h"


namespace LibSWBF2::Wrappers
{
	bool Script::FromChunk(scr_* scriptChunk, Script& out)
	{
		if (scriptChunk == nullptr)
		{
			LOG_ERROR("Given scriptChunk was NULL!");
			return false;
		}

		out.p_Script = scriptChunk;

		return true;
	}

	String Script::GetName() const
	{
		return p_Script->p_Name->m_Text;
	}

	bool Script::GetData(const uint8_t*& data, size_t& size) const
	{
		return p_Script->p_Body->GetData(data, size);
	}
}