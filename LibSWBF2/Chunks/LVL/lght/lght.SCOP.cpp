#include "stdafx.h"
#include "Logging/Logger.h"
#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "lght.SCOP.h"
#include <algorithm>
#include <cstring>
#include <iostream>


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

        while (ThereIsAnother(stream))
        {
            uint32_t nextDATATag = DATA::PeekDATATag(stream);

            //LOG_WARN("Next Tag: {}", nextDATATag);

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
                    break;
                case 3711978346:
                    READ_CHILD(stream, p_ConeChunk);
                    break;
                case 3679873338:
                    READ_CHILD(stream, p_Light1Name);
                    //LOG_WARN("Got light 1: {}", p_Light1Name -> m_String.Buffer());
                    break;
                case 3663095719:
                    READ_CHILD(stream, p_Light2Name);
                    //LOG_WARN("Got light 2: {}", p_Light2Name -> m_String.Buffer());
                    break;
                case 2802900028:
                    READ_CHILD(stream, p_TopColorChunk);
                    //LOG_WARN("Got top color: {}", p_TopColorChunk -> ToString().Buffer());
                    break;
                case 1319594794:
                    READ_CHILD(stream, p_BottomColorChunk);
                    //LOG_WARN("Got bottom color: {}", p_BottomColorChunk -> ToString().Buffer());
                    break;
                default:
                    READ_CHILD_GENERIC(stream);
                    break; 
            }
        }

        BaseChunk::EnsureEnd(stream);
    }
}
