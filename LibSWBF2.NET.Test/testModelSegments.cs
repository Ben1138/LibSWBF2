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

            Container container = testBench.LoadAndTrackContainer(args[0], out Level level);

            if (level == null) return -1;
            
            Model[] models = level.Get<Model>();


            foreach (Model model in models)
            {   
                Console.WriteLine("\n" + model.Name + ": ");

                //if (model.Name != args[1]) continue;


                
                if (model.IsSkeletonBroken)
                {
                    Console.WriteLine("\tSkeleton is broken!!");
                }

                Console.WriteLine("\tSkeleton: ");
                foreach (Bone bone in model.Skeleton)
                {
                    Console.WriteLine("\t\tName: {0} Parent: {1}", bone.Name, bone.ParentName);
                }
                
                
                Segment[] segments = model.GetSegments(); 
                int i = 0;
                foreach (Segment seg in segments)
                {
                    string MNAM = seg.Tag;
                    if (MNAM == "") continue;

                    
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

                    string bone = seg.BoneName;
                    //string MNAM = seg.MNAM;

                    if (bone != "")
                    {
                        Console.WriteLine("\t\tSegment belongs to bone: {0}", bone);
                    }

                    if (MNAM != "")
                    {
                        Console.WriteLine("\t\tSegment has MNAM: {0}", MNAM);
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
