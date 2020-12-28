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
        public Segment(IntPtr segmentPtr) : base(segmentPtr){}
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
            float[] verts = new float[(int)numVerts*3];
            Marshal.Copy(vertsArr, verts, 0, (int)numVerts*3);
            return verts;
        }

        public float[] GetNormalsBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");

            APIWrapper.Segment_GetNormalBuffer(NativeInstance, out uint numNormals, out IntPtr normalsArr);
            float[] normals = new float[(int)numNormals*3];
            Marshal.Copy(normalsArr, normals, 0, (int)numNormals*3);
            return normals;
        }

        public int[] GetIndexBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");

            APIWrapper.Segment_GetIndexBuffer(NativeInstance, out uint numInds, out IntPtr indsArr);
            int indsLength = (int) numInds;
            int[] indicies = new int[indsLength];
            Marshal.Copy(indsArr, indicies, 0, indsLength);
            return indicies;
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

        public string GetMaterialTexName()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            IntPtr strPtr = APIWrapper.Segment_GetMaterialTexName(NativeInstance);

            if (strPtr == IntPtr.Zero)
            {
                return "";
            }            
            return Marshal.PtrToStringAnsi(strPtr);
        }

        public int GetTopology()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return APIWrapper.Segment_GetTopology(NativeInstance);            
        }

        public uint GetMaterialFlags()
        {
            return APIWrapper.Segment_GetMaterialFlags(NativeInstance);
        }
    }
}
