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
        internal Terrain(IntPtr terrainPtr) : base(terrainPtr){}
        public Terrain() : base(IntPtr.Zero){}


        public void GetHeightBounds(out float floor, out float ceiling)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetHeightBounds(NativeInstance, out floor, out ceiling);
        }


        public List<string> GetTextureNames()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetTexNames(NativeInstance, out uint numTextures, out IntPtr stringsPtr);
            return MemUtils.IntPtrToStringList(stringsPtr, (int) numTextures); 
        }       


        public void GetHeightMap(out uint dim, out uint dimScale, out float[] data) 
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetHeightMap(NativeInstance, out dim, out dimScale, out IntPtr heightsNative);

            int dataLength = (int) (dim * dim);

            float[] heights = new float[dataLength];
            Marshal.Copy(heightsNative, heights, 0, dataLength);
            data = heights;
        }


        public void GetBlendMap(out uint dim, out uint numLayers, out byte[] data)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetBlendMap(NativeInstance, out dim, out numLayers, out IntPtr bytesNative);

            int dataLength = (int) (dim * dim * numLayers);

            byte[] byteArray = new byte[dataLength];
            Marshal.Copy(bytesNative, byteArray, 0, dataLength);
            data = byteArray; 
        } 


        public uint[] GetIndexBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetIndexBuffer(NativeInstance, out IntPtr buf, out int numInds);
            return MemUtils.IntPtrToArray<uint>(buf, numInds);
        }


        public float[] GetPositionsBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetVertexBuffer(NativeInstance, out IntPtr buf, out int numVerts);
            return MemUtils.IntPtrToArray<float>(buf, numVerts * 3);
        }


        public float[] GetNormalsBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetNormalsBuffer(NativeInstance, out IntPtr buf, out int numVerts);
            return MemUtils.IntPtrToArray<float>(buf, numVerts * 3);   
        }
    }
}
