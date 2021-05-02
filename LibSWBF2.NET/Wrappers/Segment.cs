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

    public sealed class Segment : NativeWrapper
    {
        public ETopology Topology { get; private set; }
        public string   BoneName { get; private set; }
        public string   MNAM { get; private set; }
        public bool     IsPretransformed { get; private set; }
        public int      NumVertices { get; private set; }
        public int      NumIndices { get; private set; }
        public int      NumVertexWeights { get; private set; }
        public Material Material { get; private set; }

        IntPtr IndexBufferPtr;
        IntPtr VertexBufferPtr;
        IntPtr UVBufferPtr;
        IntPtr NormalsBufferPtr;
        IntPtr VertexWeightsBufferPtr;

        internal override void SetPtr(IntPtr seg)
        {
            base.SetPtr(seg);
            if (APIWrapper.Segment_FetchAllFields(seg, out bool isPretransformed, out IntPtr boneNamePtr, out IntPtr MNAMPtr,
                                                        out uint numVertsOut, out VertexBufferPtr, out NormalsBufferPtr, out UVBufferPtr,
                                                        out uint numVWsOut, out VertexWeightsBufferPtr,
                                                        out int topo, out uint numIndsOut, out IndexBufferPtr,
                                                        out IntPtr matPtr))
            {
                IsPretransformed = isPretransformed;
                NumIndices = (int) numIndsOut;
                NumVertices = (int) numVertsOut;
                NumVertexWeights = (int) numVWsOut;
                BoneName = Marshal.PtrToStringAnsi(boneNamePtr);
                MNAM = Marshal.PtrToStringAnsi(MNAMPtr);

                Topology = (ETopology) topo;
                Material = FromNative<Material>(matPtr);
            }

        }


        private ushort[] ToTriList(ushort[] triStrip)
        {
            CheckValidity();
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
            CheckValidity();
            return (uint) NumVertices;
        }

        public unsafe T[] GetVertexBuffer<T>() where T : unmanaged
        {
            CheckValidity();
            return MemUtils.IntPtrToArray<T>(VertexBufferPtr, (NumVertices * 3 * 4) / sizeof(T));
        }

        public unsafe T[] GetNormalsBuffer<T>() where T : unmanaged
        {
            CheckValidity();
            return MemUtils.IntPtrToArray<T>(NormalsBufferPtr, (NumVertices * 3 * 4) / sizeof(T));
        }

        public unsafe T[] GetUVBuffer<T>() where T : unmanaged
        {
            CheckValidity();
            return MemUtils.IntPtrToArray<T>(UVBufferPtr, (NumVertices * 2 * 4) / sizeof(T));
        }

        public VertexWeight[] GetVertexWeights()
        {
            CheckValidity();
            return MemUtils.IntPtrToArray<VertexWeight>(VertexWeightsBufferPtr, NumVertexWeights);            
        }

        public ushort[] GetIndexBuffer(ETopology requestedTopology = ETopology.TriangleList)
        {
            CheckValidity();

            if (requestedTopology != ETopology.TriangleList &&
                requestedTopology != ETopology.TriangleStrip)
            {
                throw new Exception("Only requestable topologies are tri strip and tri list!");
            }

            if (Topology != ETopology.TriangleList &&
                Topology != ETopology.TriangleStrip)
            {
                return new ushort[0];
            }

            if (Topology == ETopology.TriangleList &&
                requestedTopology == ETopology.TriangleStrip)
            {
                throw new Exception("Cant convert triangle strip to list yet!");
            }

            ushort[] indices = MemUtils.IntPtrToArray<ushort>(IndexBufferPtr, NumIndices);

            if (requestedTopology == Topology)
            {
                return indices;
            } 
            else 
            {
                return ToTriList(indices);
            }
        }
    }
}
