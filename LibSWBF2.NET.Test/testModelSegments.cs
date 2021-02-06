using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;
using LibSWBF2.Utils;



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


            foreach (Model model in models)
            {   
                Console.WriteLine("\n" + model.name + ": ");


                if (model.isSkeletonBroken)
                {
                    Console.WriteLine("\tSkeleton is broken!!");
                }

                Console.WriteLine("\tSkeleton: ");
                
                Bone[] bones = model.skeleton;

                for (int k = 0; k < bones.Length; k++)
                {
                    Console.WriteLine("\t\tName: {0} Parent: {1}", bones[k].name, bones[k].parentName);
                }
                
                Segment[] segments = model.GetSegments(); 
                int i = 0;
                foreach (Segment seg in segments)
                {
                    Console.WriteLine("\tSegment " + i++ + ": ");
                    float[] vBuf = seg.GetVertexBuffer<float>();                        
                    //string texName = seg.GetMaterialTexName();

                    VertexWeight[] weights = seg.GetVertexWeights();

                    Console.WriteLine("\t\tTopology: {0}", seg.topology);


                    float[] buffer = seg.GetNormalsBuffer<float>();
                    Console.WriteLine("\t\tNum positions: {0}, Num normals: {1}", vBuf.Length/3, buffer.Length/3);

                    if (model.isSkinned)
                    {
                        Console.WriteLine("\t\t{0} weights ---- {1} vertices.", weights.Length, seg.GetVertexBufferLength());
                        Console.WriteLine("\t\tIs pretransformed: {0}", seg.isPretransformed);
                    }
                    else
                    {
                        Console.WriteLine("\t\tSegment belongs to bone: {0}", seg.boneName);
                    }

                    Material mat = seg.material;

                    Console.WriteLine("\n\t\tMaterial textures used: ");

                    foreach (string texName in mat.textures)
                    {   
                        if (texName == "") continue;

                        Console.Write("\t\t\t" + texName);
                        Texture tex = level.GetTexture(texName);
                        if (tex != null)
                        {
                            Console.WriteLine(" Height: {0} Width: {1}", tex.height, tex.width);
                        }                        
                    }

                    Console.WriteLine("\t\tMaterial flags: ");
                    Console.WriteLine("\t\t\t" + EnumUtils.MaterialFlagsToString(mat.materialFlags));
                }
            } 

            TestBench.StopLogging();
            
            return 0;
        }
    }
}
