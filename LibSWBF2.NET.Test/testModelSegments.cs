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
                //Level level = Level.FromFile(@"/Volumes/bootable/stockdata/_lvl_pc/yav/yav1.lvl");
                //Level level = Level.FromFile(@"C:\Program Files (x86)\Steam\steamapps\common\Star Wars Battlefront II\GameData\data\_lvl_pc\yav\yav1.lvl");

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
