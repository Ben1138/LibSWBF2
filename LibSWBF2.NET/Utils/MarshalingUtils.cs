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

        /*  FROM https://stackoverflow.com/a/39961349  */
        public delegate object ConstructorDelegate(params object[] args);

        private static Dictionary<Type,ConstructorDelegate> constructorsDict = new Dictionary<Type,ConstructorDelegate>();

        public static ConstructorDelegate CreateConstructor(Type type, params Type[] parameters)
        {
            // Get the constructor info for these parameters
            var constructorInfo = type.GetConstructor(parameters);

            // define a object[] parameter
            var paramExpr = Expression.Parameter(typeof(Object[]));

            // To feed the constructor with the right parameters, we need to generate an array 
            // of parameters that will be read from the initialize object array argument.
            var constructorParameters = parameters.Select((paramType, index) =>
                // convert the object[index] to the right constructor parameter type.
                Expression.Convert(
                    // read a value from the object[index]
                    Expression.ArrayAccess(
                        paramExpr,
                        Expression.Constant(index)),
                    paramType)).ToArray();

            // just call the constructor.
            var body = Expression.New(constructorInfo, constructorParameters);

            var constructor = Expression.Lambda<ConstructorDelegate>(body, paramExpr);
            return constructor.Compile();
        }
    
        public static T[] ptrsToObjects<T>(IntPtr nativePtr, int count) where T : NativeWrapper
        {
            T[] objectArr = new T[count];
            IntPtr[] ptrs = new IntPtr[count];

            
            if (!constructorsDict.ContainsKey(typeof(T)))
            {
                constructorsDict[typeof(T)] = CreateConstructor(typeof(T), typeof(IntPtr));
            }

            var typeConstructor = constructorsDict[typeof(T)];
            

            //var typeConstructor = CreateConstructor(typeof(T), typeof(IntPtr));

            if (nativePtr == IntPtr.Zero)
            {
                return objectArr;
            }

            Marshal.Copy(nativePtr, ptrs, 0, count);
            
            for (int i = 0; i < count; i++){
                objectArr[i] = (T) typeConstructor(ptrs[i]);
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
