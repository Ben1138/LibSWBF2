using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Logging;
using LibSWBF2.Wrappers;



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

            foreach (var str in terrain.GetTextureNames()){
                
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
            
            TestBench.StopLogging();
            return 1;
        }
    }
}
