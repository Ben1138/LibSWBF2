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
                Logger.SetLogLevel(ELogType.Warning);
                Logger.OnLog += (LoggerEntry logEntry) => 
                {
                    Console.WriteLine(logEntry.ToString());
                };

                Console.WriteLine("Loading... This might take a while...");
                Level level = Level.FromFile(@"/Users/will/Desktop/geo1.lvl");
                //Level level = Level.FromFile(@"/home/will/.wine32bit/drive_c/Program Files/Steam/steamapps/common/Star Wars Battlefront II/GameData/data/_lvl_pc/geo/geo1.lvl");

                Model[] models = level.GetModels();
                foreach (Model model in models)
                {
                    Console.WriteLine("\t" + model.Name + "\n");

                    Segment[] segments = model.GetSegments(); 
                    foreach (Segment seg in segments)
                    {
                        Console.WriteLine("Getting seg vert buffer");
                        float[] vBuf = seg.GetVertexBuffer();
                        Console.WriteLine("Getting seg texname");

                        string texName = seg.GetMaterialTexName();
                        Console.WriteLine("\t\t" + "Num verts: " + 
                                          vBuf.Length / 3 + " Texture name: " +
                                          texName);
                    }
                } 
            }
        }
    }
}
