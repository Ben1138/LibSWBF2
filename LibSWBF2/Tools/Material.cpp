#include "stdafx.h"
#include "Material.h"
#include "Segment.h"
#include "Level.h"
#include "Logging\Logger.h"


namespace LibSWBF2::Tools
{
	using Logging::ELogType;

	bool Material::FromChunk(Level* mainContainer, MTRL* materialChunk, Material& out)
	{
		if (mainContainer == nullptr)
		{
			LOG("Given mainContainer was NULL!", ELogType::Error);
			return false;
		}
		if (materialChunk == nullptr)
		{
			LOG("Given materialChunk was NULL!", ELogType::Error);
			return false;
		}

		out.m_MainContainer = mainContainer;
		out.p_Material = materialChunk;
		return true;
	}

	EMaterialFlags Material::GetFlags() const
	{
		return p_Material->m_Flags;
	}

	const Color& Material::GetDiffuseColor() const
	{
		return p_Material->m_DiffuseColor;
	}

	const Color& Material::GetSpecularColor() const
	{
		return p_Material->m_SpecularColor;
	}

	uint32_t Material::GetSpecularExponent() const
	{
		return p_Material->m_SpecularExponent;
	}

	const String& Material::GetAttachedLight() const
	{
		return p_Material->m_AttachedLight;
	}

	const Texture* Material::GetTexture(uint8_t index) const
	{
		segm* segment = dynamic_cast<segm*>(p_Material->GetParent());
		if (segment == nullptr)
		{
			LOG("Parent of MTRL is not segm!", ELogType::Error);
			return nullptr;
		}

		if (index >= segment->m_Textures.Size())
		{
			LOG("Texture index '"+std::to_string(index)+"' is out of bounds ("+std::to_string(segment->m_Textures.Size())+")!", ELogType::Error);
			return nullptr;
		}

		return m_MainContainer->GetTexture(segment->m_Textures[index]->m_Name);
	}
}