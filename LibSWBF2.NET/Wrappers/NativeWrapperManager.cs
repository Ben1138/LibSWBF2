using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibSWBF2.Wrappers
{
    public abstract class NativeWrapperManager : NativeWrapper
    {
        protected HashSet<WeakReference<NativeWrapper>> Children;

        protected bool IsOwned = false;
        protected void SetOwnedChild(NativeWrapperManager manager)
        {
            manager.IsOwned = true;
        }

        protected static Dictionary<Type, uint> wrapperMap;
        static NativeWrapperManager()
        {
            wrapperMap = new Dictionary<Type, uint>();
            wrapperMap[typeof(Terrain)] = 0;
            wrapperMap[typeof(Model)] = 1;
            wrapperMap[typeof(Texture)] = 2;
            wrapperMap[typeof(World)] = 3;
            wrapperMap[typeof(EntityClass)] = 4;
            wrapperMap[typeof(AnimationBank)] = 5;
        }

        protected NativeWrapperManager() : base(IntPtr.Zero)
        {
            Children = new HashSet<WeakReference<NativeWrapper>>();
        }

        protected NativeWrapperManager(IntPtr ptr) : base(ptr)
        {
            Children = new HashSet<WeakReference<NativeWrapper>>();
        }


        ~NativeWrapperManager()
        {
            foreach (WeakReference<NativeWrapper> childRef in Children)
            {
                if (childRef.TryGetTarget(out NativeWrapper child))
                {
                    child.Invalidate();
                }
            }
            Children.Clear();

            if (IsValid() && !IsOwned)
            {
                Delete();
                Invalidate();
            }
        }


        public virtual void Delete(){}
    }
}
