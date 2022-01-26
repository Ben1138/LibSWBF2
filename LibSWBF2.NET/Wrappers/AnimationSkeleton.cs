using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Utils;
using LibSWBF2.Logging;
using LibSWBF2.Enums;
using LibSWBF2.Types;



namespace LibSWBF2.Wrappers
{
    [StructLayout(LayoutKind.Sequential, Pack=1)]
    public struct Joint 
    {
        public uint BoneCRC;
        public Vector4 BaseRotation;
        public Vector3 BasePosition;
        public uint ParentBoneCRC;
    }


    public sealed class AnimationSkeleton : NativeWrapper
    {
        public Joint[] GetJoints()
        {
            CheckValidity();
            if (!APIWrapper.AnimationSkeleton_GetJoints(NativeInstance, out int numJoints, out IntPtr jointBuffer))
            {
                return new Joint[0];
            }

            return MemUtils.IntPtrToArray<Joint>(jointBuffer, numJoints);            
        }

        public string GetName()
        {
            CheckValidity();
            return Marshal.PtrToStringAnsi(APIWrapper.AnimationSkeleton_GetName(NativeInstance));            
        }
    }
}
