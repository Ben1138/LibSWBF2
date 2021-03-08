using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Threading; 

using LibSWBF2.Logging;
using LibSWBF2.Enums;
using LibSWBF2.Utils;


namespace LibSWBF2
{
    public struct SWBF2Handle
    {
        uint NativeHandle;

        public SWBF2Handle(uint nativeHandle)
        {
            NativeHandle = nativeHandle;
        }
        public uint GetNativeHandle() => NativeHandle;

        public bool IsValid() => NativeHandle != uint.MaxValue;
    }
}

namespace LibSWBF2.Wrappers
{
    public class Container : NativeWrapper
    {        
        public Container() : base(APIWrapper.Container_Initialize()){}
        
 
        public bool Delete()
        {
            return APIWrapper.Container_Delete(NativeInstance);
        }


        public SWBF2Handle AddLevel(string path)
        {
            return new SWBF2Handle(APIWrapper.Container_AddLevel(NativeInstance, path));
        }

        public SWBF2Handle AddLevel(string path, string[] subLVLs)
        {
            if (subLVLs == null) subLVLs = new string[0];
            IntPtr[] ptrs = Utils.MemUtils.StringToIntPtrList(subLVLs);
            return new SWBF2Handle(APIWrapper.Container_AddLevelFiltered(NativeInstance, path, ptrs, (uint)ptrs.Length));
        }

        public SWBF2Handle AddSoundBank(string path)
        {
            return new SWBF2Handle(APIWrapper.Container_AddSoundBank(NativeInstance, path));
        }

        public void FreeAll(bool force)
        {
            APIWrapper.Container_FreeAll(NativeInstance, force);
        }

        public float GetProgress(SWBF2Handle handle)
        {
            return APIWrapper.Container_GetProgress(NativeInstance, handle.GetNativeHandle());
        }

        public float GetOverallProgress()
        {
            return APIWrapper.Container_GetOverallProgress(NativeInstance);
        }

        public Level GetLevel(SWBF2Handle handle, bool block = false)
        {
            while (!IsDone())
            {
                if (block)
                {
                    Thread.Sleep(200);
                } 
                else 
                {
                    return null;
                } 
            }

            return Level.FromNative(APIWrapper.Container_GetLevel(NativeInstance, handle.GetNativeHandle()));
        }

        public void LoadLevels()
        {
            APIWrapper.Container_LoadLevels(NativeInstance);
        }

        public T FindWrapper<T>(string name) where T : NativeWrapper, new()
        {
            if (WrapperTypeMapping.ContainsKey(typeof(T)))
            {
                T newObj = new T();
                IntPtr ptr = APIWrapper.Container_GetWrapper(NativeInstance, WrapperTypeMapping[typeof(T)], name);

                if (ptr == IntPtr.Zero)
                {
                    return null;
                }

                newObj.SetPtr(ptr);

                return newObj;
            }

            return null;
        }


        public Config FindConfig(ConfigType type, uint nameHash=0)
        {
            IntPtr cfgPtr = APIWrapper.Container_GetConfig(NativeInstance, (uint) type, nameHash);
            if (cfgPtr == IntPtr.Zero)
            {
                return null;
            }

            return new Config(cfgPtr);
        }


        public Config FindConfig(ConfigType type, string name)
        {
            return FindConfig(type, HashUtils.GetFNV(name));
        }


        public Enums.ELoadStatus GetStatus(SWBF2Handle handle)
        {
            return (Enums.ELoadStatus)APIWrapper.Container_GetStatus(NativeInstance, handle.GetNativeHandle());
        }

        public bool IsDone()
        {
            return APIWrapper.Container_IsDone(NativeInstance);
        }
    }
}
