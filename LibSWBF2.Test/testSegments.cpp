#include "testing.h"



int main(int ac, char** av)
{
	List<String> pathsInput;

	for (int i = 1; i < ac; i++)
	{
		pathsInput.Add(av[i]);
	}

	auto lvlPtrs = LoadAndTrackLVLs(pathsInput);

	for (int i = 0; i < lvlPtrs.size(); i++)
	{
		auto testLVL = lvlPtrs[i];
		const List<Model>& models = testLVL -> GetModels();

		COUT("Results from test: ");// << testLVL -> GetLevelName().Buffer());

		for (int i = 0; i < models.Size(); i++)
		{
			const List<Segment>& segments = models[i].GetSegments();
			COUT("\t" << models[i].GetName().Buffer());

			for (int j = 0; j < segments.Size(); j++)
			{
				uint32_t vBufSize;
				Vector3 *vertexBuffer;

				uint32_t indexBufSize;
				uint16_t *indexBuffer;

				segments[j].GetVertexBuffer(vBufSize, vertexBuffer);
				segments[j].GetIndexBuffer(indexBufSize, indexBuffer);

				const Material& segmentMat = segments[j].GetMaterial();
				const Texture* segmentTex = segmentMat.GetTexture(0);

				if (segmentTex == nullptr)
				{
					continue;
				}

				String segmentTexName = segmentTex -> GetName();
				String materialFlags = MaterialFlagsToString( segmentMat.GetFlags() );
				
				COUT("\t\tSegment " << j << ": Texture name: " << segmentTexName.Buffer() << " Material properties: " << materialFlags.Buffer());
			}
		}

	}


	return 0;
}
