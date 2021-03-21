using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Logging;
using LibSWBF2.Types;
using LibSWBF2.Utils;
using LibSWBF2.Enums;

namespace LibSWBF2.Wrappers
{
    public sealed class EntityClass : NativeWrapper, ISWBFProperties
    {
        public string           Name { get; private set; }
        public EEntityClassType ClassType { get; private set; }
        public EntityClass      BaseClass { get; private set; }
        public string           BaseClassName { get; private set; }


        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            APIWrapper.EntityClass_FetchAllFields(ptr, out IntPtr name, out byte classType, out IntPtr baseClass, out IntPtr baseClassName);
            Name = Marshal.PtrToStringAnsi(name);
            ClassType = (EEntityClassType)classType;
            BaseClass = FromNative<EntityClass>(baseClass);
            BaseClassName = Marshal.PtrToStringAnsi(baseClassName);
        }

        /// <summary>
        /// will return the first encounter. will fall back to base class, if existent
        /// </summary>
        public bool GetProperty(string propName, out string propValue)
        {
            CheckValidity();
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
            CheckValidity();
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
            CheckValidity();
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
            CheckValidity();
            if (APIWrapper.EntityClass_GetPropertiesFromHash(NativeInstance, hashedPropName, out IntPtr res, out uint count))
            {
                propValues = MemUtils.IntPtrToStringList(res, (int)count).ToArray();
                return true;
            }
            propValues = null;
            return false;
        }

        public bool GetOverriddenProperties(out uint[] properties, out string[] values)
        {
            CheckValidity();
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
