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
    public class CollisionMesh : NativeWrapper
    {
        internal CollisionMesh(IntPtr CollisionMeshPtr) : base(IntPtr.Zero){ SetPtr(CollisionMeshPtr); }

        public uint maskFlags;

        private IntPtr indexBufferPtr;
        public uint indexCount;

        private IntPtr vertexBufferPtr;
        public uint vertexCount;

        internal override void SetPtr(IntPtr cmPtr)
        {   
            if (APIWrapper.CollisionMesh_FetchAllFields(cmPtr, out indexCount, out indexBufferPtr,
                                                    out vertexCount, out vertexBufferPtr, out maskFlags))
            {
                NativeInstance = cmPtr;
            }
        }

        public unsafe T[] GetVertices<T>() where T : unmanaged
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<T>(vertexBufferPtr, ((int) vertexCount * 3 * 4) / sizeof(T));
        }

        public ushort[] GetIndices()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<ushort>(indexBufferPtr, (int) indexCount);
        }
    }
}
