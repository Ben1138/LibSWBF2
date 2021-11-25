using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Enums;
using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{
    public sealed class SoundBank : NativeWrapper
    {
        public uint Name            { get; private set; }
        public bool HasData         { get; private set; }
        public ESoundFormat Format  { get; private set; }
        

        internal override void SetPtr(IntPtr bankPtr)
        {
            base.SetPtr(bankPtr);
            if (APIWrapper.SoundBank_FetchAllFields(bankPtr, out uint nameOut, out bool hasDataOut, 
                                                    out uint formatOut))
            {
                Format = (ESoundFormat) formatOut;
                Name = nameOut;
                HasData = hasDataOut;
            }
        }

        public Sound GetSound(uint nameHash)
        {
            CheckValidity();
            bool r = APIWrapper.SoundBank_GetSound(NativeInstance, nameHash, out IntPtr soundOut);
            return r ? RegisterChild(FromNative<Sound>(soundOut)) : null; 
        }

        public Sound[] GetSounds()
        {
            CheckValidity();
            bool r = APIWrapper.SoundBank_GetSounds(NativeInstance, out IntPtr soundArray, out uint numSounds, out uint soundInc);
            return r ? RegisterChildren(MemUtils.IntPtrToWrapperArray<Sound>(soundArray, (int)numSounds, (int)soundInc)) : new Sound[0];
        }
    }
}