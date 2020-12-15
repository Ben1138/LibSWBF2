#include "testing.h"

using LibSWBF2::FNV;


int main(int ac, char **av)
{
	if (ac < 4) return -1;

	List<String> paths;
	String lvl_path = av[1];
	String animSetName = av[2];
	uint32_t animName = 0xfd3418d4;//(uint32_t) FNV::Hash(av[3]);

	paths.Add(lvl_path);
	auto testLVLs = LoadAndTrackLVLs(paths);

	if (testLVLs.size() == 0) return -1;

	auto testLVL = testLVLs[0];

	auto animSet = testLVL -> GetAnimationSet(animSetName);
	auto model = testLVL -> GetModel(animSetName);

	if (model == nullptr || animSet == nullptr || !model -> IsSkeletalMesh())
	{
		COUT(animSetName.Buffer() << " must refer to an anim set and model sharing the same name...");
		return -1;
	}

	if (!animSet -> ContainsAnim(animName))
	{
		COUT(std::hex << animName << " doesn't belong to queried set! This set contains: ");

		List<uint32_t> hashes = animSet -> GetAnimHashes();

		for (int i = 0; i < hashes.Size(); i++)
		{
			COUT("\t" << std::hex << hashes[i]);
		}



		return -1;
	}

	List<Bone> bones;

	COUT(fmt::format("Printing curves for anim {}", animSetName.Buffer()).c_str());

	if (model -> GetSkeleton(bones))
	{

		COUT("Model bone hashes: ");
		for (int i = 0; i < bones.Size(); i++)
		{
			COUT("\t" << std::hex << (uint32_t) FNV::Hash(bones[i].m_BoneName));
		}

		COUT("Bones in anim: ");
		List<uint32_t> animBones = animSet -> GetBoneHashes();
		for (int i = 0; i < animBones.Size(); i++)
		{
			COUT("\t" << std::hex << animBones[i] << std::dec);
		}


		for (int i = 0; i < bones.Size(); i++)
		{
			List<uint16_t> indices;
			List<float> values;

			Bone &cur_bone = bones[i];
			uint32_t boneHash = (uint32_t) FNV::Hash(cur_bone.m_BoneName);

			COUT(fmt::format("\n\n\tBone #{}, {}\n", i, cur_bone.m_BoneName.Buffer()));

			for (uint16_t j = 0; j < 7; j++)
			{
				if (!animSet -> GetCurve(animName, animBones[i], j, indices, values))
				{
					COUT("Bone not found or error occurred");
				}

				if (j < 4)
				{
					COUT(fmt::format("\t\tRot {}: ", j));
				}
				else
				{
					COUT(fmt::format("\t\tLoc {}: ", j - 4));
				}

				for (int k = 0; k < indices.Size(); k++)
				{
					COUT("\t\t\t" << indices[k] << ": " << values[k]);
				}
			}
		}
	}

	return 0;
}
