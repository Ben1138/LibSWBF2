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

                Terrain terrain = level.GetTerrains()[0];

                foreach (var str in terrain.GetTextureNames()){
                    
                    if (str == ""){
                        continue;
                    }

                    Console.Write("Texture name: " + str);
                    if (level.GetTexture(str, out int width, out int height, out byte[] data)){
                        Console.WriteLine(" width: " + width + " height: " + height + " bytes length: " + data.Length);
                    } else {
                        Console.WriteLine(" lookup failed.");
                    }
                }
                
                terrain.GetHeightMap(out uint dim, out uint dimScale, out float[] heightMapData);
                terrain.GetBlendMap(out dim, out uint numLayers, out byte[] blendMapData);
            }
        }
    }
}
