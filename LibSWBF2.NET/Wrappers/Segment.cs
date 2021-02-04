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


        public Topology topology;

        public string boneName;

        public bool isPretransformed;

        public int numVertices;
        private IntPtr vertexBufferPtr, uvBufferPtr, normalsBufferPtr;

        public int numIndices;
        private IntPtr indexBufferPtr;

        public int numVertexWeights;
        private IntPtr vertexWeightsBufferPtr;

        public Material material;


        internal override void SetPtr(IntPtr seg)
        {
            bool status = APIWrapper.Segment_FetchAllFields(seg, out isPretransformed, out IntPtr boneNamePtr,
                                                        out uint numVertsOut, out vertexBufferPtr, out normalsBufferPtr, out uvBufferPtr,
                                                        out uint numVWsOut, out vertexWeightsBufferPtr,
                                                        out int topo, out uint numIndsOut, out indexBufferPtr,
                                                        out IntPtr matPtr);
            if (!status) { 
                NativeInstance = IntPtr.Zero;
                return;
            }

            NativeInstance = seg;

            numIndices = (int) numIndsOut;
            numVertices = (int) numVertsOut;
            numVertexWeights = (int) numVWsOut;
            boneName = Marshal.PtrToStringAnsi(boneNamePtr);
            topology = (Topology) topo;
            material = new Material(matPtr);
        }


        private ushort[] ToTriList(ushort[] triStrip)
        {
            List<ushort> triList = new List<ushort>();
            ushort a,b,c,temp;

            for (int i = 0; i < triStrip.Length - 2; i++)
            {
                a = triStrip[i];
                b = triStrip[i+1];
                c = triStrip[i+2]; 

                if (a != b && b != c && a != c) //Catch degenerate 
                {
                    if (i % 2 != 0) //swap clockwiseness 
                    {
                        temp = b;
                        b = a;
                        a = temp; 
                    }

                    triList.Add(a);
                    triList.Add(b);
                    triList.Add(c);
                }
            }

            return triList.ToArray();
        }


        public uint GetVertexBufferLength()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return (uint) numVertices * 3;
        }

        public float[] GetVertexBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<float>(vertexBufferPtr, numVertices * 3);
        }

        public float[] GetNormalsBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<float>(normalsBufferPtr, numVertices * 3);
        }

        public float[] GetUVBuffer()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<float>(uvBufferPtr, numVertices * 2);
        }

        public VertexWeight[] GetVertexWeights()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<VertexWeight>(vertexWeightsBufferPtr, numVertexWeights);            
        }

        public ushort[] GetIndexBuffer(Topology requestedTopology = Topology.TriangleList)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");

            if (requestedTopology != Topology.TriangleList &&
                requestedTopology != Topology.TriangleStrip)
            {
                throw new Exception("Only requestable topologies are tri strip and tri list!");
            }

            if (topology != Topology.TriangleList &&
                topology != Topology.TriangleStrip)
            {
                return new ushort[0];
            }

            if (topology == Topology.TriangleList &&
                requestedTopology == Topology.TriangleStrip)
            {
                throw new Exception("Cant convert triangle strip to list yet!");
            }

            ushort[] indices = MemUtils.IntPtrToArray<ushort>(indexBufferPtr, numIndices);

            if (requestedTopology == topology)
            {
                return indices;
            } 
            else 
            {
                return ToTriList(indices);
            }
        }


        /*
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
        */

        public int GetTopology()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return (int) topology;
            //return APIWrapper.Segment_GetTopology(NativeInstance);            
        }

        public string GetBone()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return boneName;
            //return Marshal.PtrToStringAnsi(APIWrapper.Segment_GetBone(NativeInstance));
        }

        public Material GetMaterial()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return material;
            //return new Material(APIWrapper.Segment_GetMaterial(NativeInstance));            
        }

        public bool IsPretransformed()
        {   
            return isPretransformed;
            //return APIWrapper.Segment_IsPretransformed(NativeInstance);           
        }
    }
}
