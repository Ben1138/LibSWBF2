using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Enums;
using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{
    public sealed class Model : NativeWrapper
    {
        public string Name { get; private set; }
        public bool   IsSkeletonBroken { get; private set; }
        public bool   IsSkinned { get; private set; }
        public ReadOnlyCollection<Bone> Skeleton { get; private set; }

        IntPtr collisionMeshPtr;
        IntPtr segmentArray;
        int    segmentCount, segmentIncrement;


        internal override void SetPtr(IntPtr modelPtr)
        {
            base.SetPtr(modelPtr);
            if (APIWrapper.Model_FetchSimpleFields(modelPtr, out IntPtr namePtr, out bool isSkinned, out bool isSkeletonBroken,
                                                            out segmentArray, out segmentCount, out segmentIncrement,
                                                            out IntPtr boneArr, out int boneCount, out int boneInc,
                                                            out collisionMeshPtr))
            {
                IsSkinned = isSkinned;
                IsSkeletonBroken = isSkeletonBroken;
                Name = Marshal.PtrToStringAnsi(namePtr);
                Skeleton = new ReadOnlyCollection<Bone>(RegisterChildren(MemUtils.IntPtrToWrapperArray<Bone>(boneArr, boneCount, boneInc)));
            }
        }


        public Segment[] GetSegments()
        {
            CheckValidity();
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<Segment>(segmentArray, segmentCount, segmentIncrement));
        }

        public CollisionMesh GetCollisionMesh()
        {
            CheckValidity();
            return RegisterChild(FromNative<CollisionMesh>(collisionMeshPtr)); 
        }

        public CollisionPrimitive[] GetPrimitivesMasked(ECollisionMaskFlags mask = ECollisionMaskFlags.All)
        {
            CheckValidity();
            APIWrapper.Model_GetPrimitivesMasked(NativeInstance, mask, out int numPrims, out IntPtr ptr);
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<CollisionPrimitive>(ptr, numPrims));
        }
    }
}