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
    class Test
    {
        static void Main(string[] args)
        {
            {
                //Logger.SetLogLevel(ELogType.Warning);
                //Logger.OnLog += (LoggerEntry logEntry) => 
                //{
                //    Console.WriteLine(logEntry.ToString());
                //};

                Console.WriteLine("Loading... This might take a while...");
                Level level = Level.FromFile(@"/Users/will/Desktop/MLC.lvl");

                Model[] models = level.GetModels();
                foreach (Model model in models)
                {
                    Console.WriteLine("\n" + model.Name);

                    Segment[] segments = model.GetSegments(); 
                    int i = 0;
                    foreach (Segment seg in segments)
                    {
                        Console.WriteLine("\tSegment " + i++ + ": ");
                        float[] vBuf = seg.GetVertexBuffer();                        
                        string texName = seg.GetMaterialTexName();

                        Console.WriteLine("\t\t" + "Num verts: " + 
                                          vBuf.Length / 3 + 
                                        "\n \t\tTexture name: " +
                                          texName);
                    }
                    
                } 
            }
        }
    }
}
