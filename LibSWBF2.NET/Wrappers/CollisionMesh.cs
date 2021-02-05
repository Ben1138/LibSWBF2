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
        internal CollisionMesh(IntPtr CollisionMeshPtr) : base(CollisionMeshPtr){ SetPtr(CollisionMeshPtr); }

        public uint maskFlags;

        private IntPtr indexBufferPtr;
        private int indexCount;

        private IntPtr vertexBufferPtr;
        private int vertexCount;

        internal override void SetPtr(IntPtr cmPtr)
        {   
            NativeInstance = IntPtr.Zero;
            if (APIWrapper.CollisionMesh_FetchAllFields(cmPtr, out uint iCount, out indexBufferPtr,
                                                    out uint vCount, out vertexBufferPtr, out maskFlags))
            {
                NativeInstance = cmPtr;
                indexCount = (int) iCount;
                vertexCount = (int) vCount;
            }
        }

        public unsafe T[] GetVertices<T>() where T : unmanaged
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<T>(vertexBufferPtr, (vertexCount * 3 * 4) / sizeof(T));
        }

        public ushort[] GetIndices()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToArray<ushort>(indexBufferPtr, indexCount);
        }
    }
}
