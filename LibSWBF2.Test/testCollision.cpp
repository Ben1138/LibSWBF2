#include "LibSWBF2.h"
#include "FileWriter.h"
#include "Types/Enums.h"
#include "../LibSWBF2/Wrappers/Model.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using LibSWBF2::Types::String;
using LibSWBF2::Types::List;

using namespace LibSWBF2::Wrappers;
using LibSWBF2::Wrappers::Model;
using LibSWBF2::Wrappers::CollisionMesh;

using LibSWBF2::Container;
using LibSWBF2::Logging::Logger;
using LibSWBF2::Logging::LoggerEntry;


#define COUT(x) std::cout << x << std::endl



int main()
{
	const char *path;
	const char *path1;

#ifdef __APPLE__
	path = "/Users/will/Desktop/geo1.lvl";
	path1 = "/Users/will/Desktop/geo1.lvl";
#else
	path = "/home/will/Desktop/geo1.lvl";
#endif

	Container *container = Container::Create();
	auto handle = container -> AddLevel(path);
	//auto handle1 = container -> AddLevel(path1);
	container -> StartLoading();

	while (!container -> IsDone())
	{
		usleep(100000);
		std::cout << "\rProgress: " << container -> GetLevelProgress(handle) << std::flush;
	}

	std::cout << std::endl;

	Level *testLVL = container -> GetLevel(handle);
	//Level *testLVL1 = container -> GetLevel(handle1);


	const List<Model>& models = testLVL -> GetModels();

	for (int i = 0; i < models.Size(); i++)
	{
		const Model& modeli = models[i];

		COUT(modeli.GetName().Buffer());
		
		const List<CollisionPrimitive>& prims = modeli.GetCollisionPrimitives();
		const CollisionMesh& mesh = modeli.GetCollisionMesh();

		COUT("\n\tPrimitives: ");

		for (int i = 0; i < prims.Size(); i++)
		{
			COUT("\t\t" << prims[i].ToString().Buffer());
		}

		COUT("\tMesh: ");

		uint32_t numIndices, numVertices;
		uint32_t *indices;
		Vector3* verts;

		mesh.GetIndexBuffer(LibSWBF2::ETopology::TriangleList, numIndices, indices);
		mesh.GetVertexBuffer(numVertices, verts);

		COUT("\t\tIndicies length: " << numIndices);
		COUT("\t\tVertices length: " << numVertices << "\n");
	}
	
	return 0;
}
