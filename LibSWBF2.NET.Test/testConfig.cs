using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;
using LibSWBF2.Types;
using LibSWBF2.Utils;



namespace LibSWBF2.NET.Test
{
    class ConfigTest
    {
        public static int Main(string[] args)
        {   
            TestBench.StartLogging(ELogType.Warning);

            Level level = TestBench.LoadAndTrackLVL(args[0]);
            if (level == null) return -1;

            Config lighting = level.GetConfig(args[1]);

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

            TestBench.StopLogging();

            return 1;
        }
    }
}
