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
	Level *testLVL = Level::FromFile("/Users/will/Desktop/geo1.lvl");
	//Level *testLVL = Level::FromFile("/Volumes/bootable/stockdata/_lvl_pc/mus/mus1.lvl");
#else
	Level *testLVL = Level::FromFile("/home/will/Desktop/MLC.lvl");
#endif

	COUT("Loaded file");

	const List<World>& worlds = testLVL -> GetWorlds();
	const List<EntityClass>& entities = testLVL -> GetEntityClasses();

	const String geomProp("GeometryName");


	COUT("\n==================  Listing all entities  ========================\n");

	for (int i = 0; i < entities.Size(); i++)
	{
		COUT("Found entity type: " << entities[i].GetClassType().Buffer() 
			<< " which is subclass of " << entities[i].GetClassBase().Buffer()
		);
	}


	COUT("\n==================  Listing all instances  ========================\n");

	for (int i = 0; i < worlds.Size(); i++)
	{
		const List<Instance>& instances = worlds[i].GetInstances();
		
		for (int j = 0; j < instances.Size(); j++)
		{
			const String& name = instances[j].GetName();
			
			COUT("Found instance: " << name.Buffer() 
				<< " at position " << instances[j].GetPosition().ToString().Buffer()
			);			
		}
	}


	COUT("\n==================  Listing all instances with corresponding entity references  ========================\n");

	for (int i = 0; i < worlds.Size(); i++)
	{
		const List<Instance>& instances = worlds[i].GetInstances();
		
		for (int j = 0; j < instances.Size(); j++)
		{
			const String& name = instances[j].GetName();
			const String& instanceType = instances[j].GetType();

			auto *instanceClass = testLVL -> GetEntityClass(instanceType);
			String geometryName; 

			if (instanceClass != nullptr && instanceClass -> GetProperty(geomProp,geometryName))
			{
				COUT("Found instance: " << name.Buffer() 
					<< " of type " << instanceType.Buffer()
					<< " at position " << instances[j].GetPosition().ToString().Buffer()
					<< " with model name " << geometryName.Buffer()
				);
			}
		}
	}





	return 0;
}
