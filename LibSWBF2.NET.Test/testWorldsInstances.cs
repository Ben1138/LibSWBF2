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
    class WorldInstancesRegionsTest
    {
        static int Main(string[] args)
        {
            TestBench testBench = new TestBench();

            Container container = testBench.LoadAndTrackContainer(new List<string>(args), out List<Level> lvls);

            Level level = lvls[0];
            if (level == null)
            {
                return -1;
            }
        
            World[] worlds = level.GetWrappers<World>();

            foreach (World world in worlds)
            {
                Console.WriteLine("\n" + world.name);
                
                Console.WriteLine("  Instances: ");
                foreach (Instance instance in world.GetInstances())
                {
                    var ec = container.FindWrapper<EntityClass>(instance.entityClassName);

                    if (ec == null)
                    {
                        continue;
                    }

                    string baseName = ec.GetBaseName();

                    
                    string instName = instance.name;
                    Vector4 rot = instance.rotation;
                    Vector3 pos = instance.position;

                    Console.WriteLine("\n\tInstance: " + instName);
                    
                    Console.WriteLine("\t  Class: " + ec.name);
                    Console.WriteLine("\t  Parent: " + baseName);
                    Console.WriteLine("\t  Rotation: " + rot.ToString());
                    Console.WriteLine("\t  Position: " + pos.ToString());

                    Console.WriteLine("\t  Overridden properties: ");
                    if (instance.GetOverriddenProperties(out uint[] props, out string[] values))
                    {
                        for (int j = 0; j < props.Length; j++)
                        {
                            Console.WriteLine("\t    Hash: {0}, Value: {1}", props[j], values[j]);
                        }
                    }                  
                }


                Console.WriteLine("  Regions:");
                foreach (Region region in world.GetRegions())
                {
                    Console.WriteLine("\n\tRegion: " + region.name);
                
                    Console.WriteLine("\t  Size: " + region.size.ToString());
                    Console.WriteLine("\t  Rotation: " + region.rotation.ToString());
                    Console.WriteLine("\t  Type: " + region.type);
                } 
            }

            return 1;
        }
    }
}
