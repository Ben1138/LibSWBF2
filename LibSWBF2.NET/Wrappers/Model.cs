using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;

namespace LibSWBF2.Wrappers
{
    public class Model : NativeWrapper
    {
        internal Model(IntPtr modelPtr) : base(modelPtr)
        {

        }

        public string Name
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return APIWrapper.Model_GetName(NativeInstance); 
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
            IntPtr[] segments = new IntPtr[segmentCount];
            Marshal.Copy(segmentArr, segments, 0, (int)segmentCount);

            Segment[] segmentsArray = new Segment[segmentCount];
            for (int i = 0; i < segmentCount; i++)
            {
                segmentsArray[i] = new Segment(segments[i]);
            }

            return segmentsArray;
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
    }
}