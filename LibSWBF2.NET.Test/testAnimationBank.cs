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
    class AnimationSetTest
    {
        static int Main(string[] args)
        {
            if (args.Length < 3) return -1;

            TestBench.StartLogging(ELogType.Warning);

            Level level = TestBench.LoadAndTrackLVL(args[0]);
            if (level == null){
                TestBench.StopLogging();
                return -1;
            } 

            string animSetName = args[1];
            string animationName = args[2];

            List<uint> boneCRCs = new List<uint>();

            for (int i = 0; i < args.Length - 3; i++)
            {
                boneCRCs.Add(HashUtils.GetCRC(args[3 + i]));
            }


            AnimationSet set = level.GetAnimationSet(animSetName);
            if (set == null)
            {
                Console.WriteLine("Animation set not found!");
                TestBench.StopLogging();
                return -1;
            }


            uint[] animHashes = set.GetAnimationCRCs();

            foreach (uint hash in animHashes)
            {
                if (hash == HashUtils.GetCRC(animationName))
                {
                    set.GetAnimationMetadata(hash, out int numFrames, out int numBones);


                    Console.WriteLine("Printing bone curves for {0}(0x{1:X})", animationName, hash);
                    Console.WriteLine("{0} transforms {1} bones over {2} frames...", animationName, numBones, numFrames);
                    for (int i = 0; i < boneCRCs.Count; i++)
                    {
                        string boneName = args[3 + i];
                        uint boneHash   = boneCRCs[i];

                        Console.WriteLine("\tBone #{0}: {1} (0x{2:X})", i, boneName, boneHash);

                        bool status = set.GetCurve(hash, boneHash, 0,
                            out ushort[] inds, out float[] values);

                        if (!status)
                        {
                            Console.WriteLine("\t\tFailed to fetch curve!");
                            TestBench.StopLogging();
                            return -1;
                        }

                        Console.WriteLine("\t\tRotation X component: ");

                        for (int j = 0; j < inds.Length && j < 5; j++)
                        {
                            Console.WriteLine("\t\t\t{0}: {1}", inds[j], values[j]);
                        }
                    }

                    TestBench.StopLogging();
                    return 0;                    
                }
            }

            Console.WriteLine("Animation not found!");
            TestBench.StopLogging();
            return -1;
        }
    }
}
