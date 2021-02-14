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
        /*
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
        */


        public static int Main(string[] args)
        {   
            TestBench testBench = new TestBench();

            Container container = testBench.LoadAndTrackContainer(new List<string>(args), out List<Level> levels);
            
            Level level = levels[0];
            if (level == null) return -1;

            World[] worlds = level.GetWrappers<World>();
            foreach (World world in worlds)
            {
                Console.WriteLine("\nWorld: {0}", world.name);

                //Test for crash...
                Config skydome = container.FindConfig(ConfigType.Skydome, world.skydomeName);
                if (skydome != null)
                {
                    Console.WriteLine("Skydome: {0} (0x{1:x})", world.skydomeName, HashUtils.GetFNV(world.name));
                    Config domeInfo = skydome.GetChildConfig("DomeInfo");
                    if (domeInfo != null)
                    {
                        List<Config> domeModelConfigs = domeInfo.GetChildConfigs("DomeModel");
                        foreach (Config domeModelConfig in domeModelConfigs)
                        {
                            string geometryName = domeModelConfig.GetString("Geometry");
                            Console.WriteLine("  Dome geometry: " + geometryName);
                        }
                    }
                }

                Config lighting = level.GetConfig(world.name, ConfigType.Lighting);
                if (lighting == null) continue;
                Console.WriteLine("Lighting: ");

                uint lightHash = HashUtils.GetFNV("Light");
                List<string> lightNames = lighting.GetStrings(lightHash);
                List<Config> lights = lighting.GetChildConfigs(lightHash);

                Console.WriteLine("\n  Lights: ");
                int i = 0;
                foreach (Config light in lights)
                {
                    Console.WriteLine("\n\tName: " + lightNames[i++]);
                    Console.WriteLine("\tColor: " + light.GetVec3(HashUtils.GetFNV("Color")).ToString());
                    Console.WriteLine("\tRegion: " + (light.IsPropertySet("Region") ?  light.GetString("Region") : "No region set!"));
                    Console.WriteLine("\tType: " + light.GetFloat(HashUtils.GetFNV("Type")).ToString());
                }

                Config globalLighting = lighting.GetChildConfig("GlobalLights");
                if (globalLighting == null) continue;
                
                Console.WriteLine("\n  Global lighting config: ");
                Console.WriteLine("\tLight 1: " + globalLighting.GetString("Light1"));
                Console.WriteLine("\tLight 2: " + globalLighting.GetString("Light2"));
                Console.WriteLine("\tTop Ambient Color: " + globalLighting.GetVec3("Top").ToString());
                Console.WriteLine("\tBottom Ambient Color: " + globalLighting.GetVec3("Bottom").ToString());
            }


            List<Config> effects = level.GetConfigs(ConfigType.Effect);

            Console.WriteLine("\nEffects: ");
            foreach (Config effect in effects)
            {
                Console.WriteLine("  Effect name hash: 0x{0:x}", effect.name);
                Console.WriteLine("\tEmitter name: {0}", (effect.IsPropertySet("ParticleEmitter") ? effect.GetString("ParticleEmitter") : "No emitter set!"));
            }


            List<Config> paths = level.GetConfigs(ConfigType.Path);
            Console.WriteLine("\nPath configs: ");
            foreach (Config path in paths)
            {
                Console.WriteLine("  Path config: 0x{0:x}", path.name);
                int i = 0;
    
                List<string> pathNames = path.GetStrings("Path");
                List<Config> childPaths = path.GetChildConfigs("Path");

                foreach (string pathName in pathNames)
                {
                    Console.WriteLine("\tPath {0} has {1} nodes.", pathName, childPaths[i++].GetFloat("Nodes"));
                }
            }

            return 1;
        }
    }
}
