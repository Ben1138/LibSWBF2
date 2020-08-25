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
                //Level level = Level.FromFile(@"/home/will/Desktop/tst1.lvl");
                Level level = Level.FromFile(@"/home/will/.wine32bit/drive_c/Program Files/Steam/steamapps/common/Star Wars Battlefront II/GameData/data/_lvl_pc/geo/geo1.lvl");

                Terrain terrain = level.GetTerrain();

                string printStr = "";

                foreach (var str in terrain.Names)
                {
                    printStr += (" " + str);
                }

                Console.WriteLine("Terrain texture names: " + printStr);
                
                /*Console.WriteLine("Indicies: ");

                int[] rawVerts = terrain.Indicies;

                for (int i = 0; i < rawVerts.Length; i+=3){
                    if (i % 200 == 0){
                        Console.WriteLine(i + ": (" + rawVerts[i] + ", " + rawVerts[i+1] + ", " + rawVerts[i+2] + ")");
                    }
                }*/

                Console.WriteLine("Done!");
            }

            Console.ReadKey();
        }
    }
}
