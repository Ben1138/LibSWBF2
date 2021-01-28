using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Logging;
using LibSWBF2.Enums;
using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{

    [StructLayout(LayoutKind.Sequential, Pack=1)]
    public struct VertexWeight 
    {
        public float weight;
        public byte index;
    }

    public class Segment : NativeWrapper
    {
        public Segment(IntPtr segmentPtr) : base(segmentPtr) {}
        public Segment() : base(IntPtr.Zero) {}

        public uint GetVertexBufferLength()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return APIWrapper.Segment_GetVertexBufferLength(NativeInstance);
        }

        public float[] GetVertexBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Segment_GetVertexBuffer(NativeInstance, out uint numVerts, out IntPtr vertsArr);
            return MemUtils.IntPtrToArray<float>(vertsArr, (int) numVerts * 3);
        }

        public float[] GetNormalsBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Segment_GetNormalBuffer(NativeInstance, out uint numNormals, out IntPtr normalsArr);
            return MemUtils.IntPtrToArray<float>(normalsArr, (int) numNormals * 3);
        }

        public ushort[] GetIndexBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Segment_GetIndexBuffer(NativeInstance, out uint numInds, out IntPtr indsArr);
            return MemUtils.IntPtrToArray<ushort>(indsArr, (int) numInds);
        }

        public float[] GetUVBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Segment_GetUVBuffer(NativeInstance, out uint numUVs, out IntPtr UVsArr);
            return MemUtils.IntPtrToArray<float>(UVsArr, 2 * (int) numUVs);
        }

        public VertexWeight[] GetVertexWeights()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Segment_GetVertexWeightsBuffer(NativeInstance, out int numVWs, out IntPtr vwBuffer);
            return MemUtils.IntPtrToArray<VertexWeight>(vwBuffer, numVWs);            
        }

        public int GetTopology()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return APIWrapper.Segment_GetTopology(NativeInstance);            
        }

        public string GetBone()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return Marshal.PtrToStringAnsi(APIWrapper.Segment_GetBone(NativeInstance));
        }

        public Material GetMaterial()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return new Material(APIWrapper.Segment_GetMaterial(NativeInstance));            
        }

        public bool IsPretransformed()
        {
            return APIWrapper.Segment_IsPretransformed(NativeInstance);           
        }
    }
}
