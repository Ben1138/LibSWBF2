#include "pch.h"
#include "Material.h"
#include "Texture.h"
#include "Level.h"

#include "Container.h"
#include "InternalHelpers.h"


#include "Chunks/LVL/modl/MTRL.h"
#include "Chunks/LVL/modl/TNAM.h"
#include "Chunks/LVL/modl/modl.segm.h"



namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Chunks::LVL::modl::segm;

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

	const Color4u8& Material::GetDiffuseColor() const
	{
		return p_Material->m_DiffuseColor;
	}

	const Color4u8& Material::GetSpecularColor() const
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