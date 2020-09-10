using LibSWBF2.Logging;
using LibSWBF2.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LibSWBF2.Wrappers
{
    public class Level : NativeWrapper
    {
        private HashSet<WeakReference<NativeWrapper>> Children;

        // Make constructor private, so instantiation is only possible via FromFile
        private Level() : base(IntPtr.Zero)
        {
            Children = new HashSet<WeakReference<NativeWrapper>>();
        }

        ~Level()
        {
            Delete();
        }

        /// <summary>
        /// Don't use this method unless you know exactly what you're doing!
        /// This will delete the underlying native Level instance and invalidate this
        /// Level wrapper instance, as well as all its children of whom references might
        /// still float around somewhere.
        /// </summary>
        public void Delete()
        {
            if (!IsValid())
            {
                Logger.Log("Cannot delete invalid Level!", ELogType.Warning);
                return;
            }

            APIWrapper.Level_Destroy(NativeInstance);
            NativeInstance = IntPtr.Zero;

            foreach (WeakReference<NativeWrapper> childRef in Children)
            {
                if (childRef.TryGetTarget(out NativeWrapper child))
                {
                    child.Invalidate();
                }
                else
                {
                    Children.Remove(childRef);
                }
            }
        }

        public static Level FromFile(string path)
        {
            IntPtr native = APIWrapper.Level_FromFile(path);
            if (native == null)
            {
                return null;
            }

            Level level = new Level();
            level.NativeInstance = native;
            return level;
        }

        public bool IsWorldLevel
        {
            get { return APIWrapper.Level_IsWorldLevel(NativeInstance); }
        }

        public Model[] GetModels()
        {
            APIWrapper.Level_GetModels(NativeInstance, out IntPtr modelArr, out uint modelCount);
            
            Model[] models = MemUtils.IntPtrsToWrappers<Model>(modelArr, (int) modelCount);
            
            foreach (Model model in models)
            {
                Children.Add(new WeakReference<NativeWrapper>(model));                
            }

            return models;
        }

        public Model GetModel(string modelName)
        {
            IntPtr modelPtr = APIWrapper.Level_GetModel(NativeInstance, modelName);
            if (modelPtr == null)
            {
                return null;
            }

            Model model = new Model(modelPtr);
            Children.Add(new WeakReference<NativeWrapper>(model));
            return model;
        }
    }
}
