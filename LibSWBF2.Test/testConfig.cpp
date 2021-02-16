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

	const Config* cfg = testLVL -> GetConfig(LibSWBF2::EConfigType::Effect, "com_sfx_ord_flame"_fnv);

	Field emitter = cfg -> GetField("ParticleEmitter"_fnv);

	Field spawner = emitter.scope.GetField("Spawner"_fnv);
	COUT(fmt::format("Spawner size field: {}", spawner.scope.GetField("Size"_fnv).GetVector3().m_Z).c_str());

	Field xformer = emitter.scope.GetField("Transformer"_fnv);
	COUT(fmt::format("XFormer time field: {}", xformer.scope.GetField("Lifetime"_fnv).GetFloat()).c_str());


	return 0;
}
