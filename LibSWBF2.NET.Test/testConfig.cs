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
            /*
            string tstFX = "com_sfx_ord_flame";
            var fxConfig = container.FindConfig(ConfigType.Effect, tstFX);

            Field lEmitter = fxConfig.GetField("ParticleEmitter");
        

            Console.WriteLine("Num particles: {0}", (int) lEmitter.scope.GetField("MaxParticles").GetVec2().Y);

            Field lTransformer = lEmitter.scope.GetField("Transformer");
            Field lSpawner = lEmitter.scope.GetField("Spawner");

            if (lTransformer == null)
            {
                Console.WriteLine("Transformer is null!"); //return 0;
            }

            if (lSpawner == null)
            {
                Console.WriteLine("Spawner is null!"); //return 0;
            }

            Console.WriteLine("Start size: {0}", lSpawner.scope.GetField("Size").GetVec3().Z);
            //Console.WriteLine("Lifetime: {0}", lTransformer.GetChildConfig("Position").GetFloat("LifeTime"));

            //return 1;
            */
            
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
                    Field domeInfo = skydome.GetField("DomeInfo");
                    if (domeInfo != null)
                    {
                        List<Field> domeModelConfigs = domeInfo.scope.GetFields("DomeModel");
                        foreach (Field domeModelConfig in domeModelConfigs)
                        {
                            string geometryName = domeModelConfig.scope.GetField("Geometry").GetString();
                            Console.WriteLine("  Dome geometry: " + geometryName);
                        }
                    }
                }

                Config lighting = level.GetConfig(world.name, ConfigType.Lighting);
                if (lighting == null) continue;
                Console.WriteLine("Lighting: ");

                uint lightHash = HashUtils.GetFNV("Light");
                List<Field> lights = lighting.GetFields(lightHash);

                Console.WriteLine("\n  Lights: ");
                int i = 0;
                foreach (Field light in lights)
                {
                    Console.WriteLine("\n\tName: " + light.GetString());
                    Console.WriteLine("\tColor: " + light.scope.GetField("Color").GetVec3().ToString());
                    Console.WriteLine("\tType: " + light.scope.GetField("Type").GetFloat().ToString());
                }

                Field globalLighting = lighting.GetField("GlobalLights");
                if (globalLighting == null) continue;
                
                Console.WriteLine("\n  Global lighting config: ");
                Console.WriteLine("\tLight 1: " + globalLighting.scope.GetField("Light1").GetString());
                Console.WriteLine("\tLight 2: " + globalLighting.scope.GetField("Light2").GetString());
                Console.WriteLine("\tTop Ambient Color: " + globalLighting.scope.GetField("Top").GetVec3().ToString());
                Console.WriteLine("\tBottom Ambient Color: " + globalLighting.scope.GetField("Bottom").GetVec3().ToString());
            }


            List<Config> effects = level.GetConfigs(ConfigType.Effect);

            Console.WriteLine("\nEffects: ");
            foreach (Config effect in effects)
            {
                Console.WriteLine("  Effect name hash: 0x{0:x}", effect.name);
                //Console.WriteLine("\tEmitter name: {0}", (effect.IsPropertySet("ParticleEmitter") ? effect.GetString("ParticleEmitter") : "No emitter set!"));
            }


            List<Config> paths = level.GetConfigs(ConfigType.Path);
            Console.WriteLine("\nPath configs: ");
            foreach (Config path in paths)
            {
                Console.WriteLine("  Path config: 0x{0:x}", path.name);
                int i = 0;
    
                List<Field> pathNames = path.GetFields("Path");

                foreach (Field pathName in pathNames)
                {
                    Console.WriteLine("\tPath {0} has {1} nodes.", pathName.GetString(), pathName.scope.GetField("Node").GetFloat());
                }
            }

            container.Delete();

            return 1;
        }
    }
}
