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

        public bool IsSkeletalMesh
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return APIWrapper.Model_IsSkeletalMesh(NativeInstance); 
            }
        }

        public Segment[] GetSegments()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Model_GetSegments(NativeInstance, out IntPtr segmentArr, out uint segmentCount);
            return MemUtils.IntPtrToWrapperArray<Segment>(segmentArr, (int) segmentCount);
        }

        // TODO: swap IntPtr with actualy wrapper class
        public IntPtr[] GetSkeleton()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");

            APIWrapper.Model_GetSkeleton(NativeInstance, out IntPtr boneArr, out uint boneCount);
            IntPtr[] bones = new IntPtr[boneCount];
            Marshal.Copy(boneArr, bones, 0, (int)boneCount);
            return bones;
        }

        public CollisionMesh GetCollisionMesh()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return new CollisionMesh(APIWrapper.Model_GetCollisionMesh(NativeInstance));            
        }
    }
}