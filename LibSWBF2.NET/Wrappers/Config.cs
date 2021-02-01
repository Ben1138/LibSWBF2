using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Logging;
using LibSWBF2.Utils;
using LibSWBF2.Types;

namespace LibSWBF2.Wrappers
{
    public class Config : NativeWrapper
    {
        public Config(IntPtr ConfigPtr) : base(ConfigPtr){}
        public Config() : base(IntPtr.Zero){}


        public List<Config> GetChildConfigs(uint hash)
        {
            IntPtr configs = APIWrapper.Config_GetChildConfigs(NativeInstance, hash, out int numConfigs, out int inc);
            return new List<Config>(MemUtils.IntPtrToWrapperArray<Config>(configs, numConfigs, inc));
        }

        public bool IsPropertySet(uint hash)
        {
            return APIWrapper.Config_IsPropertySet(NativeInstance, hash);
        }

        public bool IsPropertySet(string str)
        {
            return IsPropertySet(HashUtils.GetFNV(str));
        }

        public List<string> GetStrings(uint hash)
        {
            IntPtr stringsPtr = APIWrapper.Config_GetStrings(NativeInstance, hash, out int count);
            return MemUtils.IntPtrToStringList(stringsPtr, count);
        }

        public List<string> GetStrings(string str)
        {
            return GetStrings(HashUtils.GetFNV(str));
        }

        public string GetString(uint hash)
        {
            return Marshal.PtrToStringAnsi(APIWrapper.Config_GetString(NativeInstance, hash));
        }

        public string GetString(string str)
        {
            return GetString(HashUtils.GetFNV(str));
        }

        public float GetFloat(uint hash)
        {
            return APIWrapper.Config_GetFloat(NativeInstance, hash);
        }

        public float GetFloat(string str)
        {
            return GetFloat(HashUtils.GetFNV(str));
        }

        public Vector2 GetVec2(uint hash)
        {
            return new Vector2(APIWrapper.Config_GetVec2(NativeInstance, hash));
        }

        public Vector2 GetVec2(string str)
        {
            return GetVec2(HashUtils.GetFNV(str));
        }

        public Vector3 GetVec3(uint hash)
        {
            return new Vector3(APIWrapper.Config_GetVec3(NativeInstance, hash));
        }

        public Vector3 GetVec3(string str)
        {
            return GetVec3(HashUtils.GetFNV(str));
        }

        public Vector4 GetVec4(uint hash)
        {
            return new Vector4(APIWrapper.Config_GetVec4(NativeInstance, hash));
        }

        public Vector4 GetVec4(string str)
        {
            return GetVec4(HashUtils.GetFNV(str));
        }
    }
}
