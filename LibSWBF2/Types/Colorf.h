#pragma once

namespace LibSWBF2::Types
{
	class FileWriter;
	class FileReader;

	struct LIBSWBF2_API Colorf
	{
		static const ChunkSize SIZE = sizeof(float_t) * 4;

		Colorf();
		Colorf(const float_t Red, const float_t Green, const float_t Blue);
		Colorf(const float_t Red, const float_t Green, const float_t Blue, const float_t Alpha);
		~Colorf();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float_t m_Red = 0.0f;
		float_t m_Green = 0.0f;
		float_t m_Blue = 0.0f;
		float_t m_Alpha = 0.0f;
	};
}