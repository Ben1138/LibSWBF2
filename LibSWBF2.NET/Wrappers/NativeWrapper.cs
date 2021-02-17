using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Wrappers;

namespace LibSWBF2.Wrappers
{
    public abstract class NativeWrapper
    {
        protected static Dictionary<Type, uint> WrapperTypeMapping;
        
        static NativeWrapper()
        {
            WrapperTypeMapping = new Dictionary<Type, uint>();
            WrapperTypeMapping[typeof(Terrain)]       = 0;
            WrapperTypeMapping[typeof(Model)]         = 1;
            WrapperTypeMapping[typeof(Texture)]       = 2;
            WrapperTypeMapping[typeof(World)]         = 3;
            WrapperTypeMapping[typeof(EntityClass)]   = 4;
            WrapperTypeMapping[typeof(AnimationBank)] = 5;
            WrapperTypeMapping[typeof(Script)]        = 6;
        }   


        protected IntPtr NativeInstance = IntPtr.Zero;

        internal NativeWrapper(IntPtr native)
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

        internal virtual void SetPtr(IntPtr ptr)
        {
            NativeInstance = ptr;
        }
    }
}
