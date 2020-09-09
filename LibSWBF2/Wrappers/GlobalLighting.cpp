#include "stdafx.h"
#include "GlobalLighting.h"
#include "InternalHelpers.h"
#include <stdint.h>


namespace LibSWBF2::Wrappers
{
    bool GlobalLightingConfig::FromChunk(SCOP_LGHT* body, GlobalLightingConfig& out)
    {
        if (body == nullptr)
        {
            LOG_ERROR("tag or body was null in GlobalLightingConfig wrapper constructor");
            return false;
        }
        out = GlobalLightingConfig(body);
        return true;
    }


    GlobalLightingConfig::GlobalLightingConfig(SCOP_LGHT* body) : p_FieldsChunk(body) {}


    bool GlobalLightingConfig::GetTopColor(Vector3& colorOut) const
    {
        if (p_FieldsChunk->p_TopColorChunk == nullptr)
        {
            return false;
        }
        colorOut = p_FieldsChunk->p_TopColorChunk->m_Vec;
        return true;
    }

    bool GlobalLightingConfig::GetBottomColor(Vector3& colorOut) const
    {
        if (p_FieldsChunk->p_BottomColorChunk == nullptr)
        {
            return false;
        }
        colorOut = p_FieldsChunk->p_BottomColorChunk->m_Vec;
        return true;
    }

    bool GlobalLightingConfig::GetLight1(String& light1NameOut) const
    {
        if (p_FieldsChunk->p_Light1Name == nullptr)
        {
            LOG_WARN("light 1 not found");
            return false;
        }
        light1NameOut = p_FieldsChunk->p_Light1Name->m_String;
        return true;
    }

    bool GlobalLightingConfig::GetLight2(String& light2NameOut) const
    {
        if (p_FieldsChunk->p_Light2Name == nullptr)
        {
            LOG_WARN("light 2 not found");
            return false;
        }
        light2NameOut = p_FieldsChunk->p_Light2Name->m_String;
        return true;
    }

    String GlobalLightingConfig::ToString() const
    {
        String stringRep = "Global lighting section: ";
        Vector3 color;
        String name;

        if (GetTopColor(color))
        {
            stringRep = stringRep + "Top color: " + color.ToString() + ", ";
        }

        if (GetBottomColor(color))
        {
            stringRep = stringRep + "Bottom color: " + color.ToString() + ", ";
        }

        if (GetLight1(name))
        {
            stringRep = stringRep + "Light1: " + name + ", ";
        }

        if (GetLight2(name))
        {
            stringRep = stringRep + "Light2: " + name;
        }

        return stringRep;
    }
}