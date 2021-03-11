using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Types;
using LibSWBF2.Logging;

namespace LibSWBF2.Wrappers
{
    public sealed class CollisionPrimitive : NativeWrapper
    {
        public uint    MaskFlags { get; private set; }
        public uint    PrimitiveType { get; private set; }
        public Vector4 Rotation { get; private set; }
        public Vector3 Position { get; private set; }
        public string  Name { get; private set; }
        public string  ParentName { get; private set; }

        float f1, f2, f3;


        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            APIWrapper.CollisionPrimitive_FetchAllFields(
                NativeInstance, out f1, out f2, out f3,
                out IntPtr namePtr, out IntPtr parentNamePtr,
                out uint maskFlags, out uint primitiveType,
                out IntPtr posPtr, out IntPtr rotPtr
            );

            MaskFlags = maskFlags;
            PrimitiveType = primitiveType;

            Rotation = new Vector4(rotPtr);
            Position = new Vector3(posPtr);

            Name = Marshal.PtrToStringAnsi(namePtr);
            ParentName = Marshal.PtrToStringAnsi(parentNamePtr);
        }

        public bool GetCubeDims(out float x, out float y, out float z)
        {
            CheckValidity();
            x = f1;
            y = f2;
            z = f3;
            return PrimitiveType == 4;
        }

        public bool GetCylinderDims(out float radius, out float height)
        {
            CheckValidity();
            radius = f1;
            height = f2;
            return PrimitiveType == 2;
        }

        public bool GetSphereRadius(out float radius)
        {
            CheckValidity();
            radius = f1;
            return PrimitiveType == 1;
        }
    }
}
