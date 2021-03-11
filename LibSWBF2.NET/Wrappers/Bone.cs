using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Logging;
using LibSWBF2.Enums;
using LibSWBF2.Types;

namespace LibSWBF2.Wrappers
{
    public sealed class Bone : NativeWrapper
    {
        public string  Name { get; private set; }
        public string  ParentName { get; private set; }
        public Vector4 Rotation { get; private set; }
        public Vector3 Location { get; private set; }

        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
        	APIWrapper.Bone_FetchAllFields(ptr, out IntPtr namePtr, out IntPtr parentNamePtr, out IntPtr loc, out IntPtr rot);
        	Name = Marshal.PtrToStringAnsi(namePtr);
            ParentName = Marshal.PtrToStringAnsi(parentNamePtr);
        	Rotation = new Vector4(rot);
        	Location = new Vector3(loc);
        }
    }
}
