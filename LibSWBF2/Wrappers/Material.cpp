#include "stdafx.h"
#include "Material.h"
#include "Segment.h"
#include "Level.h"
#include "LevelContainer.h"
#include "InternalHelpers.h"


namespace LibSWBF2::Wrappers
{
	bool Material::FromChunk(Level* mainContainer, MTRL* materialChunk, Material& out)
	{
		if (mainContainer == nullptr)
		{
			LOG_ERROR("Given mainContainer was NULL!");
			return false;
		}
		if (materialChunk == nullptr)
		{
			LOG_ERROR("Given materialChunk was NULL!");
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

	bool Material::GetTextureName(uint8_t index, String& outName) const
	{
		segm* segment = dynamic_cast<segm*>(p_Material->GetParent());
		if (segment == nullptr)
		{
			LOG_ERROR("Parent of MTRL is not segm!");
			return false;
		}

		if (index >= segment->m_Textures.Size())
		{
			LOG_WARN("Texture index '{}' is out of bounds ({})!", index, segment->m_Textures.Size());
			return false;
		}
		outName = segment->m_Textures[index]->m_Name;
		return true;
	}

	const Texture* Material::GetTexture(uint8_t index) const
	{
		String textureName;
		if (m_MainContainer != nullptr && GetTextureName(index, textureName))
		{
			return m_MainContainer->GetTexture(textureName);
		}
		return nullptr;
	}
}