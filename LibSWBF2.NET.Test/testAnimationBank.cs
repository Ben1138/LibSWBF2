using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;
using LibSWBF2.Types;
using LibSWBF2.Utils;


namespace LibSWBF2.NET.Test
{
    class AnimationBankTest
    {
        static int Main(string[] args)
        {
            if (args.Length < 3) return -1;

            TestBench testBench = new TestBench();

            testBench.LoadAndTrackContainer(args[0], out Level level);
            if (level == null){
                return -1;
            } 

            string animSetName = args[1];
            string animationName = args[2];


            AnimationSkeleton animSkel = level.Get<AnimationSkeleton>(animSetName);
            if (animSkel != null)
            {
                Console.WriteLine("Found animation skel of name: {0} with bones: ", animSkel.GetName());

                Joint[] animSkelJoints = animSkel.GetJoints();
                for (int k = 0; k < animSkelJoints.Length; k++)
                {
                    Joint j = animSkelJoints[k];
                    Console.WriteLine("  {0}: Name 0x{1:x} Rot: {2} Pos: {3}", k, j.BoneCRC, j.BaseRotation.ToString(), j.BasePosition.ToString());
                }
            }




            List<uint> boneCRCs = new List<uint>();

            for (int i = 0; i < args.Length - 3; i++)
            {
                boneCRCs.Add(HashUtils.GetCRC(args[3 + i]));
            }


            AnimationBank bank = level.Get<AnimationBank>(animSetName);
            if (bank == null)
            {
                Console.WriteLine("Animation bank not found!");
                return -1;
            }


            uint[] animHashes = bank.GetAnimationCRCs();

            foreach (uint hash in animHashes)
            {
                if (hash == HashUtils.GetCRC(animationName))
                {
                    bank.GetAnimationMetadata(hash, out int numFrames, out int numBones);


                    Console.WriteLine("Printing bone curves for {0}(0x{1:X})", animationName, hash);
                    Console.WriteLine("{0} transforms {1} bones over {2} frames...", animationName, numBones, numFrames);
                    for (int i = 0; i < boneCRCs.Count; i++)
                    {
                        string boneName = args[3 + i];
                        uint boneHash   = boneCRCs[i];

                        Console.WriteLine("\tBone #{0}: {1} (0x{2:X})", i, boneName, boneHash);

                        bool status = bank.GetCurve(hash, boneHash, 0,
                            out ushort[] inds, out float[] values);

                        if (!status)
                        {
                            Console.WriteLine("\t\tFailed to fetch curve!");
                            return -1;
                        }

                        Console.WriteLine("\t\tRotation X component: ");

                        for (int j = 0; j < inds.Length && j < 5; j++)
                        {
                            Console.WriteLine("\t\t\t{0}: {1}", inds[j], values[j]);
                        }
                    }

                    return 0;                    
                }
            }

            Console.WriteLine("Animation not found!");
            return -1;
        }
    }
}
