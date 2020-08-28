using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;

namespace LibSWBF2.Wrappers
{
    public class Segment : NativeWrapper
    {
        internal Segment(IntPtr modelPtr) : base(modelPtr)
        {

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

        public uint[] GetIndexBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");

            APIWrapper.Segment_GetIndexBuffer(NativeInstance, out uint numInds, out IntPtr indsArr);
            uint[] indicies = new uint[(int)numInds];
            Marshal.Copy(indsArr, indicies, 0, (int)numInds);
            return indicies;
        }

        public float[] GetUVBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");

            APIWrapper.Segment_GetUVBuffer(NativeInstance, out uint numUVs, out IntPtr UVsArr);
            float[] UVs = new float[(int)numUVs*2];
            Marshal.Copy(UVsArr, UVs, 0, (int)numUVs*2);
            return UVs;
        }
    }
}
