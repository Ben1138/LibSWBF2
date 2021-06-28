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
            var tb = new TestBench();

            var c = tb.LoadAndTrackContainer(new List<string>(args), out List<Level> lvls);


            Level level = lvls[0];
            if (level == null)
            {
                return -1;
            }
        
            var classes = level.Get<EntityClass>();

            int k = 0;
            foreach (var ec in classes)
            {
                Console.WriteLine("\n" + ec.Name + " of base class: " + ec.BaseClassName);

                ec.GetOverriddenProperties(out uint[] hashes, out string[] values);

                Console.WriteLine("Properties: ");
                for (int i = 0; i < values.Length; i++)
                {
                    Console.WriteLine("\t0x{0:x}: {1}", hashes[i], values[i]);
                }
                
            } 

            return 1;            
        }
    }
}
