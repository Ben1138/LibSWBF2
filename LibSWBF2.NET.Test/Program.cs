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
    class Program
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
                Level level = Level.FromFile(@"/Users/will/Desktop/MLC.lvl");

                Console.WriteLine("Is World Level: " + level.IsWorldLevel);
                Console.WriteLine("Terrain texture names: ");

                Terrain terrain = level.GetTerrain();
                Console.WriteLine(terrain.Names);

                //level.Delete();
                Console.WriteLine("Done!");
            }

            Console.ReadKey();
        }
    }
}
