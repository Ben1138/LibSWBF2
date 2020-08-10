using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace LibSWBF2.Wrappers
{
    public class Model
    {
        private IntPtr NativeModel;

        internal Model(IntPtr modelPtr)
        {
            NativeModel = modelPtr;
        }

        ~Model()
        {

        }

        public string Name
        {
            get { return APIWrapper.Model_GetName(NativeModel); }
        }

        public bool IsSkeletalMesh
        {
            get { return APIWrapper.Model_IsSkeletalMesh(NativeModel); }
        }

        public IntPtr[] GetSegments()
        {
            APIWrapper.Model_GetSegments(NativeModel, out IntPtr segmentArr, out uint segmentCount);
            IntPtr[] segments = new IntPtr[segmentCount];
            Marshal.Copy(segmentArr, segments, 0, (int)segmentCount);
            return segments;
        }

        public IntPtr[] GetSkeleton()
        {
            APIWrapper.Model_GetSkeleton(NativeModel, out IntPtr boneArr, out uint boneCount);
            IntPtr[] bones = new IntPtr[boneCount];
            Marshal.Copy(boneArr, bones, 0, (int)boneCount);
            return bones;
        }
    }
}
