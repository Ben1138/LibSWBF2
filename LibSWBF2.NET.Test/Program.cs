using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LibSWBF2.Wrappers;

namespace LibSWBF2.NET.Test
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Loading...");
            Level level = Level.FromFile(@"F:\SteamLibrary\steamapps\common\Star Wars Battlefront II\GameData\data\_lvl_pc\geo\geo1.lvl");

            Console.WriteLine("Is World Level: " + level.IsWorldLevel);
            Console.WriteLine("Models:");

            Model[] models = level.GetModels();
            foreach (Model model in models)
            {
                Console.WriteLine("\t" + model.Name);
            }
        }
    }
}
