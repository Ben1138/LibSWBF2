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
        protected static readonly Dictionary<Type, uint> WrapperTypeMapping = new Dictionary<Type, uint>()
        {
            { typeof(Terrain),            0 },
            { typeof(Model),              1 },
            { typeof(Texture),            2 },
            { typeof(World),              3 },
            { typeof(EntityClass),        4 },
            { typeof(AnimationBank),      5 },
            { typeof(Script),             6 },
            { typeof(Sound),              7 },
            { typeof(Localization),       8 },
            { typeof(AnimationSkeleton),  9 }
        };

        // will be empty in most cases
        private HashSet<WeakReference<NativeWrapper>> Children = new HashSet<WeakReference<NativeWrapper>>();

        protected IntPtr NativeInstance { get; private set; } = IntPtr.Zero;

        // nobody outside this lib may create instances
        protected NativeWrapper() { }

        internal static T FromNative<T>(IntPtr ptr) where T : NativeWrapper, new()
        {
            if (ptr == IntPtr.Zero)
            {
                return null;
            }
            T inst = new T();
            inst.SetPtr(ptr);
            return inst;
        }

        // will be called after creation
        internal virtual void SetPtr(IntPtr ptr)
        {
            NativeInstance = ptr;
        }

        protected void CheckValidity()
        {
            if (!IsValid())
            {
                throw new Exception("Underlying native class is destroyed!");
            }
        }

        protected T RegisterChild<T>(T child) where T : NativeWrapper
        {
            if (child == null) return child;
            Children.Add(new WeakReference<NativeWrapper>(child));
            return child;
        }

        protected T[] RegisterChildren<T>(T[] children) where T : NativeWrapper
        {
            if (children == null) return children;
            for (int i = 0; i < children.Length; ++i)
            {
                if (children[i] != null)
                {
                    Children.Add(new WeakReference<NativeWrapper>(children[i]));
                }
            }
            return children;
        }

        protected void Invalidate()
        {
            NativeInstance = IntPtr.Zero;

            foreach (WeakReference<NativeWrapper> childRef in Children)
            {
                if (childRef.TryGetTarget(out NativeWrapper child))
                {
                    child.Invalidate();
                }
            }
            Children.Clear();
        }

        public bool IsValid()
        {
            return NativeInstance != IntPtr.Zero;
        }
    }
}
