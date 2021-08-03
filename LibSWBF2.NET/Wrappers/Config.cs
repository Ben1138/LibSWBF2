using System;
using System.Runtime.InteropServices;

using LibSWBF2.Utils;
using LibSWBF2.Types;
using LibSWBF2.Enums;

namespace LibSWBF2.Wrappers
{
    public sealed class Field : NativeWrapper
    {
        public Scope Scope { get; private set; }

        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            if (APIWrapper.Field_FetchAllFields(ptr, out IntPtr scopePtr))
            {
                Scope = FromNative<Scope>(scopePtr);
            }
        }

        public uint GetNameHash()
        {
            CheckValidity();
            return APIWrapper.Field_GetNameHash(NativeInstance);
        }

        public string GetName()
        {
            CheckValidity();
            return Marshal.PtrToStringAnsi(APIWrapper.Field_GetName(NativeInstance));
        }

        public byte GetNumValues()
        {
            CheckValidity();
            return APIWrapper.Field_GetNumValues(NativeInstance);
        }

        public string GetString(byte index=0)
        {
            CheckValidity();
            return Marshal.PtrToStringAnsi(APIWrapper.Field_GetString(NativeInstance, index));
        }

        public EDataValueType GetValueType(byte index=0)
        {
            CheckValidity();
            return APIWrapper.Field_GetValueType(NativeInstance, index);
        }

        public float GetFloat(byte index=0)
        {
            CheckValidity();
            return APIWrapper.Field_GetFloat(NativeInstance, index);
        }

        public Vector2 GetVec2()
        {
            CheckValidity();
            return new Vector2(APIWrapper.Field_GetVec2(NativeInstance));
        }

        public Vector3 GetVec3()
        {
            CheckValidity();
            return new Vector3(APIWrapper.Field_GetVec3(NativeInstance));
        }

        public Vector4 GetVec4()
        {
            CheckValidity();
            return new Vector4(APIWrapper.Field_GetVec4(NativeInstance));
        }
    }


    public sealed class Scope: NativeWrapper
    {
        public Field[] GetFields(uint hash = 0)
        {
            CheckValidity();
            IntPtr fields = APIWrapper.ConfigScope_GetFields(NativeInstance, hash, true, out uint count);
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<Field>(fields, (int) count));
        }

        public Field GetField(uint hash)
        {
            CheckValidity();
            Field[] fields = GetFields(hash);
            return fields.Length == 0 ? null : fields[0];
        }

        public Field[] GetFields(string name)
        {
            CheckValidity();
            return GetFields(HashUtils.GetFNV(name));
        }

        public Field GetField(string name)
        {
            CheckValidity();
            return GetField(HashUtils.GetFNV(name));
        }

        public string GetString(string name)
        {
            CheckValidity();
            Field f = GetField(name);
            if (f == null)
            {
                return "";
            }
            return f.GetString();
        }

        public float GetFloat(string name)
        {
            CheckValidity();
            Field f = GetField(name);
            if (f == null)
            {
                return 0.0f;
            }
            return f.GetFloat();
        }

        public Vector2 GetVec2(string name)
        {
            CheckValidity();
            Field f = GetField(name);
            if (f == null)
            {
                return new Vector2();
            }
            return f.GetVec2();
        }

        public Vector3 GetVec3(string name)
        {
            CheckValidity();
            Field f = GetField(name);
            if (f == null)
            {
                return new Vector3();
            }
            return f.GetVec3();
        }

        public Vector4 GetVec4(string name)
        {
            CheckValidity();
            Field f = GetField(name);
            if (f == null)
            {
                return new Vector4();
            }
            return f.GetVec4();
        }
    }



    public sealed class Config : NativeWrapper
    {
        public uint Name { get; private set; }

        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            if (APIWrapper.Config_FetchSimpleFields(ptr, out uint name))
            {
                Name = name;
            }
        }

        public Field[] GetFields(uint hash = 0)
        {
            CheckValidity();
            IntPtr fields = APIWrapper.ConfigScope_GetFields(NativeInstance, hash, false, out uint count);
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<Field>(fields, (int) count));
        }

        public Field GetField(uint hash)
        {
            CheckValidity();
            Field[] fields = GetFields(hash);
            return fields.Length == 0 ? null : fields[0];
        }

        public Field[] GetFields(string name)
        {
            CheckValidity();
            return GetFields(HashUtils.GetFNV(name));
        }

        public Field GetField(string name)
        {
            CheckValidity();
            return GetField(HashUtils.GetFNV(name));
        }
    }
}
