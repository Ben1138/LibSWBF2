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
    class InstancesTest
    {
        static int Main(string[] args)
        {
            {
                TestBench.StartLogging(ELogType.Warning);

                Level level = TestBench.LoadAndTrackLVL(args[0]);
                if (level == null)
                {
                    TestBench.StopLogging();
                    return -1;
                }
            
                World[] worlds = level.GetWorlds();

                int k = 0;
                foreach (World world in worlds)
                {
                    Console.WriteLine("\n" + world.Name);

                    Instance[] instances = world.GetInstances(); 
                    
                    int i = 0;
                    
                    foreach (Instance instance in instances)
                    {

                        var ec = level.GetEntityClass(instance.GetEntityClassName());

                        if (ec == null)
                        {
                            continue;
                        }


                        Console.WriteLine("\tInstance " + i++ + ": ");
                        
                        string instName = instance.Name;
                        Vector4 rot = instance.GetRotation();
                        Vector3 pos = instance.GetPosition();

                        Console.WriteLine("\t\t" + "Name: " + instName +
                                        "  Class: " + instance.GetEntityClassName() + 
                                        "  Rotation: " + rot.ToString() +
                                        "  Position: " + pos.ToString());

                        //Console.WriteLine("\t\tAttached ODF = " + ec.GetProperty("AttachODF"));

                    }
                } 

                TestBench.StopLogging();
                return 1;
            }
        }
    }
}
