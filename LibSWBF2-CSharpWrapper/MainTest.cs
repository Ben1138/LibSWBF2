using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LibSWBF2.Types;

namespace LibSWBF2
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
            Log.Add("Test1", ELogType.Info);
            Log.Add("Test2fdgdfg", ELogType.Info);
            Log.Add("Testdfgd3", ELogType.Info);
            Log.Add("Test4", ELogType.Info);
            Log.Add("Test55555555", ELogType.Info);

            PrintLastLines();

            Color color = new Color(0.5f, 0.5f, 0.5f);

            PrintLastLines();

            Console.WriteLine(color.R);

            Console.ReadKey();
        }
    }
}
