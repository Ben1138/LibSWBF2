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
        public Model(IntPtr modelPtr) : base(IntPtr.Zero) { SetPtr(modelPtr); }
        public Model() : base(IntPtr.Zero){}

        public string name="";

        public bool isSkeletonBroken;
        public bool isSkinned;

        public Bone[] skeleton;

        private IntPtr collisionMeshPtr;

        private IntPtr segmentArray;
        private int segmentCount, segmentIncrement;


        internal override void SetPtr(IntPtr modelPtr)
        {
            if (APIWrapper.Model_FetchSimpleFields(modelPtr, out IntPtr namePtr, out isSkinned, out isSkeletonBroken,
                                                            out segmentArray, out segmentCount, out segmentIncrement,
                                                            out IntPtr boneArr, out int boneCount, out int boneInc,
                                                            out collisionMeshPtr))
            {
                NativeInstance = modelPtr;
                name = Marshal.PtrToStringAnsi(namePtr);
                skeleton = MemUtils.IntPtrToWrapperArray<Bone>(boneArr, boneCount, boneInc);
            }
        }


        public Segment[] GetSegments()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToWrapperArray<Segment>(segmentArray, segmentCount, segmentIncrement);
        }

        public CollisionMesh GetCollisionMesh()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return collisionMeshPtr == IntPtr.Zero ? null : new CollisionMesh(collisionMeshPtr);     
        }

        public CollisionPrimitive[] GetPrimitivesMasked(uint mask = 0xffffffff)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Model_GetPrimitivesMasked(NativeInstance, mask, out int numPrims, out IntPtr ptr);
            return MemUtils.IntPtrToWrapperArray<CollisionPrimitive>(ptr, numPrims);
        }
    }
}