#pragma once
#include "req.h"


namespace LibSWBF2
{
	class FileWriter;
	class FileReader;
}


namespace LibSWBF2::Types
{
	struct Vector3;
	struct String;

	#pragma pack(push,1)
	struct LIBSWBF2_API WorldAnimationKey
	{
		float_t m_Time;
		Vector3 m_Value;
		EWorldAnimKeyTransitionType m_TransitionType;
		Vector3 m_EaseOut;
		Vector3 m_EaseIn;

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		String ToString() const;

	};
	#pragma pack(pop)
}