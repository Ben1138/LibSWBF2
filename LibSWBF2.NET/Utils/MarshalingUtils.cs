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

        public static T[] IntPtrToWrapperArray<T>(IntPtr nativePtr, int count) where T : NativeWrapper, new()
        {
            if (nativePtr == IntPtr.Zero) return new T[0];

            T[] wrappers = new T[count];
            IntPtr[] ptrArr = new IntPtr[count];
            Marshal.Copy(nativePtr, ptrArr, 0, count);

            for (int i = 0; i < count; i++){
                wrappers[i] = new T();
                wrappers[i].SetPtr(ptrArr[i]);
            }

            return wrappers;
        }


        public static T[] IntPtrToArray<T>(IntPtr dataPtr, int count) where T : unmanaged
        {
            if (dataPtr == IntPtr.Zero || count == 0) return new T[0];

            T[] array = new T[count];
            int opt = 0;

            if (opt == 0) {        
                unsafe
                {
                    int numBytes = count * sizeof(T);
                    T* srcPtr = (T*) dataPtr.ToPointer();
                    fixed (T* destPtr = array)
                    {
                        long* srcPtrLong  = (long *) srcPtr;
                        long* destPtrLong = (long *) destPtr; 

                        var j = 0;
                        while (j < numBytes / 8)
                        {
                          *(destPtrLong + j++) = *(srcPtrLong++);
                        }

                        byte* srcPtrByte  = (byte *) srcPtr;
                        byte* destPtrByte = (byte *) destPtr;

                        j *= 8;
                        while (j < numBytes)
                        {
                            *(destPtrByte + j++) = *(srcPtrByte++);
                        }
                    }
                }
            }
            else {
                unsafe
                {
                    int numBytes = count * sizeof(T);
                    T* srcPtr = (T*) dataPtr.ToPointer();
                    fixed (T* destPtr = array)
                    {
                        APIWrapper.Memory_Blit((void *) destPtr, (void *) srcPtr, numBytes);
                    }
                }    
            }

            return array;
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
