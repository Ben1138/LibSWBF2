// LibSWBF2.Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "LibSWBF2.h"
#include "FileWriter.h"
#include "Chunks/LVL/LVL.h"

#include <iostream>
#include <fstream>
#include <string>

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;

using namespace LibSWBF2::Chunks::LVL;

using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl



void libLog(const LoggerEntry* log){ COUT(log->ToString().Buffer()); }



int main()
{
	Logger::SetLogCallback(&libLog);

	Level *testLVL = FromFile("/Users/will/Desktop/MLC.lvl");

	return 0;
}
