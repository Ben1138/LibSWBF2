using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;
using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{
    public class Terrain : NativeWrapper
    {
        internal Terrain(IntPtr terrainPtr) : base(terrainPtr)
        {

        }

        public Terrain() : base(IntPtr.Zero){}


        public int width;
        public int height;

        public List<string> TextureNames
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                APIWrapper.Terrain_GetTexNames(NativeInstance, out uint numTextures, out IntPtr stringsPtr);
                return MemUtils.ptrToStringList(stringsPtr, (int) numTextures);
            }
        }

        public float[] Vertices
        {
            get
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                APIWrapper.Terrain_GetVerts(NativeInstance, out uint numVerts, out IntPtr vertsNative);

                float[] rawVerts = new float[((int)numVerts) * 3];
                Marshal.Copy(vertsNative, rawVerts, 0, (int) numVerts * 3);
                return rawVerts;
            }
        }

        public float[] Heights
        {
            get
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                APIWrapper.Terrain_GetHeights(NativeInstance, out uint _width, out uint _height, out IntPtr heightsNative);
                width = (int) _width;
                height = (int) _width;

                Console.WriteLine("Heights width = " + _width);
                Console.WriteLine("Heights height = " + _height);

                float[] heights = new float[(int) width * width];
                Marshal.Copy(heightsNative, heights, 0, (int) width * width);
                return heights;
            }
        }

        public int[] Indicies
        {
            get
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                APIWrapper.Terrain_GetIndicies(NativeInstance, out uint numInds, out IntPtr indiciesNative);

                int[] rawInds = new int[(int) numInds];
                Marshal.Copy(indiciesNative, rawInds, 0, (int) numInds);
                return rawInds;
            }
        }

        public byte[] GetBlendMap(out int dim, out int numLayersUsed)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetBlendMap(NativeInstance, out uint edgeLength, out uint numLayers, out IntPtr bytesNative);

            int mapSize = (int) (edgeLength * edgeLength * numLayers);

            byte[] byteArray = new byte[mapSize];
            Marshal.Copy(bytesNative, byteArray, 0, mapSize);
            
            dim = (int) edgeLength;
            numLayersUsed = (int) numLayers;

            return byteArray;  
        } 
    }
}
