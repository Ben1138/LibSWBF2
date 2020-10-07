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
    class Program
    {
        static ReaderWriterLockSlim m_Lock = new ReaderWriterLockSlim();
        static bool m_bCatchLogs = true;

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

        static void Main(string[] args)
        {
            Logger.SetLogLevel(ELogType.Warning);
            Thread logThread = new Thread(new ThreadStart(CatchLogs));
            logThread.Start();

            Console.WriteLine("Loading... This might take a while...");

            string path1 = @"/home/will/Desktop/geo1.lvl";
            string path2 = @"/home/will/Desktop/MLC.lvl";
            
            //string path1 = @"/Users/will/Desktop/MLC.lvl";
            //string path2 = @"/Users/will/Desktop/geo1.lvl";

            //Level level = Level.FromFile(@"F:\SteamLibrary\steamapps\common\Star Wars Battlefront II\GameData\data\_lvl_pc\geo\geo1.lvl");

            Container container = new Container();
            uint handle1 = container.AddLevel(path1);
            uint handle2 = container.AddLevel(path2);

            float progress1 = 0.0f, progress2 = 0.0f;

            container.LoadLevels();

            while (!container.IsDone())
            {
                Console.Write("\rLevel1 status: {0}%, Level2 status: {1}%",
                             (int) (progress1 * 100.0f), (int) (progress2 * 100.0f));

                progress1 = container.GetProgress(handle1);
                progress2 = container.GetProgress(handle2);
            }

            Level lvl1 = container.GetLevel(handle1);
            Level lvl2 = container.GetLevel(handle2);

            Console.WriteLine("\nFirst level contains {0} models, second contains {1}", 
                                lvl1.GetModels().Length, lvl2.GetModels().Length);


            Model[] models = lvl2.GetModels();

            Stopwatch sw = Stopwatch.StartNew();

            foreach (Model model in models)
            {
                Model containerModel = container.FindWrapper<Model>(model.Name);

                ushort[] inds1 = containerModel.GetCollisionMesh().GetIndices();
                ushort[] inds2 = model.GetCollisionMesh().GetIndices();

                //Console.WriteLine("Container collision ibuf length {0}, Direct collision ibuf length {1}",
                //                inds1.Length, inds2.Length);
            }

            Console.WriteLine("Elapsed: {0}", sw.Elapsed);

            m_Lock.EnterWriteLock();
            m_bCatchLogs = false;
            m_Lock.ExitWriteLock();
            logThread.Join();
        }
    }
}
