using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibSWBF2.Wrappers
{
    public abstract class NativeWrapper
    {
        protected IntPtr NativeInstance = IntPtr.Zero;

        public NativeWrapper(IntPtr native)
        {
            NativeInstance = native;
        }

        internal void Invalidate()
        {
            NativeInstance = IntPtr.Zero;
        }

        public bool IsValid()
        {
            return NativeInstance != IntPtr.Zero;
        }

        internal void SetPtr(IntPtr ptr)
        {
            NativeInstance = ptr;
        }
    }
}
