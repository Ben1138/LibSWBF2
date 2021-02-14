#include "testing.h"



int main(int ac, char **av)
{
	List<String> pathsInput;

	for (int i = 1; i < ac; i++)
	{
		pathsInput.Add(av[i]);
	}

	auto lvlPtrs = LoadAndTrackLVLs(pathsInput);

	if (lvlPtrs.size() == 0)
	{
		return -1;
	}

	auto testLVL = lvlPtrs[0];


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
		uint16_t *indices;
		Vector3* verts;

		mesh.GetIndexBuffer(LibSWBF2::ETopology::TriangleList, numIndices, indices);
		mesh.GetVertexBuffer(numVertices, verts);

		COUT("\t\tIndicies length: " << numIndices);
		COUT("\t\tVertices length: " << numVertices << "\n");
	}
	
	return 0;
}
