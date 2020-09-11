using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Runtime.InteropServices;
using System.Security;
using System.Runtime.InteropServices.WindowsRuntime;
using LibSWBF2.Wrappers;

namespace LibSWBF2.Utils
{
    class MemUtils {


        public static T[] ptrsToObjects<T>(IntPtr nativePtr, int count) where T : NativeWrapper, new()
        {
            T[] objectArr = new T[count];

            if (nativePtr == IntPtr.Zero) return objectArr;

            IntPtr[] ptrs = new IntPtr[count];
            
            Marshal.Copy(nativePtr, ptrs, 0, count);
            
            for (int i = 0; i < count; i++){
                objectArr[i] = new T();
                objectArr[i].SetPtr(ptrs[i]);
            }

            return objectArr;
        }
        

        public static List<string> IntPtrToStringList(IntPtr nativePtr, int count)
        {
            List<string> strings = new List<string>();
            IntPtr[] stringPtrs = new IntPtr[count];
            Marshal.Copy(nativePtr, stringPtrs, 0, count);

            for (int i = 0; i < count; i++)
            {
                strings.Add(Marshal.PtrToStringAnsi(stringPtrs[i]));
            }

            return strings;
        }
    }
}
