using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Utils;
using LibSWBF2.Logging;

namespace LibSWBF2.Wrappers
{
    public sealed class CollisionMesh : NativeWrapper
    {
        public uint IndexCount { get; private set; }
        public uint VertexCount { get; private set; }
        public Enums.ECollisionMaskFlags MaskFlags { get; private set; }

        IntPtr VertexBufferPtr;
        IntPtr IndexBufferPtr;

        internal override void SetPtr(IntPtr cmPtr)
        {
            base.SetPtr(cmPtr);
            if (APIWrapper.CollisionMesh_FetchAllFields(cmPtr, out uint indexCount, out IndexBufferPtr,
                                                    out uint vertexCount, out VertexBufferPtr, out Enums.ECollisionMaskFlags maskFlags))
            {
                IndexCount = indexCount;
                VertexCount = vertexCount;
                MaskFlags = maskFlags;
            }
        }

        public unsafe T[] GetVertices<T>() where T : unmanaged
        {
            CheckValidity();
            return MemUtils.IntPtrToArray<T>(VertexBufferPtr, ((int) VertexCount * 3 * 4) / sizeof(T));
        }

        public ushort[] GetIndices()
        {
            CheckValidity();
            return MemUtils.IntPtrToArray<ushort>(IndexBufferPtr, (int) IndexCount);
        }
    }
}
