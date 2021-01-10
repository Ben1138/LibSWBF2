#include "testing.h"

using LibSWBF2::CRC;


int main(int ac, char **av)
{
	if (ac < 4) return -1;

	List<String> paths;

	for (int i = 1; i < ac - 2; i++)
	{
		paths.Add(av[i]);
	}

	String animSetName = av[ac - 2];
	String animName = av[ac - 1];
	uint32_t animNameCRC = (uint32_t) CRC::CalcLowerCRC(animName.Buffer());
	//uint32_t animName = (uint32_t) CRC::CalcLowerCRC(av[3]);

	//paths.Add(lvl_path);
	auto container = LoadAndTrackContainer(paths);

	auto animSet = container -> FindAnimationBank(animSetName);


	if (animSet == nullptr)
	{
		COUT("\nAnimation bank not found");
		return -1;
	}


	if (!animSet -> ContainsAnim(animNameCRC))
	{
		COUT(std::hex << animName.Buffer() << " doesn't belong to queried bank! This set contains: ");

		List<uint32_t> hashes = animSet -> GetAnimHashes();

		for (int i = 0; i < hashes.Size(); i++)
		{
			COUT("\t" << std::hex << hashes[i]);
		}

		return -1;
	}



	//List<Bone> bones;

	COUT(fmt::format("\n\nPrinting curves for anim {}", animName.Buffer()).c_str());

	auto bones = animSet -> GetBoneHashes();
	std::vector<uint32_t> bonesSorted;
	for (int i = 0; i < bones.Size(); i++)
	{
		if (std::count(bonesSorted.begin(), bonesSorted.end(), bones[i]) == 0)
			bonesSorted.push_back(bones[i]);
	}
	std::sort(bonesSorted.begin(), bonesSorted.end()); 


	int numFrames, numBones;

	animSet -> GetAnimationMetadata(animNameCRC, numFrames, numBones);



	//if (model -> GetSkeleton(bones))
	//{
		for (int i = 0; i < bonesSorted.size(); i++)
		{
			List<uint16_t> indices, indices1, indices2, indices3;
			List<float> values, values1, values2, values3;


			//Bone &cur_bone = bones[i];
			//uint32_t boneCRC = (uint32_t) CRC::CalcLowerCRC(cur_bone.m_BoneName.Buffer());
			uint32_t boneCRC = bonesSorted[i];

			//COUT(fmt::format("\tBone #{0}, 0x{1:x}\n", i, boneCRC));
			COUT(fmt::format("0x{0:x}", boneCRC).c_str());


			/*
			animSet -> GetCurve(animNameCRC, boneCRC, 4, indices,  values);
			animSet -> GetCurve(animNameCRC, boneCRC, 5, indices1, values1);
			animSet -> GetCurve(animNameCRC, boneCRC, 6, indices2, values2);

			for (int j = 0; j < numFrames; j++)
			{
	        	COUT(fmt::format("\t{}: ({}, {}, {})", j, values[j], values1[j], values2[j]));
			}
			*/

			
			for (uint16_t j = 0; j < 7; j++)
			{
				if (!animSet -> GetCurve(animNameCRC, boneCRC, j, indices, values))
				{
					COUT("Bone not found or error occurred");
					return -1;
				}


				if (j < 4)
				{
					COUT(fmt::format("\t\tRot {}: ", j));
				}
				else
				{
					COUT(fmt::format("\t\tLoc {}: ", j - 4));
				}

				for (int k = 0; k < 5 && k < indices.Size(); k++)
				{
					COUT("\t\t\t" << indices[k] << ": " << values[k]);
				}
			}
			
		}
	//}


	return 0;
}
