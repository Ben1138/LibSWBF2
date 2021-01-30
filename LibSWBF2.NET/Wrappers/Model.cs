using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Logging;
using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{
    public class Model : NativeWrapper
    {
        public Model(IntPtr modelPtr) : base(modelPtr) {}
        public Model() : base(IntPtr.Zero){}

        public string Name
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return Marshal.PtrToStringAnsi(APIWrapper.Model_GetName(NativeInstance)); 
            }
        }

        public bool IsSkinnedMesh
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return APIWrapper.Model_IsSkinnedMesh(NativeInstance); 
            }
        }


        public bool IsSkeletonBroken
        {
            get
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return APIWrapper.Model_IsSkeletonBroken(NativeInstance);
            }
        }

        public Bone[] GetSkeleton()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Model_GetSkeleton(NativeInstance, out IntPtr bones, out uint numBones, out int inc);
            return MemUtils.IntPtrToWrapperArray<Bone>(bones, (int) numBones, inc);
        }

        public Segment[] GetSegments()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Model_GetSegments(NativeInstance, out IntPtr segmentArr, out uint segmentCount);
            return MemUtils.IntPtrToWrapperArray<Segment>(segmentArr, (int) segmentCount);
        }

        public CollisionMesh GetCollisionMesh()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            IntPtr collPtr = APIWrapper.Model_GetCollisionMesh(NativeInstance);  

            if (collPtr == IntPtr.Zero)
            {
                return null;
            }   
            else
            {
                return new CollisionMesh(collPtr);
            }       
        }

        public CollisionPrimitive[] GetPrimitivesMasked(uint mask = 0xffffffff)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Model_GetPrimitivesMasked(NativeInstance, mask, out int numPrims, out IntPtr ptr);
            return MemUtils.IntPtrToWrapperArray<CollisionPrimitive>(ptr, numPrims);
        }
    }
}