#include "testing.h"



int main(int ac, char **av)
{
	if (ac < 4) return -1;


	String lvl_path = av[1];
	String animSetName = av[2];
	uint32_t animName = (uint32_t) FNVHash(av[3]);

	auto testLVLs = LoadAndTrackLVLs(lvl_path);

	if (testLVLs.size() == 0) return -1;






	return 0;
}
