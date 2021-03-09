using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Logging;
using LibSWBF2.Types;
using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{
    public class EntityClass : NativeWrapper
    {
        public EntityClass(IntPtr ecPtr) : base(ecPtr){}

        public EntityClass() : base(IntPtr.Zero) {}


        /// <summary>
        /// will return the first encounter. will fall back to base class, if existent
        /// </summary>
        public bool GetProperty(string propName, out string propValue)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            if (APIWrapper.EntityClass_GetPropertyFromName(NativeInstance, propName, out IntPtr res))
            {
                propValue = Marshal.PtrToStringAnsi(res);
                return true;
            }
            propValue = "";
            return false;
        }

        /// <summary>
        /// will return the first encounter. will fall back to base class, if existent
        /// </summary>
        public bool GetProperty(uint hashedPropName, out string propValue)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            if (APIWrapper.EntityClass_GetPropertyFromHash(NativeInstance, hashedPropName, out IntPtr res))
            {
                propValue = Marshal.PtrToStringAnsi(res);
                return true;
            }
            propValue = "";
            return false;
        }

        /// <summary>
        /// will return all encounters. will also recursively search base classes, if existent
        /// </summary>
        public bool GetProperty(string propName, out string[] propValues)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            if (APIWrapper.EntityClass_GetPropertiesFromName(NativeInstance, propName, out IntPtr res, out uint count))
            {
                propValues = MemUtils.IntPtrToStringList(res, (int)count).ToArray();
                return true;
            }
            propValues = null;
            return false;
        }

        /// <summary>
        /// will return all encounters. will also recursively search base classes, if existent
        /// </summary>
        public bool GetProperty(uint hashedPropName, out string[] propValues)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            if (APIWrapper.EntityClass_GetPropertiesFromHash(NativeInstance, hashedPropName, out IntPtr res, out uint count))
            {
                propValues = MemUtils.IntPtrToStringList(res, (int)count).ToArray();
                return true;
            }
            propValues = null;
            return false;
        }


        public string Name
        {
            get
            {
                if (!IsValid()) return "";// throw new Exception("Underlying native class is destroyed!");
                return Marshal.PtrToStringAnsi(APIWrapper.EntityClass_GetName(NativeInstance));               
            }
        }

        public string BaseName
        {
            get
            {
                if (!IsValid()) return "";// throw new Exception("Underlying native class is destroyed!");
                return Marshal.PtrToStringAnsi(APIWrapper.EntityClass_GetBaseName(NativeInstance));
            }
        }

        public EntityClass GetBase()
        {
            IntPtr basePtr = APIWrapper.EntityClass_GetBase(NativeInstance);
            if (basePtr != IntPtr.Zero)
            {
                return new EntityClass(basePtr);
            }
            return null;
        }

        public bool GetOverriddenProperties(out uint[] properties, out string[] values)
        {
            bool status = APIWrapper.EntityClass_GetOverriddenProperties(NativeInstance, out IntPtr props, out IntPtr vals, out int count);

            if (status)
            {
                properties = MemUtils.IntPtrToArray<uint>(props, count);
                values = MemUtils.IntPtrToStringList(vals, count).ToArray();
            }
            else 
            {
                properties = new uint[0];
                values = new string[0];
            }

            return status;
        }
    }
}
