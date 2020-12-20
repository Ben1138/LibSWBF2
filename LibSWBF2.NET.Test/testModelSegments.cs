using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;



namespace LibSWBF2.NET.Test
{
    class ModelsSegmentsTest
    {
        static int Main(string[] args)
        {            
            TestBench.StartLogging(ELogType.Warning);

            Level level = TestBench.LoadAndTrackLVL(args[0]);
            if (level == null) return -1;
            
            Model[] models = level.GetModels();


            int j = 0;
            foreach (Model model in models)
            {
                if (model.IsSkeletalMesh)
                {
                    Console.WriteLine("\n" + model.Name + "'s bones: ");
                    
                    Bone[] bones = model.GetSkeleton();

                    for (int k = 0; k < bones.Length; k++)
                    {
                        Console.WriteLine("\tName: {0} Parent: {1}", bones[k].name, bones[k].parentName);
                    }
                }

                Segment[] segments = model.GetSegments(); 
                int i = 0;
                foreach (Segment seg in segments)
                {
                    Console.WriteLine("\n\tSegment " + i++ + ": ");
                    float[] vBuf = seg.GetVertexBuffer();                        
                    string texName = seg.GetMaterialTexName();

                    VertexWeight[] weights = seg.GetVertexWeights();

                    Console.WriteLine("\t\tTopology: {0}", seg.GetTopology());

                    //Console.WriteLine("\t\t{0} weights ---- {1} vertices.", weights.Length, seg.GetVertexBufferLength());


                    //byte[] data;

                    //Console.Write("\tTexture name: " + texName + " Format: ");
                    //level.GetTexture(texName, out int w, out int h, out data);
                }
            } 

            TestBench.StopLogging();
            
            return 0;
        }
    }
}
