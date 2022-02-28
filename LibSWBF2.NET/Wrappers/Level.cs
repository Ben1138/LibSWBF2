using LibSWBF2.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Utils;
using LibSWBF2.Types;
using LibSWBF2.Enums;



namespace LibSWBF2.Wrappers
{
    public sealed class Level : NativeWrapper
    {
        internal bool bHasOwner = false;

        /// <summary>
        /// Don't use this method unless you know exactly what you're doing!
        /// This will delete the underlying native Level instance and invalidate this
        /// Level wrapper instance, as well as all its children of whom references might
        /// still float around somewhere.
        /// </summary>
        public void Delete()
        {
            CheckValidity();
            if (bHasOwner)
            {
                Logger.Log("Cannot delete Level that is owned by a Container!", ELogType.Warning);
                return;
            }
            Invalidate();
            APIWrapper.Level_Destroy(NativeInstance);
        }

        public static Level FromFile(string path)
        {
            return FromNative<Level>(APIWrapper.Level_FromFile(path));
        }

        public bool IsWorldLevel
        {
            get { CheckValidity(); return APIWrapper.Level_IsWorldLevel(NativeInstance); }
        }


        public string Name
        {
            get { CheckValidity(); return Marshal.PtrToStringAnsi(APIWrapper.Level_GetName(NativeInstance)); }
        }

        public string Path
        {
            get { CheckValidity(); return Marshal.PtrToStringAnsi(APIWrapper.Level_GetPath(NativeInstance)); }
        }


        public T Get<T>(string name) where T : NativeWrapper, new()
        {
            CheckValidity();
            if (WrapperTypeMapping.ContainsKey(typeof(T)))
            {
                IntPtr ptr = APIWrapper.Level_GetWrapper(NativeInstance, WrapperTypeMapping[typeof(T)], name);
                return RegisterChild(FromNative<T>(ptr));
            }
            return null;
        }

        public T Get<T>(uint name) where T : NativeWrapper, new()
        {
            CheckValidity();
            if (WrapperTypeMapping.ContainsKey(typeof(T)))
            {
                IntPtr ptr = APIWrapper.Level_GetWrapperFNV(NativeInstance, WrapperTypeMapping[typeof(T)], name);
                return RegisterChild(FromNative<T>(ptr));
            }
            return null;
        }

        public T[] Get<T>() where T : NativeWrapper, new()
        {
            CheckValidity();
            T[] wrappers = new T[0];
            if (WrapperTypeMapping.ContainsKey(typeof(T)))
            {
                IntPtr ptr = APIWrapper.Level_GetWrappers(NativeInstance, WrapperTypeMapping[typeof(T)], out uint num, out uint inc);

                wrappers = MemUtils.IntPtrToWrapperArray<T>(ptr, (int) num, (int) inc);
                for (int i = 0; i < wrappers.Length; i++)
                {
                    RegisterChild(wrappers[i]);
                }
            }
            return wrappers;
        }


        public Config GetConfig(uint hash, EConfigType cfgType)
        {
            CheckValidity();
            IntPtr ptr = APIWrapper.Level_GetConfig(NativeInstance, cfgType, hash);
            return RegisterChild(FromNative<Config>(ptr));
        }

        public Config GetConfig(string name, EConfigType cfgType)
        {
            CheckValidity();
            return GetConfig(HashUtils.GetFNV(name), cfgType);
        }

        public Config[] GetConfigs(EConfigType cfgType)
        {
            CheckValidity();
            IntPtr ptr = APIWrapper.Level_GetConfigs(NativeInstance, cfgType, out int count);
            if (ptr == IntPtr.Zero)
            {
                return new Config[0];
            }
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<Config>(ptr, count));
        }
    }
}
