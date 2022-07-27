using LibSWBF2.Wrappers;
using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Utils
{
    class MemUtils
    {
        // Given a pointer to a buffer of class instances, a count, and the size of the C++ class, this method will
        // return NativeWrappers using the offsets of each class element in the native buffer.
        public static T[] IntPtrToWrapperArray<T>(IntPtr nativePtr, int count, int elSize) where T : NativeWrapper, new()
        {
            if (nativePtr == IntPtr.Zero) return new T[0];

            T[] wrappers = new T[count];

            for (int i = 0; i < count; i++)
            {
                wrappers[i] = NativeWrapper.FromNative<T>(IntPtr.Add(nativePtr, elSize * i));
            }

            return wrappers;
        }


        // Given a pointer to a buffer of pointers to class instances and an instance count, this method will return
        // an array of NativeWrappers using each pointer element of the native buffer.
        public static T[] IntPtrToWrapperArray<T>(IntPtr nativePtr, int count) where T : NativeWrapper, new()
        {
            if (nativePtr == IntPtr.Zero || count == 0) return new T[0];

            T[] wrappers = new T[count];
            IntPtr[] ptrArr = new IntPtr[count];
            Marshal.Copy(nativePtr, ptrArr, 0, count);

            for (int i = 0; i < count; i++)
            {
                wrappers[i] = NativeWrapper.FromNative<T>(ptrArr[i]);
            }

            return wrappers;
        }


        // Using the memcpy wrapper (Memory_Blit), this method will extract an array of unmanaged
        // types from a native buffer. Works for all primitive unmanaged types, as well as unmanaged structs
        // (e.g. VertexWeight and soon the Vector types).
        public static T[] IntPtrToArray<T>(IntPtr dataPtr, int count) where T : unmanaged
        {
            T[] array = new T[count];

            if (dataPtr == IntPtr.Zero || count == 0) return array;

            unsafe
            {
                int numBytes = count * sizeof(T);
                T* srcPtr = (T*)dataPtr.ToPointer();
                fixed (T* destPtr = array)
                {
                    APIWrapper.Memory_Blit(destPtr, srcPtr, numBytes);
                }
            }

            return array;
        }



        // Extracts managed strings from an unmanaged array of char pointers.
        public static string[] IntPtrToStringList(IntPtr nativePtr, int count)
        {
            if (nativePtr == IntPtr.Zero)
            {
                return new string[0];
            }

            string[] strings = new string[count];
            IntPtr[] stringPtrs = new IntPtr[count];
            Marshal.Copy(nativePtr, stringPtrs, 0, count);
            for (int i = 0; i < count; i++)
            {
                strings[i] = Marshal.PtrToStringAnsi(stringPtrs[i]);
            }
            return strings;
        }


        // copies given strings into unmanaged memory and returns their addresses
        // CAUTION: you need to free the allocated memory afterwards (e.g. via FreeStrings)
        public static IntPtr[] StringToIntPtrList(string[] strings)
        {
            IntPtr[] stringPtrs = new IntPtr[strings.Length];
            for (int i = 0; i < strings.Length; i++)
            {
                stringPtrs[i] = Marshal.StringToHGlobalAnsi(strings[i]);
            }

            return stringPtrs;
        }


        public static void FreeStrings(IntPtr[] stringPtrs)
        {
            for (int i = 0; i < stringPtrs.Length; ++i)
            {
                Marshal.FreeHGlobal(stringPtrs[i]);
            }
        }


        public static T DerefUnmanaged<T>(IntPtr ptr) where T : unmanaged
        {
            T result;


            unsafe
            {
                T* srcPtr = (T*)ptr.ToPointer();
                result = *srcPtr;
            }


            return result;
        }



    }
}
