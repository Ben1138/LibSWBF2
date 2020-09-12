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

                Terrain terrain = level.GetTerrain();

                foreach (var str in terrain.Names)
                {
                    if (str == ""){
                        continue;
                    }

                    string printStr = "Texture name: " + str;
                    if (level.GetTexture(str, out byte[] data, out int width, out int height))
                    {
                        printStr += (" width: " + width + " height: " + height + " bytes length: " + data.Length);
                    }
                    else 
                    {
                        printStr += " lookup failed.";
                    }
                    Console.WriteLine(printStr);
                }

                terrain.GetHeightMap(out uint dim, out uint dimScale, out float[] heightMapData);
                terrain.GetBlendMap(out dim, out uint numLayers, out byte[] blendMapData);
            }

            Console.ReadKey();
        }
    }
}
