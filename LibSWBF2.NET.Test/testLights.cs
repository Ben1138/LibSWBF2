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

                Light[] lights = level.GetLights();

                foreach (var light in lights)
                {
                    //Console.WriteLine(light.ToString());
                }

                if (level.GetGlobalLightingConfig(
                        out Vector3 topCol, out Vector3 bottomCol,
                        out Light light1, out Light light2))
                {
                    Console.WriteLine("Global lighting config: ");
                    Console.WriteLine(" Top color: " + topCol.ToString());
                    Console.WriteLine(" Bottom color: " + bottomCol.ToString());
                    
                    if (light1 != null)
                    {
                        Console.WriteLine("\n Light1: " + light1.ToString());
                    }

                    if (light2 != null)
                    {
                        Console.WriteLine("\n Light2: " + light2.ToString());
                    }
                }
            }
        }
    }
}
