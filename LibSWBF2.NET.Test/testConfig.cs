using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;
using LibSWBF2.Types;
using LibSWBF2.Enums;
using LibSWBF2.Utils;



namespace LibSWBF2.NET.Test
{
    class ConfigTest
    {

        public static uint GetUIntRep(string name)
        {
            uint result = 0;
            byte i = 0;
            foreach (char c in name)
            {
                result |= (((uint) c) << (8 * i)); 
                i++;           
            }
            return result;
        }


        public static int Main(string[] args)
        {   
            //Console.WriteLine("0x{0:x}", GetUIntRep(args[0]));
            //return 0;

            TestBench.StartLogging(ELogType.Warning);

            Level level = TestBench.LoadAndTrackLVL(args[0]);
            if (level == null) return -1;

            Config lighting = level.GetConfig(args[1], ConfigType.LIGHTING);

            uint lightHash = HashUtils.GetFNV("Light");
            List<string> lightNames = lighting.GetStrings(lightHash);
            List<Config> lights = lighting.GetChildConfigs(lightHash);

            Console.WriteLine("\nLights: ");
            int i = 0;
            foreach (Config light in lights)
            {
                Console.WriteLine("\n\tName: " + lightNames[i++]);
                Console.WriteLine("\tColor: " + light.GetVec3(HashUtils.GetFNV("Color")).ToString());
                Console.WriteLine("\tRegion: " + (light.IsPropertySet("Region") ?  light.GetString("Region") : "No region set!"));
                Console.WriteLine("\tType: " + light.GetFloat(HashUtils.GetFNV("Type")).ToString());
            }

            Config globalLighting = lighting.GetChildConfigs(HashUtils.GetFNV("GlobalLights"))[0];
            Console.WriteLine("\nGlobal lighting config: ");
            Console.WriteLine("\tLight 1: " + globalLighting.GetString("Light1"));
            Console.WriteLine("\tLight 2: " + globalLighting.GetString("Light2"));


            List<Config> effects = level.GetConfigs(ConfigType.EFFECT);

            Console.WriteLine("\nEffects: ");
            foreach (Config effect in effects)
            {
                Console.WriteLine("\tEffect name hash: 0x{0:x}", effect.name);
                Console.WriteLine("\t\tEmitter name: {0}", (effect.IsPropertySet("ParticleEmitter") ? effect.GetString("ParticleEmitter") : "No emitter set!"));
            }


            List<Config> paths = level.GetConfigs(ConfigType.PATH);
            Console.WriteLine("\nPath configs: ");
            foreach (Config path in paths)
            {
                Console.WriteLine("\tPath config: 0x{0:x}", path.name);
                i = 0;
    
                List<string> pathNames = path.GetStrings("Path");
                List<Config> childPaths = path.GetChildConfigs("Path");

                foreach (string pathName in pathNames)
                {
                    Console.WriteLine("\t\tPath {0} has {1} nodes.", pathName, childPaths[i++].GetFloat("Nodes"));
                }
            }            



            TestBench.StopLogging();

            return 1;
        }
    }
}
