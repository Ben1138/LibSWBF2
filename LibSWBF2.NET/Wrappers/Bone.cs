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
    public class Bone : NativeWrapper
    {
        public Bone() : base(IntPtr.Zero){}

        internal override void SetPtr(IntPtr ptr)
        {
        	APIWrapper.Bone_FetchAllFields(ptr, out IntPtr namePtr, out IntPtr parentNamePtr, out IntPtr loc, out IntPtr rot);

        	name = Marshal.PtrToStringAnsi(namePtr);

            if (parentNamePtr != IntPtr.Zero)
            {
                parentName = Marshal.PtrToStringAnsi(parentNamePtr);
            }

        	rotation = new Vector4(rot);
        	location = new Vector3(loc);
        }


        public string name;
        public string parentName = "";
        public Vector4 rotation;
        public Vector3 location;
    }
}
