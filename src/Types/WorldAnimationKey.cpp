#include <LibSWBF2/pch.h>
#include <LibSWBF2/Types/LibString.h>
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/IO/FileWriter.h>
#include <LibSWBF2/Types/WorldAnimationKey.h>
#include <LibSWBF2/Types/LibString.h>
#include <LibSWBF2/Types/Vector3.h>
#include <fmt/format.h>


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
