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
using LibSWBF2.Enums;

namespace LibSWBF2.NET.Test
{
    class CollisionTest
    {
        static int Main(string[] args)
        {
            TestBench testBench = new TestBench();

            Container container = testBench.LoadAndTrackContainer(new List<string>(args), out List<Level> lvls);


            //var lvls = testBench.LoadAndTrackLVLs(new List<string>(args));

            for (int i = 0; i < lvls.Count; i++)
            {
                Console.WriteLine("Level {0}'s collision meshes: ", i);

                var level = lvls[i];

                Model[] models = level.Get<Model>();
                foreach (Model model in models)
                {
                    Console.WriteLine("\n\tModel: " + model.Name);
                    CollisionMesh mesh = model.GetCollisionMesh();

                    if (mesh == null) continue;

                    Console.WriteLine("\t\tCollision mask flags: {0}", mesh.MaskFlags);
                    Console.WriteLine("\t\tNum collision indices:   {0}", mesh.GetIndices().Length);
                    Console.WriteLine("\t\tNum collision verticies: {0}", mesh.GetVertices<Vector3>().Length);
                
                    CollisionPrimitive[] prims = model.GetPrimitivesMasked((ECollisionMaskFlags) 16);

                    Console.WriteLine("\t\t{0} Primitives: ", prims.Length);

                    foreach (var prim in prims)
                    {
                        Console.WriteLine("\t\t\tName: {0} Parent: {1}", prim.Name, prim.ParentName);
                    }
                }
            }

            return 0;
        }
    }
}
