using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Utils;
using LibSWBF2.Logging;
using LibSWBF2.Enums;



namespace LibSWBF2.Wrappers
{
    public class AnimationBank : NativeWrapper
    {
        public AnimationBank(IntPtr AnimationBankPtr) : base(AnimationBankPtr)
        {

        }

        public AnimationBank() : base(IntPtr.Zero) {}


        public bool GetCurve(uint animCRC, uint boneCRC, uint component,
                            out ushort[] inds, out float[] values)
        {
            bool status = APIWrapper.AnimationBank_GetCurve(
                                NativeInstance, animCRC, boneCRC, component,
                                out IntPtr indexBuffer, out IntPtr valueBuffer, 
                                out int numKeys);

            inds = MemUtils.IntPtrToArray<ushort>(indexBuffer, numKeys);
            values = MemUtils.IntPtrToArray<float>(valueBuffer, numKeys);

            return status;
        }

        public uint[] GetAnimationCRCs()
        {
            IntPtr crcs = APIWrapper.AnimationBank_GetAnimationCRCs(NativeInstance, out int numAnims);
            return MemUtils.IntPtrToArray<uint>(crcs, numAnims);
        }

        public bool GetAnimationMetadata(uint animCRC, out int numFrames, out int numBones)
        {
            return APIWrapper.AnimationBank_GetAnimationMetadata(NativeInstance, animCRC, out numFrames, out numBones);
        }
    }
}
