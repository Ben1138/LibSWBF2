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

        public uint GetUInt(byte index=0)
        {
            CheckValidity();
            return APIWrapper.Field_GetUInt32(NativeInstance, index);
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

        public bool GetField(string name, out Field fieldOut)
        {
            fieldOut = null;
            CheckValidity();
            fieldOut = GetField(name);
            return fieldOut != null;
        }

        public string GetString(string name)
        {
            GetString(name, out String r);
            return r;
        }

        public bool GetString(string name, out string sOut)
        {
            CheckValidity();
            Field f = GetField(name);

            if (f == null)
            {
                sOut = "";
                return false;
            }
            else 
            {
                sOut = f.GetString();
                return true;
            }
        }

        public float GetFloat(string name)
        {
            GetFloat(name, out float r);
            return r;
        }

        public bool GetFloat(string name, out float fOut)
        {
            CheckValidity();
            Field f = GetField(name);

            fOut = f == null ? 0f : f.GetFloat();
            return f != null;
        }


        public uint GetUInt(string name)
        {
            GetUInt(name, out uint r);
            return r;
        }

        public bool GetUInt(string name, out uint uOut)
        {
            CheckValidity();
            Field f = GetField(name);

            uOut = f == null ? 0 : f.GetUInt();
            return f != null;
        }


        public Vector2 GetVec2(string name)
        {
            GetVec2(name, out Vector2 r);
            return r;
        }

        public bool GetVec2(string name, out Vector2 vecOut)
        {
            CheckValidity();
            Field f = GetField(name);

            if (f == null)
            {
                vecOut = new Vector2();
                return false;
            }
            else 
            {
                vecOut = f.GetVec2();
                return true;
            }
        }

        public Vector3 GetVec3(string name)
        {
            GetVec3(name, out Vector3 r);
            return r;
        }

        public bool GetVec3(string name, out Vector3 vecOut)
        {
            CheckValidity();
            Field f = GetField(name);

            if (f == null)
            {
                vecOut = new Vector3();
                return false;
            }
            else 
            {
                vecOut = f.GetVec3();
                return true;
            }
        }

        public Vector4 GetVec4(string name)
        {
            GetVec4(name, out Vector4 r);
            return r;
        }

        public bool GetVec4(string name, out Vector4 vecOut)
        {
            CheckValidity();
            Field f = GetField(name);

            if (f == null)
            {
                vecOut = new Vector4();
                return false;
            }
            else 
            {
                vecOut = f.GetVec4();
                return true;
            }
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
