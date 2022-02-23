#include "pch.h"
#include "Types/LibString.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <fmt/format.h>
#include "WorldAnimationKey.h"
#include "LibString.h"
#include "Vector3.h"


namespace LibSWBF2::Types
{
	void WorldAnimationKey::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_Time);
		m_Value.WriteToStream(stream);
		stream.WriteByte((uint8_t) m_TransitionType);
		m_EaseOut.WriteToStream(stream);
		m_EaseIn.WriteToStream(stream);
	}

	void WorldAnimationKey::ReadFromStream(FileReader& stream)
	{
		m_Time = stream.ReadFloat();
		m_Value.ReadFromStream(stream);
		m_TransitionType = (EWorldAnimKeyTransitionType) stream.ReadByte();
		m_EaseOut.ReadFromStream(stream);
		m_EaseIn.ReadFromStream(stream);
	}

	String WorldAnimationKey::ToString() const
	{
		String rep = fmt::format("Time: {}, Value: {}, TransitionType: {}, EaseIn: {}, EaseOut: {}", 
								m_Time, 
								m_Value.ToString().Buffer(),
								WorldAnimKeyTransitionTypeToString(m_TransitionType).Buffer(),
								m_EaseOut.ToString().Buffer(),
								m_EaseIn.ToString().Buffer()).c_str();
		return rep;
	}
}