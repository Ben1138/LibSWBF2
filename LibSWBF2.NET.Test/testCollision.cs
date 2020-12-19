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
    class CollisionTest
    {
        static void Main(string[] args)
        {
            TestBench.StartLogging(ELogType.Warning);

            var lvls = TestBench.LoadAndTrackLVLs(new List<string>(args));

            for (int i = 0; i < lvls.Count; i++)
            {
                Console.WriteLine("Level {0}'s collision meshes: ", i);

                level = lvls[i];

                Model[] models = level.GetModels();
                foreach (Model model in models)
                {
                    Console.WriteLine("\n\tModel: " + model.Name);
                    CollisionMesh mesh = model.GetCollisionMesh();

                    Console.WriteLine("\t\tNum collision indices:   {0}", mesh.GetIndices().Length);
                    Console.WriteLine("\t\tNum collision verticies: {0}", mesh.GetVertices().Length);
                
                    CollisionPrimitive[] prims = model.GetPrimitivesMasked();

                    Console.WriteLine("\t\t{0} Primitives: ", prims.Length);

                    foreach (var prim in prims)
                    {
                        Console.WriteLine("\t\t\t{0}", prim.name);
                    }
                }
            }

            TestBench.StopLogging();

            return 0;
        }
    }
}
