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
            Logger.SetLogLevel(ELogType.Warning);
            Logger.OnLog += (LoggerEntry logEntry) => 
            {
                Console.WriteLine(logEntry.ToString());
            };

            Console.WriteLine("Loading... This might take a while...");
            
            //Level level = Level.FromFile(@"F:\SteamLibrary\steamapps\common\Star Wars Battlefront II\GameData\data\_lvl_pc\geo\geo1.lvl");
            //Level level = Level.FromFile(@"/Users/will/Desktop/MLC.lvl");
            Level level = Level.FromFile(@"/home/will/Desktop/geo1.lvl");
            //Level level = Level.FromFile(@"/home/will/Desktop/geo1.lvl");
            //Level level = Level.FromFile(@"/Users/will/Desktop/geo1.lvl");

            Model[] models = level.GetModels();
            foreach (Model model in models)
            {
                Console.WriteLine("\nModel: " + model.Name);
                CollisionMesh mesh = model.GetCollisionMesh();

                Console.WriteLine("\tNum collision indices:   " + mesh.GetIndices().Length.ToString());
                Console.WriteLine("\tNum collision verticies: " + mesh.GetVertices().Length.ToString());
            }

            Console.WriteLine("Done!");
        }
    }
}
