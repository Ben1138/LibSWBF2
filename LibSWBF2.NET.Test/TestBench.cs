using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using static System.Diagnostics.Stopwatch;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;



namespace LibSWBF2.NET.Test
{
    public class TestBench
    {
        private ReaderWriterLockSlim m_Lock = new ReaderWriterLockSlim();
        private volatile bool m_bCatchLogs = true;

        private Thread logThread;

        private void CatchLogs()
        {
            do
            {
                while(Logger.GetNextLog(out LoggerEntry next))
                {
                    Console.WriteLine(next.ToString());
                }
            }
            while (m_bCatchLogs);
        }

        
        public TestBench()
        {
            Logger.SetLogLevel(ELogType.Warning);
            logThread = new Thread(new ThreadStart(CatchLogs));
            logThread.IsBackground = true;
            logThread.Start();            
        }

        public void StopLogging()
        {
            m_bCatchLogs = false;
            logThread.Join();
        }

        ~TestBench()
        {
            StopLogging();
        }


        public Container LoadAndTrackContainer(List<string> paths, out List<Level> levelsOut)
        {
            Container container = new Container();

            List<uint> handles = new List<uint>();

            foreach (var path in paths)
            {
                handles.Add(container.AddLevel(path));
            }

            container.LoadLevels();

            while (!container.IsDone())
            {
                string status = "\r";
                for (int i = 0; i < handles.Count; i++)
                {
                    float progress = container.GetProgress(handles[i]);
                    status += String.Format("{0}: {1}%\t", i, (int) (progress * 100.0f));
                }

                Console.Write(status);
            }
            Console.WriteLine("");

            List<Level> lvls = new List<Level>();
            foreach (var handle in handles)
            {
                Level lvl = container.GetLevel(handle);

                if (lvl != null)
                {
                    lvls.Add(lvl);
                }
            }

            levelsOut = lvls;

            return container;
        }
    }
}
