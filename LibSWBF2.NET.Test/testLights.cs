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
    class LightsTest
    {
        static void Main(string[] args)
        {
            {
                TestBench.StartLogging(ELogType.Warning);

                Level level = TestBench.LoadAndTrackLVL(args[0]);

                Light[] lights = level.GetLights();

                foreach (var light in lights)
                {
                    Console.WriteLine(light.ToString());
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

                TestBench.StopLogging();
            }
        }
    }
}
