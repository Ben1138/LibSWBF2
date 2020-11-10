using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

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
            Level level = Level.FromFile(@"/home/will/Desktop/geo1.lvl");
            //Level level = Level.FromFile("F:/SteamLibrary/steamapps/common/Star Wars Battlefront II/GameData/data/_lvl_pc/geo/geo1.lvl");

            Model[] models = level.GetModels();
            foreach (Model model in models)
            {
                Console.WriteLine("\nModel: " + model.Name);
                CollisionMesh mesh = model.GetCollisionMesh();

                Console.WriteLine("\tNum collision indices:   {0}", mesh.GetIndices().Length);
                Console.WriteLine("\tNum collision verticies: {0}", mesh.GetVertices().Length);
            
                CollisionPrimitive[] prims = model.GetPrimitivesMasked();

                Console.WriteLine("\t{0} Primitives: ", prims.Length);

                foreach (var prim in prims)
                {
                    Console.WriteLine("\t\t{0}", prim.name);
                }
            }

            Console.WriteLine("Done!");

            m_Lock.EnterWriteLock();
            m_bCatchLogs = false;
            m_Lock.ExitWriteLock();
            logThread.Join();
        }
    }
}
