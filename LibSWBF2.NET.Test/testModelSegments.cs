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
            TestBench testBench = new TestBench();

            Container container = testBench.LoadAndTrackContainer(new List<string>(args), out List<Level> levels);


            Level level = levels[0];
            if (level == null) return -1;
            
            Model[] models = level.Get<Model>();


            foreach (Model model in models)
            {   
                Console.WriteLine("\n" + model.Name + ": ");

                /*
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
                */
                
                Segment[] segments = model.GetSegments(); 
                int i = 0;
                foreach (Segment seg in segments)
                {
                    
                    Console.WriteLine("\tSegment " + i++ + ": ");
                    float[] vBuf = seg.GetVertexBuffer<float>();                        
                    //string texName = seg.GetMaterialTexName();

                    VertexWeight[] weights = seg.GetVertexWeights();

                    Console.WriteLine("\t\tTopology: {0}", seg.Topology);


                    float[] buffer = seg.GetNormalsBuffer<float>();
                    Console.WriteLine("\t\tNum positions: {0}, Num normals: {1}", vBuf.Length/3, buffer.Length/3);

                    if (model.IsSkinned)
                    {
                        Console.WriteLine("\t\t{0} weights ---- {1} vertices.", weights.Length, seg.GetVertexBufferLength());
                        Console.WriteLine("\t\tIs pretransformed: {0}", seg.IsPretransformed);
                    }
                    else
                    {
                        Console.WriteLine("\t\tSegment belongs to bone: {0}", seg.BoneName);
                    }

                    Material mat = seg.Material;

                    Console.WriteLine("\n\t\tMaterial textures used: ");

                    foreach (string texName in mat.Textures)
                    {   
                        if (texName == "") continue;

                        Console.Write("\t\t\t" + texName);
                        Texture tex = level.Get<Texture>(texName);
                        if (tex != null)
                        {
                            Console.WriteLine(" Height: {0} Width: {1}", tex.Height, tex.Width);
                        }                        
                    }

                    Console.WriteLine("\t\tMaterial flags: ");
                    Console.WriteLine("\t\t\t{0}", seg.Material.MaterialFlags);
                }
            }
            
            return 0;
        }
    }
}
