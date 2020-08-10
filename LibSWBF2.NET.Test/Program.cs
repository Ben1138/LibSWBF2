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
            Level level = Level.FromFile(@"F:\SteamLibrary\steamapps\common\Star Wars Battlefront II\GameData\data\_lvl_pc\geo\geo1.lvl");

            Console.WriteLine("Is World Level: " + level.IsWorldLevel);
            Console.WriteLine("Models:");

            Model[] models = level.GetModels();
            foreach (Model model in models)
            {
                Console.WriteLine("\t" + model.Name);
            }

            Console.WriteLine("Done!");
            Console.ReadKey();
        }
    }
}
