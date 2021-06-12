using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Utils;
using LibSWBF2.Logging;
using LibSWBF2.Types;



namespace LibSWBF2.Wrappers
{
    public sealed class Instance : NativeWrapper, ISWBFProperties
    {
        public string      Name { get; private set; }
        public Vector4     Rotation { get; private set; }
        public Vector3     Position { get; private set; }
        public EntityClass EntityClass { get; private set; }
        public string      EntityClassName { get; private set; }


        internal override void SetPtr(IntPtr instancePtr)
        {
            base.SetPtr(instancePtr);
            if (APIWrapper.Instance_FetchSimpleFields(instancePtr, out IntPtr namePtr, out IntPtr rot, out IntPtr pos, out IntPtr ecNamePtr, out IntPtr ec))
            {
                Name = Marshal.PtrToStringAnsi(namePtr);
                EntityClass = RegisterChild(FromNative<EntityClass>(ec));
                EntityClassName = Marshal.PtrToStringAnsi(ecNamePtr);
                Rotation = new Vector4(rot);
                Position = new Vector3(pos);
            }
        }

        /// <summary>
        /// will return the first encounter. will fall back to base class, if existent
        /// </summary>
        public bool GetProperty(string propName, out string propValue)
        {
            CheckValidity();
            if (APIWrapper.Instance_GetPropertyFromName(NativeInstance, propName, out IntPtr res))
            {
                propValue = Marshal.PtrToStringAnsi(res);
                return true;
            }
            else
            {
                propValue = "";
                return false;
            }
        }

        /// <summary>
        /// will return the first encounter. will fall back to base class, if existent
        /// </summary>
        public bool GetProperty(uint hashedPropName, out string propValue)
        {
            CheckValidity();
            if (APIWrapper.Instance_GetPropertyFromHash(NativeInstance, hashedPropName, out IntPtr res))
            {
                propValue = Marshal.PtrToStringAnsi(res);
                return true;
            }
            else
            {
                propValue = "";
                return false;
            }
        }

        /// <summary>
        /// will return all encounters. will also recursively search base classes, if existent
        /// </summary>
        public bool GetProperty(string propName, out string[] propValues)
        {
            CheckValidity();
            if (APIWrapper.Instance_GetPropertiesFromName(NativeInstance, propName, out IntPtr res, out uint count))
            {
                propValues = MemUtils.IntPtrToStringList(res, (int)count).ToArray();
                return true;
            }
            else
            {
                propValues = null;
                return false;
            }
        }

        /// <summary>
        /// will return all encounters. will also recursively search base classes, if existent
        /// </summary>
        public bool GetProperty(uint hashedPropName, out string[] propValues)
        {
            CheckValidity();
            if (APIWrapper.Instance_GetPropertiesFromHash(NativeInstance, hashedPropName, out IntPtr res, out uint count))
            {
                propValues = MemUtils.IntPtrToStringList(res, (int)count).ToArray();
                return true;
            }
            else
            {
                propValues = null;
                return false;
            }
        }

        public void GetOverriddenProperties(out uint[] properties, out string[] values)
        {
            CheckValidity();
            APIWrapper.Instance_GetOverriddenProperties(NativeInstance, out IntPtr props, out IntPtr vals, out int count);
            properties = MemUtils.IntPtrToArray<uint>(props, count);
            values = MemUtils.IntPtrToStringList(vals, count).ToArray();
        }
    }
}
