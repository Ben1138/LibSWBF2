using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;
using LibSWBF2.Types;



namespace LibSWBF2.NET.Test
{
    class TerrainTest
    {
        public static int Main(string[] args)
        {   
            TestBench.StartLogging(ELogType.Warning);

            Level level = TestBench.LoadAndTrackLVL(args[0]);
            if (level == null) return -1;

            Terrain terrain = level.GetTerrains()[0];

            foreach (var str in terrain.layerTextures){
                
                if (str == ""){
                    continue;
                }

                Console.Write("Texture name: " + str);
                Texture tex = level.GetTexture(str);
                if (tex != null){
                    byte[] data = tex.GetBytesRGBA();
                    Console.WriteLine(" width: " + tex.width + " height: " + tex.height + " bytes length: " + data.Length);
                } else {
                    Console.WriteLine(" lookup failed.");
                }
            }
            
            terrain.GetHeightMap(out uint dim, out uint dimScale, out float[] heightMapData);
            terrain.GetBlendMap(out dim, out uint numLayers, out byte[] blendMapData);

            uint[] iBuf = terrain.GetIndexBuffer();
            Vector2[] uvBuf = terrain.GetUVBuffer<Vector2>();
            Vector3[] vertBuf = terrain.GetPositionsBuffer<Vector3>();
            Vector3[] normsBuf = terrain.GetNormalsBuffer<Vector3>();

            Console.WriteLine("Num uvs: {0}, num normals: {1}, num verts: {2}, num indices: {3}", uvBuf.Length, normsBuf.Length, vertBuf.Length, iBuf.Length);

            
            TestBench.StopLogging();
            return 1;
        }
    }
}
