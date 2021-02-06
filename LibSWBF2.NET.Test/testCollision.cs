using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;
using LibSWBF2.Types;

namespace LibSWBF2.NET.Test
{
    class CollisionTest
    {
        static int Main(string[] args)
        {
            TestBench.StartLogging(ELogType.Warning);

            var lvls = TestBench.LoadAndTrackLVLs(new List<string>(args));

            for (int i = 0; i < lvls.Count; i++)
            {
                Console.WriteLine("Level {0}'s collision meshes: ", i);

                var level = lvls[i];

                Model[] models = level.GetModels();
                foreach (Model model in models)
                {
                    Console.WriteLine("\n\tModel: " + model.name);
                    CollisionMesh mesh = model.GetCollisionMesh();

                    if (mesh == null) continue;

                    Console.WriteLine("\t\tCollision mask flags: {0}", mesh.maskFlags);
                    Console.WriteLine("\t\tNum collision indices:   {0}", mesh.GetIndices().Length);
                    Console.WriteLine("\t\tNum collision verticies: {0}", mesh.GetVertices<Vector3>().Length);
                
                    CollisionPrimitive[] prims = model.GetPrimitivesMasked(16);

                    Console.WriteLine("\t\t{0} Primitives: ", prims.Length);

                    foreach (var prim in prims)
                    {
                        Console.WriteLine("\t\t\tName: {0} Parent: {1}", prim.name, prim.parentName);
                    }
                }
            }

            TestBench.StopLogging();

            return 0;
        }
    }
}
