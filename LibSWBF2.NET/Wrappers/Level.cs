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
    public class Level : NativeWrapperManager
    {

        // Make constructor private, so instantiation is only possible via FromFile
        private Level() : base(){}


        /// <summary>
        /// Don't use this method unless you know exactly what you're doing!
        /// This will delete the underlying native Level instance and invalidate this
        /// Level wrapper instance, as well as all its children of whom references might
        /// still float around somewhere.
        /// </summary>
        public override void Delete()
        {
            if (!IsValid())
            {
                Logger.Log("Cannot delete invalid Level!", ELogType.Warning);
                return;
            }

            if (IsOwned)
            {
                Logger.Log("Cannot delete a level which is maintained by a Container!", ELogType.Warning);
                return;
            }

            APIWrapper.Level_Destroy(NativeInstance);
            Invalidate();
        }

        public static Level FromFile(string path)
        {
            IntPtr native = APIWrapper.Level_FromFile(path);
            if (native == IntPtr.Zero)
            {
                return null;
            }

            Level level = new Level();
            level.NativeInstance = native;
            return level;
        }

        internal static Level FromNative(IntPtr native)
        {
            if (native == IntPtr.Zero)
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

        public string name
        {
            get { return Marshal.PtrToStringAnsi(APIWrapper.Level_GetName(NativeInstance)); }
        }


        public T GetWrapper<T>(string name) where T : NativeWrapper, new()
        {
            if (wrapperMap.ContainsKey(typeof(T)))
            {
                T newObj = new T();
                IntPtr ptr = APIWrapper.Level_GetWrapper(NativeInstance, wrapperMap[typeof(T)], name);

                if (ptr == IntPtr.Zero)
                {
                    return null;
                }

                newObj.SetPtr(ptr);
                Children.Add(new WeakReference<NativeWrapper>(newObj));

                return newObj;
            }

            return null;
        }


        public T[] GetWrappers<T>() where T : NativeWrapper, new()
        {
            T[] wrappers = new T[0];
            if (wrapperMap.ContainsKey(typeof(T)))
            {
                IntPtr ptr = APIWrapper.Level_GetWrappers(NativeInstance, wrapperMap[typeof(T)], out uint num, out uint inc);

                wrappers = MemUtils.IntPtrToWrapperArray<T>(ptr, (int) num, (int) inc);
                for (int i = 0; i < wrappers.Length; i++)
                {
                    Children.Add(new WeakReference<NativeWrapper>(wrappers[i]));
                }
            }
            return wrappers;
        }


        public Config GetConfig(uint hash, ConfigType cfgType)
        {
            IntPtr ptr = APIWrapper.Level_GetConfig(NativeInstance, (uint) cfgType, hash);
            return ptr == IntPtr.Zero ? null : new Config(ptr);           
        }

        public Config GetConfig(string name, ConfigType cfgType)
        {
            return GetConfig(HashUtils.GetFNV(name), cfgType);
        }

        public List<Config> GetConfigs(ConfigType cfgType)
        {
            IntPtr ptr = APIWrapper.Level_GetConfigs(NativeInstance, (uint) cfgType, out int count);
            if (ptr == IntPtr.Zero)
            {
                return new List<Config>();
            }
            return new List<Config>(MemUtils.IntPtrToWrapperArray<Config>(ptr, count));
        }
    }
}
