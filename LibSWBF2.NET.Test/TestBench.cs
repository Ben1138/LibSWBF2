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
    static class TestBench
    {
        static ReaderWriterLockSlim m_Lock = new ReaderWriterLockSlim();
        static bool m_bCatchLogs = true;

        private static Thread logThread;

        static void CatchLogs()
        {
            bool bRun;
            do
            {
                while(Logger.GetNextLog(out LoggerEntry next))
                {
                    Console.WriteLine(next.ToString());
                }

                m_Lock.EnterReadLock();
                bRun = m_bCatchLogs;
                m_Lock.ExitReadLock();
            }
            while (bRun);
        }

        public static Level LoadAndTrackLVL(string path)
        {
            List<Level> results = LoadAndTrackLVLs(new List<string>{ path });

            if (results.Count == 0){
                return null;
            }

            return results[0];
        }


        public static List<Level> LoadAndTrackLVLs(List<string> paths)
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

            return lvls;
        }


        public static void StartLogging(ELogType logType)
        {
            Logger.SetLogLevel(ELogType.Warning);
            logThread = new Thread(new ThreadStart(CatchLogs));
            logThread.Start();
        }

        public static void StopLogging()
        {
            m_Lock.EnterWriteLock();
            m_bCatchLogs = false;
            m_Lock.ExitWriteLock();
            logThread.Join();
        }
    }
}
