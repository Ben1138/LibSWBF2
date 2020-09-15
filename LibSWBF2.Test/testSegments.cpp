#include "stdafx.h"
#include "LibSWBF2.h"
#include "FileWriter.h"
#include "Chunks/LVL/LVL.h"
#include "Types/Enums.h"

#include <iostream>
#include <fstream>
#include <string>

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;

using namespace LibSWBF2::Chunks::LVL;
using namespace LibSWBF2::Wrappers;
using namespace LibSWBF2;

using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl
void libLog(const LoggerEntry* log){ COUT(log->ToString().Buffer()); }



int main()
{
	Logger::SetLogCallback(&libLog);

#ifdef __APPLE__
	//Level *testLVL = Level::FromFile("/Users/will/Desktop/MLC.lvl");
	Level *testLVL = Level::FromFile("/Volumes/bootable/stockdata/_lvl_pc/mus/mus1.lvl");
#else
	Level *testLVL = Level::FromFile("/home/will/Desktop/MLC.lvl");
#endif

	COUT("Loaded file");

	const List<Model>& models = testLVL -> GetModels();

	for (int i = 0; i < models.Size(); i++)
	{
		const List<Segment>& segments = models[i].GetSegments();
		COUT(models[i].GetName().Buffer());

		for (int j = 0; j < segments.Size(); j++)
		{
			uint32_t vBufSize;
			Vector3 *vertexBuffer;

			uint32_t indexBufSize;
			uint16_t *indexBuffer;

			segments[j].GetVertexBuffer(vBufSize, vertexBuffer);
			segments[j].GetIndexBuffer(indexBufSize, indexBuffer, ETopology::TriangleList);

			const Material& segmentMat = segments[j].GetMaterial();
			const Texture* segmentTex = segmentMat.GetTexture(0);//?

			if (segmentMat.GetFlags() == EMaterialFlags::Scrolling)
			{
				COUT("Found glow at " << models[i].GetName().Buffer() << " segment " << j);
			}
			else 
			{
				continue;
			}

			if (segmentTex == nullptr)
			{
				COUT("\t TEXTURE MISSING");
				continue;
			}
			String *segmentTexName = new String(segmentTex -> GetName());
			const char *segTex = segmentTexName -> Buffer();

			//COUT(fmt::format("\tVertexBuffer size: {}", vBufSize));
			COUT(fmt::format("\tSegment texName: {}", segTex));

			int numDegenerates = 0;
			for (int i = 0; i < (int) indexBufSize - 2; i+=3)
			{
				if (indexBuffer[i] == indexBuffer[i+1] ||
					indexBuffer[i+1] == indexBuffer[i+2] ||
					indexBuffer[i] == indexBuffer[i+2])
				{
					numDegenerates++;
				}
			}
			//COUT(fmt::format("\tFound {} degenerates out of {}", numDegenerates, indexBufSize));
		}

	}

	return 0;
}
