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
            Model lastModel = null;

            {
                Logger.SetLogLevel(ELogType.Warning);
                Logger.OnLog += (LoggerEntry logEntry) => 
                {
                    Console.WriteLine(logEntry.ToString());
                };

                Console.WriteLine("Loading... This might take a while...");
                Level level = Level.FromFile(@"/Users/will/Desktop/omni.lvl");
                Terrain terrain = level.GetTerrain();

                Console.WriteLine("Terrain texture names: " + terrain.Names);
                Console.WriteLine("Indicies: ");

                int[] rawVerts = terrain.Indicies;

                for (int i = 0; i < rawVerts.Length; i+=3){
                    //Console.WriteLine(i + ": (" + rawVerts[i] + ", " + rawVerts[i+1] + ", " + rawVerts[i+2] + ")");
                }

                Console.WriteLine("Done!");
            }

            Console.ReadKey();
        }
    }
}
