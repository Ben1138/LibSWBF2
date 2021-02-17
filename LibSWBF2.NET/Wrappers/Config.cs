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
    public class Field : NativeWrapper
    {
        public Field(IntPtr fieldPtr) : base(IntPtr.Zero){ SetPtr(fieldPtr); }
        public Field() : base(IntPtr.Zero){}

        internal override void SetPtr(IntPtr ptr)
        {
            if (APIWrapper.Field_FetchAllFields(ptr, out IntPtr scopePtr, out uint name))
            {
                NativeInstance = ptr;
                scope = new Scope(scopePtr);
            }
        }

        public string GetString()
        {
            return Marshal.PtrToStringAnsi(APIWrapper.Field_GetString(NativeInstance));
        }

        public float GetFloat()
        {
            return APIWrapper.Field_GetFloat(NativeInstance);
        }

        public Vector2 GetVec2()
        {
            return new Vector2(APIWrapper.Field_GetVec2(NativeInstance));
        }

        public Vector3 GetVec3()
        {
            return new Vector3(APIWrapper.Field_GetVec3(NativeInstance));
        }

        public Vector4 GetVec4()
        {
            return new Vector4(APIWrapper.Field_GetVec4(NativeInstance));
        }

        public uint name;
        public Scope scope;

    }


    public class Scope: NativeWrapper
    {
        public Scope(IntPtr scopPtr) : base(scopPtr){}
        public Scope() : base(IntPtr.Zero){}

        public List<Field> GetFields(uint hash = 0)
        {
            IntPtr fields = APIWrapper.ConfigScope_GetFields(NativeInstance, hash, true, out uint count);
            return new List<Field>(MemUtils.IntPtrToWrapperArray<Field>(fields, (int) count));
        }

        public Field GetField(uint hash)
        {
            List<Field> fields = GetFields(hash);
            return fields.Count == 0 ? null : fields[0];
        }

        public List<Field> GetFields(string name)
        {
            return GetFields(HashUtils.GetFNV(name));
        }

        public Field GetField(string name)
        {
            return GetField(HashUtils.GetFNV(name));
        }

        public string GetString(string name)
        {
            Field f = GetField(name);
            if (f == null)
            {
                return "";
            }
            return f.GetString();
        }

        public float GetFloat(string name)
        {
            Field f = GetField(name);
            if (f == null)
            {
                return 0.0f;
            }
            return f.GetFloat();
        }

        public Vector2 GetVec2(string name)
        {
            Field f = GetField(name);
            if (f == null)
            {
                return new Vector2();
            }
            return f.GetVec2();
        }

        public Vector3 GetVec3(string name)
        {
            Field f = GetField(name);
            if (f == null)
            {
                return new Vector3();
            }
            return f.GetVec3();
        }

        public Vector4 GetVec4(string name)
        {
            Field f = GetField(name);
            if (f == null)
            {
                return new Vector4();
            }
            return f.GetVec4();
        }
    }



    public class Config : NativeWrapper
    {
        public Config(IntPtr ConfigPtr) : base(IntPtr.Zero){ SetPtr(ConfigPtr); }
        public Config() : base(IntPtr.Zero){}

        internal override void SetPtr(IntPtr ptr)
        {
            if (APIWrapper.Config_FetchSimpleFields(ptr, out name))
            {
                NativeInstance = ptr;
            }
        }

        public List<Field> GetFields(uint hash = 0)
        {
            IntPtr fields = APIWrapper.ConfigScope_GetFields(NativeInstance, hash, false, out uint count);
            return new List<Field>(MemUtils.IntPtrToWrapperArray<Field>(fields, (int) count));
        }

        public Field GetField(uint hash)
        {
            List<Field> fields = GetFields(hash);
            return fields.Count == 0 ? null : fields[0];
        }

        public List<Field> GetFields(string name)
        {
            return GetFields(HashUtils.GetFNV(name));
        }

        public Field GetField(string name)
        {
            return GetField(HashUtils.GetFNV(name));
        }

        public uint name;
    }
}
