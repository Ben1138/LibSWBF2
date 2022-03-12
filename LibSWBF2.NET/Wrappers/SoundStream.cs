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
    public sealed class SoundStream : NativeWrapper
    {
        public uint Name                  { get; private set; }
        public bool HasData               { get; private set; }
        public ESoundFormat Format        { get; private set; }
        public uint NumChannels           { get; private set; }
        public uint NumSubstreams         { get; private set; }
        public uint SubstreamInterleave   { get; private set; }


        internal override void SetPtr(IntPtr streamPtr)
        {
            base.SetPtr(streamPtr);
            if (APIWrapper.SoundStream_FetchAllFields(streamPtr, out uint nameOut, out bool hasDataOut, 
                                                    out uint formatOut, out uint numChannelsOut, 
                                                    out uint numSubstreamsOut, out uint substreamInterleaveOut))
            {
                Format = (ESoundFormat) formatOut;
                Name = nameOut;
                NumChannels = numChannelsOut;
                HasData = hasDataOut;
                NumSubstreams = numSubstreamsOut;
                SubstreamInterleave = substreamInterleaveOut;
            }
        }

        public bool SetFileReader(FileReader reader)
        {
            CheckValidity();
            return APIWrapper.SoundStream_SetFileReader(NativeInstance, reader.GetNativePtr());
        }


        // Will be automatically set to 
        public bool SetFileStreamBuffer(IntPtr buffer, int NumBytes)
        {
            CheckValidity();
            return APIWrapper.SoundStream_SetStreamBuffer(NativeInstance, buffer, NumBytes);
        }

        // Returns num bytes read
        public int ReadBytesFromStream(int NumBytes)
        {
            CheckValidity();
            return (int) APIWrapper.SoundStream_ReadBytesFromStream(NativeInstance, NumBytes);
        }


        public bool SetSegment(uint SegmentNameHash)
        {
            CheckValidity();
            return APIWrapper.SoundStream_SetSegment(NativeInstance, SegmentNameHash);
        }


        /*
        Caller may want to read x samples or read all the samples contained in x bytes.
        Following two methods accomplish those goals, both return the number of samples read.
        */

        public int ReadSamples(IntPtr samplesBuffer, int sampleBufferLength, 
                               int NumSamplesToRead, ESoundFormat format)
        {
            CheckValidity();
            return APIWrapper.SoundStream_SampleReadMethod(NativeInstance, samplesBuffer, sampleBufferLength, NumSamplesToRead, format, out int NumBytesRead, true);
        }



        public unsafe int ReadSamplesPCM16(short[] samplesBuffer) 
        {
            CheckValidity();
            int result = -1;
            fixed (short* bufferPtr = samplesBuffer)
            {
                IntPtr ptr = (IntPtr) bufferPtr;

                result = APIWrapper.SoundStream_SampleReadMethod(NativeInstance, ptr, 2 * samplesBuffer.Length, samplesBuffer.Length, ESoundFormat.PCM16, out int NumBytesRead, true);

            }

            return result;
        }


        public unsafe int ReadSamplesUnity(float[] samplesBuffer) 
        {
            CheckValidity();
            int result = -1;
            fixed (float* bufferPtr = samplesBuffer)
            {
                IntPtr ptr = (IntPtr) bufferPtr;

                result = APIWrapper.SoundStream_SampleReadMethod(NativeInstance, ptr, 4 * samplesBuffer.Length, samplesBuffer.Length, ESoundFormat.Unity, out int NumBytesRead, true);
            }

            return result;
        }




        public int ReadSamplesFromBytes(IntPtr samplesBuffer, int sampleBufferLength,
                                        int NumBytesToRead, ESoundFormat format, 
                                        out int NumBytesRead)
        {
            CheckValidity();
            return APIWrapper.SoundStream_SampleReadMethod(NativeInstance, samplesBuffer, sampleBufferLength, NumBytesToRead, format, out NumBytesRead, false);
        }

        public int GetNumSamplesInBytes(int NumBytes)
        {
            CheckValidity();
            return APIWrapper.SoundStream_GetNumSamplesInBytes(NativeInstance, NumBytes);
        }



        public Sound GetSound(uint nameHash)
        {
            CheckValidity();
            bool r = APIWrapper.SoundStream_GetSound(NativeInstance, nameHash, out IntPtr soundOut);
            return r ? RegisterChild(FromNative<Sound>(soundOut)) : null; 
        }

        public Sound[] GetSounds()
        {
            CheckValidity();
            bool r = APIWrapper.SoundStream_GetSounds(NativeInstance, out IntPtr soundArray, out uint numSounds, out uint soundInc);
            return r ? RegisterChildren(MemUtils.IntPtrToWrapperArray<Sound>(soundArray, (int)numSounds, (int)soundInc)) : new Sound[0];
        }
    }
}