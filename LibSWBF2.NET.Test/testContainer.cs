using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;

namespace LibSWBF2.NET.Test
{
    class Program
    {
        static void Main(string[] args)
        {            
            Logger.SetLogLevel(ELogType.Warning);
            Logger.OnLog += (LoggerEntry logEntry) => 
            {
                Console.WriteLine(logEntry.ToString());
            };

            Console.WriteLine("Loading... This might take a while...");

            string path2 = @"/Users/will/Desktop/MLC.lvl";
            string path1 = @"/Users/will/Desktop/geo1.lvl";
            
            //string path1 = @"/home/will/Desktop/geo1.lvl";
            //string path2 = @"/Users/will/Desktop/geo1.lvl";

            //Level level = Level.FromFile(@"F:\SteamLibrary\steamapps\common\Star Wars Battlefront II\GameData\data\_lvl_pc\geo\geo1.lvl");

            Container container = new Container();
            uint handle1 = container.AddLevel(path1);
            uint handle2 = container.AddLevel(path2);

            bool done1 = false, done2 = false;
            float progress1 = 0.0f, progress2 = 0.0f;

            container.LoadLevels();

            Thread.Sleep(100);

            while (!(done1 && done2))
            {
                progress1 = container.GetProgress(handle1);
                progress2 = container.GetProgress(handle2);

                Console.Write("\rLevel1 status: {0}%, Level2 status: {1}%",
                             (int) (progress1 * 100.0f), (int) (progress2 * 100.0f));

                done1 = progress1 == 1.0f;
                done2 = progress2 == 1.0f;
                
                Thread.Sleep(10);
            }
        
            Console.WriteLine("\nDone!");
        }
    }
}
