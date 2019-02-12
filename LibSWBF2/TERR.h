#pragma once
#include "HeaderNames.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Logger.h"
#include "Color.h"
#include "Vector4.h"
#include "List.h"
#include "LibString.h"

namespace LibSWBF2::Chunks::Terrain
{
	using Logging::Logger;
	using Logging::ELogType;
	using Types::Color;
	using Types::Vector2;
	using Types::Vector3;
	using Types::Vector4;
	using LibSWBF2::Types::List;
	using LibSWBF2::Types::String;

	struct TERR
	{
		TERR() = default;
		~TERR() = default;

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);
		bool WriteToFile(const string& Path);
		bool ReadFromFile(const string& Path);

		uint32_t FileVersion;
	};
}