#pragma once
#include <LibSWBF2/Types/LibString.h>


namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Color4f
	{
		static const ChunkSize SIZE = sizeof(float) * 4;

		Color4f();
		Color4f(const float Red, const float Green, const float Blue);
		Color4f(const float Red, const float Green, const float Blue, const float Alpha);
		~Color4f();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		String ToString() const;

		float m_Red = 0.0f;
		float m_Green = 0.0f;
		float m_Blue = 0.0f;
		float m_Alpha = 0.0f;
	};
}
