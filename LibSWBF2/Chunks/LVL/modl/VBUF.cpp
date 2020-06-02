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

                    int16_t a, b, c, d;
                    a = stream.ReadInt16();
                    b = stream.ReadInt16();
                    c = stream.ReadInt16();
                    d = stream.ReadInt16();

                    const float i16min = std::numeric_limits<int16_t>::min();
                    const float i16max = std::numeric_limits<int16_t>::max();

                    m_Positions.Add(low + (c - i16min) * mul / (i16max - i16min));
                }
                else
                {
                    m_Positions.Emplace().ReadFromStream(stream);
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
        result += "\n";
        result += "Positions = [";

        for (uint32_t i = 0; i < m_Positions.Size(); ++i)
        {
            result += m_Positions[i].ToString().Buffer() + string(", ");
            if ((i + 1) % 4 == 0)
            {
                result += "\n";
            }
        }
        result.resize(result.size() - 2);
        result += "]";
        return result.c_str();
    }
}