using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Logging;


namespace LibSWBF2.Wrappers
{
    public class Container : NativeWrapper
    {
        private static Dictionary<Type, uint> wrapperMap;
        public Container() : base(APIWrapper.Container_Initialize()){}
        static Container()
        {
            wrapperMap = new Dictionary<Type, uint>();
            wrapperMap[typeof(Model)] = 0;
        }        

        public uint AddLevel(string path)
        {
            return APIWrapper.Container_AddLevel(NativeInstance, path);
        }

        public float GetProgress(uint handle)
        {
            return APIWrapper.Container_GetProgress(NativeInstance, handle);
        }

        public Level GetLevel(uint handle)
        {
            if (GetProgress(handle) < 1.0)
            {
                return null;
            }

            return Level.FromNative(APIWrapper.Container_GetLevel(NativeInstance, handle));
        }

        public void LoadLevels()
        {
            APIWrapper.Container_LoadLevels(NativeInstance);
        }

        public T GetWrapper<T>(string name) where T : NativeWrapper, new()
        {
            if (wrapperMap.ContainsKey(typeof(T)))
            {
                T newObj = new T();
                IntPtr ptr = APIWrapper.Container_GetWrapper(NativeInstance, wrapperMap[typeof(T)], name);

                if (ptr == null)
                {
                    return null;
                }

                newObj.SetPtr(ptr);

                return newObj;
            }

            return null;
        }


        public bool IsDone()
        {
            return APIWrapper.Container_IsDone(NativeInstance);
        }
    }
}
