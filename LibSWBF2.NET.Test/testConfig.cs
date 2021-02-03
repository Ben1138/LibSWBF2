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


        public static void PrintUIntChars(uint enc)
        {
            for (int i = 0; i < 4; i++)
            {
                char c = (char) ((0x000000ff) & (enc >> (i * 8)));
                Console.Write("{0}", c);
            }
            Console.Write("\n");
        }


        public static int Main(string[] args)
        {   
            //PrintUIntChars(1752457584);
            //Console.WriteLine("0x{0:x}", GetUIntRep(args[0]));
            //return 0;

            TestBench.StartLogging(ELogType.Warning);

            Level level = TestBench.LoadAndTrackLVL(args[0]);
            if (level == null) return -1;

            World[] worlds = level.GetWorlds();
            foreach (World world in worlds)
            {
                Console.WriteLine("World: {0}", world.Name);
                //uint worldNameHash = HashUtils.GetFNV(world.Name);
                Config lighting = level.GetConfig(world.Name, ConfigType.LIGHTING);
                //Config lighting = level.GetConfig(0xc9827964, ConfigType.LIGHTING);

                if (lighting == null) continue;

                uint lightHash = HashUtils.GetFNV("Light");
                List<string> lightNames = lighting.GetStrings(lightHash);
                List<Config> lights = lighting.GetChildConfigs(lightHash);

                Console.WriteLine("\n\tLights: ");
                int i = 0;
                foreach (Config light in lights)
                {
                    Console.WriteLine("\n\t\tName: " + lightNames[i++]);
                    Console.WriteLine("\t\tColor: " + light.GetVec3(HashUtils.GetFNV("Color")).ToString());
                    Console.WriteLine("\t\tRegion: " + (light.IsPropertySet("Region") ?  light.GetString("Region") : "No region set!"));
                    Console.WriteLine("\t\tType: " + light.GetFloat(HashUtils.GetFNV("Type")).ToString());
                }

                Config globalLighting = lighting.GetChildConfig("GlobalLights");
                if (globalLighting == null) continue;
                
                Console.WriteLine("\n\tGlobal lighting config: ");
                Console.WriteLine("\t\tLight 1: " + globalLighting.GetString("Light1"));
                Console.WriteLine("\t\tLight 2: " + globalLighting.GetString("Light2"));
                Console.WriteLine("\t\tTop Ambient Color: " + globalLighting.GetVec3("Top").ToString());
                Console.WriteLine("\t\tBottom Ambient Color: " + globalLighting.GetVec3("Bottom").ToString());
            }


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
                int i = 0;
    
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
