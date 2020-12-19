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
                TestBench.StartLogging(ELogType.Warning);

                Level level = TestBench.LoadAndTrackLVL(args[0]);
                if (level == null) return -1;

                
                World[] worlds = level.GetWorlds();

                Console.WriteLine(worlds.Length);
                Console.WriteLine(worlds[0].Name);

                int k = 0;
                foreach (World world in worlds)
                {
                    Console.WriteLine(k++);
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

                TestBench.StopLogging();
            }
        }
    }
}
