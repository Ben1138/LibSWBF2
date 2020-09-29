using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;

namespace LibSWBF2.Wrappers
{
    public class CollisionPrimitive : NativeWrapper
    {
        public CollisionPrimitive() : base(IntPtr.Zero){}

        internal override void SetPtr(IntPtr ptr)
        {
            NativeInstance = ptr;
            APIWrapper.CollisionPrimitive_FetchAllFields(
                NativeInstance, out f1, out f2, out f3,
                out IntPtr namePtr, out IntPtr parentNamePtr,
                out maskFlags, out primitiveType,
                out IntPtr posPtr, out IntPtr rotPtr
            );

            rotation = new Vector4(rotPtr);
            position = new Vector3(posPtr);

            name = Marshal.PtrToStringAnsi(namePtr);
            parentName = Marshal.PtrToStringAnsi(parentNamePtr);
        }

        public uint maskFlags;
        public uint primitiveType;


        public bool GetCubeDims(out float x, out float y, out float z)
        {
            if (primitiveType != 4) return false;

            x = f1;
            y = f2;
            z = f3;
            return true;
        }

        public bool GetCylinderDims(out float radius, out float height)
        {
            if (primitiveType != 2) return false;

            radius = f1;
            height = f2;
            return true;
        }

        public bool GetSphereRadius(out float radius)
        {
            if (primitiveType != 1) return false;

            radius = f1;
            return true;
        }

        public Vector4 rotation;
        public Vector3 position;

        public string parentName, name;

        private float f1, f2, f3;
    }
}
