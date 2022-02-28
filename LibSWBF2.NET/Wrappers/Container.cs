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
        ushort NativeHandle;

        public SWBF2Handle(ushort nativeHandle)
        {
            NativeHandle = nativeHandle;
        }
        public uint GetNativeHandle() => NativeHandle;

        public bool IsValid() => NativeHandle != ushort.MaxValue;
    }
}

namespace LibSWBF2.Wrappers
{
    public sealed class Container : NativeWrapper
    {
        public Container()
        {
            SetPtr(APIWrapper.Container_Initialize());
        }

        public bool Delete()
        {
            CheckValidity();
            bool success = APIWrapper.Container_Delete(NativeInstance);
            Invalidate();
            return success;
        }

        public SWBF2Handle AddLevel(string path)
        {
            CheckValidity();
            return new SWBF2Handle(APIWrapper.Container_AddLevel(NativeInstance, path));
        }

        public SWBF2Handle AddLevel(string path, string[] subLVLs)
        {
            CheckValidity();
            if (subLVLs == null) subLVLs = new string[0];
            IntPtr[] ptrs = MemUtils.StringToIntPtrList(subLVLs);
            SWBF2Handle h = new SWBF2Handle(APIWrapper.Container_AddLevelFiltered(NativeInstance, path, ptrs, (uint)ptrs.Length));
            MemUtils.FreeStrings(ptrs);
            return h;
        }

        public void FreeAll(bool force)
        {
            CheckValidity();
            Invalidate();
            APIWrapper.Container_FreeAll(NativeInstance, force);
        }

        public float GetProgress(SWBF2Handle handle)
        {
            CheckValidity();
            return APIWrapper.Container_GetProgress(NativeInstance, handle.GetNativeHandle());
        }

        public float GetOverallProgress()
        {
            CheckValidity();
            return APIWrapper.Container_GetOverallProgress(NativeInstance);
        }

        public Level GetLevel(SWBF2Handle handle, bool block = false)
        {
            CheckValidity();
            while (block && (GetStatus(handle) == ELoadStatus.Loading || GetStatus(handle) == ELoadStatus.Uninitialized))
            {
                Thread.Sleep(200);
            }

            IntPtr ptr = APIWrapper.Container_GetLevel(NativeInstance, handle.GetNativeHandle());
            Level level = RegisterChild(FromNative<Level>(ptr));
            if (level != null)
            {
                level.bHasOwner = true;
            }
            return level;
        }

        public SWBF2Handle[] GetLoadedLevels()
        {
            APIWrapper.Container_GetLoadedLevels(NativeInstance, out IntPtr handles, out ushort count);
            ushort[] arr = MemUtils.IntPtrToArray<ushort>(handles, count);
            SWBF2Handle[] res = new SWBF2Handle[arr.Length];
            for (int i = 0; i < arr.Length; ++i)
            {
                res[i] = new SWBF2Handle(arr[i]);
            }
            return res;
        }

        public void LoadLevels()
        {
            CheckValidity();
            APIWrapper.Container_LoadLevels(NativeInstance);
        }

        public T Get<T>(string name) where T : NativeWrapper, new()
        {
            CheckValidity();
            if (WrapperTypeMapping.ContainsKey(typeof(T)))
            {
                IntPtr ptr = APIWrapper.Container_GetWrapper(NativeInstance, WrapperTypeMapping[typeof(T)], name);
                return RegisterChild(FromNative<T>(ptr));
            }
            return null;
        }

        public T Get<T>(uint name) where T : NativeWrapper, new()
        {
            CheckValidity();
            if (WrapperTypeMapping.ContainsKey(typeof(T)))
            {
                IntPtr ptr = APIWrapper.Container_GetWrapperFNV(NativeInstance, WrapperTypeMapping[typeof(T)], name);
                return RegisterChild(FromNative<T>(ptr));
            }
            return null;
        }

        public Config FindConfig(EConfigType type, uint nameHash=0)
        {
            CheckValidity();
            IntPtr ptr = APIWrapper.Container_GetConfig(NativeInstance, (uint)type, nameHash);
            return RegisterChild(FromNative<Config>(ptr));
        }


        public Config FindConfig(EConfigType type, string name)
        {
            CheckValidity();
            return FindConfig(type, HashUtils.GetFNV(name));
        }


        public ELoadStatus GetStatus(SWBF2Handle handle)
        {
            CheckValidity();
            return (ELoadStatus)APIWrapper.Container_GetStatus(NativeInstance, handle.GetNativeHandle());
        }

        public bool IsDone()
        {
            CheckValidity();
            return APIWrapper.Container_IsDone(NativeInstance);
        }
    }
}
