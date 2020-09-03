#include "stdafx.h"
#include "Logging/Logger.h"
#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"

#include "lght.SCOP.h"

#include <algorithm>
#include <cstring>
#include <iostream>

#define COUT(x) std::cout << x << std::endl;



using namespace LibSWBF2::Chunks::LVL::common;


namespace LibSWBF2::Chunks::LVL::lght
{
    
void SCOP_LGHT::RefreshSize()
{
    THROW("Not implemented!");
}

void SCOP_LGHT::WriteToStream(FileWriter& stream)
{
    THROW("Not implemented!");
}

void SCOP_LGHT::ReadFromStream(FileReader& stream)
{ 
    /*
     After reading the header, just read the children,
     as a SCOP is just length int32 + DATA children.
     */
    
    BaseChunk::ReadFromStream(stream);
    Check(stream);

    LOG_WARN("\nREADING LGHT");

    while (ThereIsAnother(stream))
    {
        uint32_t nextDATATag = DATA::PeekDATATag(stream);

        LOG_WARN(fmt::format("Next tag: {}", nextDATATag).c_str());

        switch (nextDATATag)
        {
            case 564937055:
                READ_CHILD(stream, p_RotationChunk);
                break;
            case 2471448074:
                READ_CHILD(stream, p_PositionChunk);
                break;
            case 1361572173:
                READ_CHILD(stream, p_TypeChunk);
                break;
            case 1031692888:
                READ_CHILD(stream, p_ColorChunk);
                break;
            case 4208725202:
                READ_CHILD(stream, p_RangeChunk);
                LOG_WARN(fmt::format("Range read: {}", p_RangeChunk -> m_FloatMember).c_str());
                break;
            case 3711978346:
                READ_CHILD(stream, p_ConeChunk);
                LOG_WARN(fmt::format("Cone read: {}", p_ConeChunk -> ToString()).c_str());
                break;
            default:
                READ_CHILD_GENERIC(stream);
                break; 
        }
    }

    LOG_WARN("FINISHED LGHT\n");

    BaseChunk::EnsureEnd(stream);
}
    
}
