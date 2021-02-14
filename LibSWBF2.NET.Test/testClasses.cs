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
    class ClassesTest
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
            
                var classes = level.GetEntityClasses();

                int k = 0;
                foreach (var ec in classes)
                {
                    Console.WriteLine("\n" + ec.name + " of base class: " + ec.GetBaseName());

                    ec.GetOverriddenProperties(out uint[] hashes, out string[] values);

                    Console.WriteLine("Properties: ");
                    for (int i = 0; i < values.Length; i++)
                    {
                        Console.WriteLine("\t0x{0:x}: {1}", hashes[i], values[i]);
                    }
                    
                } 

                TestBench.StopLogging();
                return 1;
            }
        }
    }
}
