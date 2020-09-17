using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LibSWBF2.Logging;
using LibSWBF2.Wrappers;
using LibSWBF2.Types;

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
                
                Level level = Level.FromFile(@"/Users/will/Desktop/MLC.lvl");
                //Level level = Level.FromFile(@"/Volumes/bootable/stockdata/_lvl_pc/kas/kas2.lvl");
                
                World[] worlds = level.GetWorlds();

                foreach (World world in worlds)
                {
                    Console.WriteLine("\n" + world.Name);

                    Instance[] instances = world.GetInstances(); 
                    
                    int i = 0;
                    
                    foreach (Instance instance in instances)
                    {
                        Console.WriteLine("\tInstance " + i++ + ": ");
                        
                        string instName = instance.Name;
                        Vector4 rot = instance.GetRotation();
                        Vector3 pos = instance.GetPosition();

                        Console.WriteLine("\t\t" + "Name: " + instName + 
                                        "\n\t\tRotation: " + rot.ToString() +
                                        "\n\t\tPosition: " + pos.ToString());
                    }
                } 
            }
        }
    }
}
