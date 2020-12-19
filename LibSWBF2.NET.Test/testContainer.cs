using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using LibSWBF2.Wrappers;
using LibSWBF2.Logging;


namespace LibSWBF2.NET.Test
{
    class ContainerTest
    {
        static void Main(string[] args)
        {
            TestBench.StartLogging(ELogType.Warning);

            var lvls = TestBench.LoadAndTrackLVLs(new List<string>(args));

            TestBench.StopLogging();
        }
    }
}