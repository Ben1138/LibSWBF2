// LibSWBF2.Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../LibSWBF2/LibSWBF2.h"
#include "../LibSWBF2/FileWriter.h"
#include <iostream>
#include <fstream>
#include <string>

using LibSWBF2::Types::String;
using LibSWBF2::Chunks::MSH::MSH;
using LibSWBF2::Wrappers::SoundBank;
using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;
using LibSWBF2::FileWriter;

void libLog(const LoggerEntry* log)
{
	//std::cout << log->ToString().Buffer() << std::endl;
}

int main()
{
	Logger::SetLogCallback(&libLog);

	SoundBank* soundBank = SoundBank::FromFile("F:\\SteamLibrary\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\sound\\common.bnk");

	if (soundBank == nullptr)
	{
		std::cout << "ERROR" << std::endl;
		return 0;
	}

	uint32_t numClips = soundBank->GetNumSoundClips();
	for (uint32_t i = 0; i < numClips; ++i)
	{
		String name;
		uint32_t sampleRate;
		uint32_t sampleCount;
		uint8_t blockAlign;
		const uint8_t* data;

		if (!soundBank->GetSoundClip(i, name, sampleRate, sampleCount, blockAlign, data) || data == nullptr)
		{
			std::cout << "Error reading clip no " << i << std::endl;
			continue;
		}

		std::string clipName = "[" +std::to_string(i) + "] " + std::string(name.Buffer()) + ".wav";
		std::cout << "Exporting clip " << clipName << std::endl;

		uint32_t dataSize = sampleCount * blockAlign;
		uint32_t fileSize = dataSize + 36;

		FileWriter wav;
		wav.Open(("F:\\SteamLibrary\\steamapps\\common\\Star Wars Battlefront II\\GameData\\data\\_lvl_pc\\sound\\common\\" + clipName).c_str());
		wav.WriteString("RIFF", 4);
		wav.WriteUInt32(fileSize);
		wav.WriteString("WAVE", 4);
		wav.WriteString("fmt ", 4);
		wav.WriteUInt32(16);				// fmt header size
		wav.WriteUInt16(1);					// PCM format
		wav.WriteUInt16(1);					// num of audio channels
		wav.WriteUInt32(sampleRate);
		wav.WriteUInt32(sampleRate * 2);	// frame size
		wav.WriteUInt16(blockAlign);
		wav.WriteUInt16(16);				// bit depth
		wav.WriteString("data", 4);
		wav.WriteUInt32(dataSize);
		wav.WriteBytes(data, dataSize);

		wav.Close();
	}

	SoundBank::Destroy(soundBank);
	return 0;
}