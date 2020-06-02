#include "stdafx.h"
#include "VBUF.h"
#include "LVL.modl.h"
#include <limits>

#undef min
#undef max

namespace LibSWBF2::Chunks::LVL::modl
{
    void VBUF::RefreshSize()
    {
        throw std::runtime_error("Not implemented!");
    }

    void VBUF::WriteToStream(FileWriter& stream)
    {
        throw std::runtime_error("Not implemented!");
    }

    void VBUF::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);

        m_Count = stream.ReadUInt32();
        m_Stride = stream.ReadUInt32();
        m_Flags = (EVBUFFlags)stream.ReadUInt32();

        modl* model = dynamic_cast<modl*>(GetParent()->GetParent());
        if (model == nullptr)
        {
            // should never happen
            LOG("Parent modl is NULL!", ELogType::Error);
            BaseChunk::EnsureEnd(stream);
            return;
        }

        for (uint32_t i = 0; i < m_Count; ++i)
        {
            if ((m_Flags & EVBUFFlags::Position) != 0)
            {
                if ((m_Flags & EVBUFFlags::PositionCompressed) != 0)
                {
                    Vector3 low = model->p_Info->m_VertexBox[0];
                    Vector3 mul = (model->p_Info->m_VertexBox[1] - model->p_Info->m_VertexBox[0]);

                    int16_t data[4];
                    data[0] = stream.ReadInt16();
                    data[1] = stream.ReadInt16();
                    data[2] = stream.ReadInt16();
                    data[3] = stream.ReadInt16();
                    Vector3 c(data[0], data[1], data[2]);

                    constexpr float i16min = std::numeric_limits<int16_t>::min();
                    constexpr float i16max = std::numeric_limits<int16_t>::max();

                    m_Positions.Add(low + (c - i16min) * mul / (i16max - i16min));
                }
                else
                {
                    m_Positions.Emplace().ReadFromStream(stream);
                }
            }

            if ((m_Flags & EVBUFFlags::BlendWeight) != 0)
            {
                if ((m_Flags & EVBUFFlags::BlendWeightCompressed) != 0)
                {
                    // TODO: generalize Vectors
                    int8_t data[4];
                    data[0] = stream.ReadByte();
                    data[1] = stream.ReadByte();
                    data[2] = stream.ReadByte();
                    data[3] = stream.ReadByte();
                    m_Weights.Add({ (float_t)data[2], (float_t)data[1], 1.0f - data[2] - data[1] });
                }
                else
                {
                    float_t x, y;
                    x = stream.ReadFloat();
                    y = stream.ReadFloat();
                    m_Weights.Add({ x, y, 1.0f - x - y});
                }
            }

            if ((m_Flags & EVBUFFlags::BlendIndices) != 0)
            {
                m_Bones.Emplace().ReadFromStream(stream);
            }

            if ((m_Flags & EVBUFFlags::Normal) != 0)
            {
                if ((m_Flags & EVBUFFlags::NormalCompressed) != 0)
                {
                    int8_t data[4];
                    data[0] = stream.ReadByte();
                    data[1] = stream.ReadByte();
                    data[2] = stream.ReadByte();
                    data[3] = stream.ReadByte();
                    Vector3 normal((float_t)data[0], (float_t)data[1], (float_t)data[2]);
                    normal = (normal * 2.0f) - 1.0f;
                    m_Normals.Add(normal);
                }
                else
                {
                    m_Normals.Emplace().ReadFromStream(stream);
                }
            }

            if ((m_Flags & EVBUFFlags::Tangents) != 0)
            {
                if ((m_Flags & EVBUFFlags::NormalCompressed) != 0)
                {
                    int8_t data[4];
                    data[0] = stream.ReadByte();
                    data[1] = stream.ReadByte();
                    data[2] = stream.ReadByte();
                    data[3] = stream.ReadByte();
                    Vector3 tangent((float_t)data[0], (float_t)data[1], (float_t)data[2]);
                    tangent = (tangent * 2.0f) - 1.0f;
                    m_Tangents.Add(tangent);

                    data[0] = stream.ReadByte();
                    data[1] = stream.ReadByte();
                    data[2] = stream.ReadByte();
                    data[3] = stream.ReadByte();
                    Vector3 biTangent((float_t)data[0], (float_t)data[1], (float_t)data[2]);
                    biTangent = (biTangent * 2.0f) - 1.0f;
                    m_BiTangents.Add(biTangent);
                }
                else
                {
                    m_Tangents.Emplace().ReadFromStream(stream);
                    m_BiTangents.Emplace().ReadFromStream(stream);
                }
            }

            if ((m_Flags & EVBUFFlags::Color) != 0)
            {
                m_Colors.Emplace().ReadFromStream(stream);
            }

            if ((m_Flags & EVBUFFlags::StaticLighting) != 0)
            {
                m_Colors.Emplace().ReadFromStream(stream);
            }

            if ((m_Flags & EVBUFFlags::TexCoord) != 0)
            {
                if ((m_Flags & EVBUFFlags::TexCoordCompressed) != 0)
                {
                    uint16_t data[2];
                    data[0] = stream.ReadByte();
                    data[1] = stream.ReadByte();
                    Vector2 uv((float_t)data[0], (float_t)data[1]);
                    uv = uv / 2048.0f;
                    m_TexCoords.Add(uv);
                }
                else
                {
                    m_TexCoords.Emplace().ReadFromStream(stream);
                }
            }
        }

        BaseChunk::EnsureEnd(stream);
    }

    String VBUF::ToString()
    {
        string result = "Count = " + std::to_string(m_Count) + "\n";
        result += "Stride = " + std::to_string(m_Stride) + "\n";
        result += "Flags = " + string(EVBUFFlagsToString(m_Flags).Buffer()) + "\n";
        result += "Normals[" + std::to_string(m_Normals.Size()) + "]\n";
        result += "Tangents[" + std::to_string(m_Tangents.Size()) + "]\n";
        result += "BiTangents[" + std::to_string(m_BiTangents.Size()) + "]\n";
        result += "Colors[" + std::to_string(m_Colors.Size()) + "]\n";
        result += "Tex Coords[" + std::to_string(m_TexCoords.Size()) + "]\n";
        result += "Bones[" + std::to_string(m_Bones.Size()) + "]\n";
        result += "Weights[" + std::to_string(m_Weights.Size()) + "]\n";
        result += "\n";

        result += "Positions["+std::to_string(m_Positions.Size())+"] = [";
        for (uint32_t i = 0; i < m_Positions.Size(); ++i)
        {
            result += m_Positions[i].ToString().Buffer() + string(", ");
            if ((i + 1) % 3 == 0)
            {
                result += "\n";
            }
        }
        result.resize(result.size() - 2);
        result += "]";

        return result.c_str();
    }
}