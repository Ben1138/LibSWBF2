#include "LibSWBF2.h"
#include "FileWriter.h"
#include "Chunks/LVL/LVL.h"

#include <iostream>
#include <fstream>
#include <string>

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;

using namespace LibSWBF2::Chunks::LVL;
using namespace LibSWBF2::Wrappers;

using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl



void libLog(const LoggerEntry* log){ COUT(log->ToString().Buffer()); }



int main()
{
	Logger::SetLogCallback(&libLog);

#ifdef __APPLE__
	Level *testLVL = Level::FromFile("/Users/will/Desktop/MLC.lvl");
#else
	Level *testLVL = Level::FromFile("/home/will/Desktop/MLC.lvl");
#endif

	const List<Model>& models = testLVL -> GetModels();

	for (int i = 0; i < models.Size(); i++)
	{
		const List<Segment>& segments = models[i].GetSegments();
		COUT(models[i].GetName().Buffer());

		for (int j = 0; j < segments.Size(); j++)
		{
			uint32_t vBufSize;
			Vector3 *vertexBuffer;

			segments[j].GetVertexBuffer(vBufSize, vertexBuffer);

			const Material& segmentMat = segments[j].GetMaterial();
			const Texture* segmentTex = segmentMat.GetTexture(0);//?

			if (segmentTex == nullptr)
			{
				LOG_ERROR("\t TEXTURE MISSING");
				continue;
			}
			String *segmentTexName = new String(segmentTex -> GetName());
			const char *segTex = segmentTexName -> Buffer();

			COUT(fmt::format("\tVertexBuffer size: {}", vBufSize));
			COUT(fmt::format("\tSegment texName: {}", segTex));
		}

	}

	return 0;
}
