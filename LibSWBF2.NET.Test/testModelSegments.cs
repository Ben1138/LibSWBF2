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
        static void Main(string[] args)
        {
            {
                TestBench.StartLogging(ELogType.Warning);

                Level level = TestBench.LoadAndTrackLVL(args[0]);
                if (level == null) return -1;
                
                Model[] models = level.GetModels();


                Console.WriteLine(models.Length);
                int j = 0;
                foreach (Model model in models)
                {
                    if (!model.Name.Contains("sky"))
                    {
                        //continue;
                    }

                    Console.WriteLine("\n" + model.Name);

                    Segment[] segments = model.GetSegments(); 
                    int i = 0;
                    foreach (Segment seg in segments)
                    {
                        Console.WriteLine("\n\tSegment " + i++ + ": ");
                        float[] vBuf = seg.GetVertexBuffer();                        
                        string texName = seg.GetMaterialTexName();
                        string materialFlags = seg.GetMaterialFlags();

                        /*
                        Console.WriteLine("\t\t" + "Num verts: " + 
                                          vBuf.Length / 3 + 
                                        "\n \t\tTexture name: " +
                                          texName +
                                        "\n \t\tMaterial traits: " +
                                          materialFlags);
                        */

                        byte[] data;

                        Console.Write("\tTexture name: " + texName + " Format: ");
                        level.GetTexture(texName, out int w, out int h, out data);
                    }
                } 
            }
        }
    }
}
