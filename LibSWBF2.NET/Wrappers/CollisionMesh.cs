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
        internal CollisionMesh(IntPtr CollisionMeshPtr) : base(CollisionMeshPtr){}

        public float[] GetVertices()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");

            APIWrapper.CollisionMesh_GetVertexBuffer(NativeInstance, out uint count, out IntPtr buffer);
            float[] verts = new float[count * 3];

            if (count > 0)
            {
                Marshal.Copy(buffer, verts, 0, (int)count);
            }
            
            return verts;
        }

        public ushort[] GetIndices()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");

            APIWrapper.CollisionMesh_GetIndexBuffer(NativeInstance, out uint count, out IntPtr buffer);
            
            return MemUtils.IntPtrToArray<ushort>(buffer, (int) count);

            /*
            int[] inds = new int[(int)count];

            if (count > 0)
            {
                Marshal.Copy(buffer, inds, 0, (int)count);
            }
            
            return inds;
            */
            
        }
    }
}
