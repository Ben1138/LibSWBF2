using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LibSWBF2.Types;
using LibSWBF2;

namespace Test
{
    static class MainTest
    {
        static void PrintLastLines()
        {
            string[] lines = Log.GetLatest(ELogType.Info);

            foreach (string line in lines)
                Console.WriteLine(line);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Press any key...");
            Console.ReadKey();

            Log.Add("Test1", ELogType.Info);
            Log.Add("Test2fdgdfg", ELogType.Info);
            Log.Add("Testdfgd3", ELogType.Info);
            Log.Add("Test4", ELogType.Info);
            Log.Add("Test55555555", ELogType.Info);

            PrintLastLines();
            
            MSH msh = new MSH("test");

            PrintLastLines();

            Color lol = msh.Color;
            lol.R = 0.42f;

            Console.WriteLine(msh.Color.R);

            Console.ReadKey();
        }
    }
}
