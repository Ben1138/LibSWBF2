using System;
using System.Collections.ObjectModel;
using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{
    public sealed class Terrain : NativeWrapper
    {
        public float HeightUpperBound { get; private set; }
        public float HeightLowerBound { get; private set; }
        public uint  NumVertices { get; private set; }
        public uint  NumNormals { get; private set; }
        public uint  NumUVs { get; private set; }
        public ReadOnlyCollection<string> LayerTextures { get; private set; }

        IntPtr vertexBufferPtr;
        IntPtr normalsBufferPtr;
        IntPtr uvsBufferPtr;


        internal override void SetPtr(IntPtr terPtr)
        {
            base.SetPtr(terPtr);
            if (APIWrapper.Terrain_FetchSimpleFields(terPtr, out int numTexes, out IntPtr texNamesPtr,
                                        out float heightUpperBound, out float heightLowerBound, 
                                        out uint numVertices, out vertexBufferPtr,
                                        out uint numNormals, out normalsBufferPtr,
                                        out uint numUVs, out uvsBufferPtr))
            {
                HeightUpperBound = heightUpperBound;
                HeightLowerBound = heightLowerBound;
                NumVertices = numVertices;
                NumNormals = numNormals;
                NumUVs = numUVs;
                LayerTextures = new ReadOnlyCollection<string>(MemUtils.IntPtrToStringList(texNamesPtr, numTexes));
            }
        }


        public void GetHeightMap(out uint dim, out uint dimScale, out float[] data) 
        {
            CheckValidity();
            APIWrapper.Terrain_GetHeightMap(NativeInstance, out dim, out dimScale, out IntPtr bytesNative);
            data = MemUtils.IntPtrToArray<float>(bytesNative, (int) (dim * dim));
        }

        public void GetBlendMap(out uint dim, out uint numLayers, out byte[] data)
        {
            CheckValidity();
            APIWrapper.Terrain_GetBlendMap(NativeInstance, out dim, out numLayers, out IntPtr bytesNative);
            data = MemUtils.IntPtrToArray<byte>(bytesNative, (int) (dim * dim * numLayers));
        } 

        public uint[] GetIndexBuffer()
        {
            CheckValidity();
            APIWrapper.Terrain_GetIndexBuffer(NativeInstance, out IntPtr buf, out uint numInds);
            return MemUtils.IntPtrToArray<uint>(buf, (int) numInds);
        }

        public unsafe T[] GetPositionsBuffer<T>() where T : unmanaged
        {
            CheckValidity();
            return MemUtils.IntPtrToArray<T>(vertexBufferPtr, ((int) NumVertices * 3 * 4) / sizeof(T));
        }

        public unsafe T[] GetNormalsBuffer<T>() where T : unmanaged
        {
            CheckValidity();
            return MemUtils.IntPtrToArray<T>(normalsBufferPtr, ((int) NumNormals * 3 * 4) / sizeof(T));   
        }

        public unsafe T[] GetUVBuffer<T>() where T : unmanaged
        {
            CheckValidity();
            return MemUtils.IntPtrToArray<T>(uvsBufferPtr, ((int) NumUVs * 2 * 4) / sizeof(T));   
        }
    }
}
