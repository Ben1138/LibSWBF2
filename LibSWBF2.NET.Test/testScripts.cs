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
    class ScriptsTest
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
        
            var scripts = level.Get<Script>();

            foreach (var script in scripts)
            {
                Console.WriteLine(script.Name);

                if (script.GetData(out IntPtr data, out uint size))
                {
                    Console.WriteLine("    Size: " + size.ToString() + " bytes...");
                }
            } 

            return 1;            
        }
    }
}
