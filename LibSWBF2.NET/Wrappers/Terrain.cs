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
        internal Terrain(IntPtr terrainPtr) : base(IntPtr.Zero){ SetPtr(terrainPtr); }
        public Terrain() : base(IntPtr.Zero){}


        public float heightUpperBound;
        public float heightLowerBound;

        public List<string> layerTextures;


        public uint numVertices;
        private IntPtr vertexBufferPtr;

        public uint numNormals;
        private IntPtr normalsBufferPtr;

        public uint numUVs;
        private IntPtr uvsBufferPtr;


        internal override void SetPtr(IntPtr terPtr)
        {
            if (APIWrapper.Terrain_FetchSimpleFields(terPtr, out int numTexes, out IntPtr texNamesPtr,
                                        out heightUpperBound, out heightLowerBound, 
                                        out numVertices, out vertexBufferPtr,
                                        out numNormals, out normalsBufferPtr,
                                        out numUVs, out uvsBufferPtr))
            {
                NativeInstance = terPtr;
                layerTextures = MemUtils.IntPtrToStringList(texNamesPtr, numTexes);
            }
        }


        public void GetHeightMap(out uint dim, out uint dimScale, out float[] data) 
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetHeightMap(NativeInstance, out dim, out dimScale, out IntPtr bytesNative);
            data = MemUtils.IntPtrToArray<float>(bytesNative, (int) (dim * dim));
        }

        public void GetBlendMap(out uint dim, out uint numLayers, out byte[] data)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetBlendMap(NativeInstance, out dim, out numLayers, out IntPtr bytesNative);
            data = MemUtils.IntPtrToArray<byte>(bytesNative, (int) (dim * dim * numLayers));
        } 

        public uint[] GetIndexBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetIndexBuffer(NativeInstance, out IntPtr buf, out uint numInds);
            return MemUtils.IntPtrToArray<uint>(buf, (int) numInds);
        }

        public unsafe T[] GetPositionsBuffer<T>() where T : unmanaged
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<T>(vertexBufferPtr, ((int) numVertices * 3 * 4) / sizeof(T));
        }

        public unsafe T[] GetNormalsBuffer<T>() where T : unmanaged
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<T>(normalsBufferPtr, ((int) numNormals * 3 * 4) / sizeof(T));   
        }

        public unsafe T[] GetUVBuffer<T>() where T : unmanaged
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<T>(uvsBufferPtr, ((int) numUVs * 2 * 4) / sizeof(T));   
        }
    }
}
