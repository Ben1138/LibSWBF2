using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Threading; 

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
            wrapperMap[typeof(Model)]        = 1;
            wrapperMap[typeof(Texture)]      = 2;
            wrapperMap[typeof(World)]        = 3;
            wrapperMap[typeof(EntityClass)]  = 4;
            wrapperMap[typeof(AnimationBank)] = 5;
        }    



        public bool Delete()
        {
            return APIWrapper.Container_Delete(NativeInstance);
        }


        public uint AddLevel(string path)
        {
            return APIWrapper.Container_AddLevel(NativeInstance, path);
        }

        public float GetProgress(uint handle)
        {
            return APIWrapper.Container_GetProgress(NativeInstance, handle);
        }

        public Level GetLevel(uint handle, bool block = false)
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

            return Level.FromNative(APIWrapper.Container_GetLevel(NativeInstance, handle));
        }

        public void LoadLevels()
        {
            APIWrapper.Container_LoadLevels(NativeInstance);
        }

        public T FindWrapper<T>(string name) where T : NativeWrapper, new()
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
