using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Wrappers
{
    public sealed class Sound : NativeWrapper
    {
        public string Name
        {
            get
            {
                CheckValidity();
                return Marshal.PtrToStringAnsi(APIWrapper.Sound_GetName(NativeInstance));
            }
        }

        public bool GetData(out uint sampleRate, out uint sampleCount, out byte blockAlign, out IntPtr data)
        {
            CheckValidity();
            return APIWrapper.Sound_GetData(NativeInstance, out sampleRate, out sampleCount, out blockAlign, out data);
        }

        public bool GetData(out uint sampleRate, out uint sampleCount, out byte blockAlign, out byte[] data)
        {
            CheckValidity();
            if (APIWrapper.Sound_GetData(NativeInstance, out sampleRate, out sampleCount, out blockAlign, out IntPtr dataPtr))
            {
                int dataSize = (int)(sampleCount * blockAlign);
                data = new byte[dataSize];
                Marshal.Copy(dataPtr, data, 0, dataSize);
                return true;
            }
            data = null;
            return false;
        }


        /*
        public bool WriteToWAV(string path)
        {
            if (GetData(out uint sampleRate, out uint sampleCount, out byte blockAlign, out byte[] data))
            {
                uint numsamples = 44100;
                ushort numchannels = 1;
                ushort samplelength = 1; // in bytes
                uint samplerate = 22050;

                FileStream f = new FileStream(path, FileMode.Create);
                BinaryWriter wr = new BinaryWriter(f);

                wr.Write(System.Text.Encoding.ASCII.GetBytes("RIFF"));
                wr.Write((uint) (36 + numsamples * numchannels * samplelength));
                wr.Write(System.Text.Encoding.ASCII.GetBytes("WAVEfmt "));
                wr.Write((uint)16);
                wr.Write((ushort)1);
                wr.Write((ushort)2);
                wr.Write((uint)samplerate);
                wr.Write(samplerate * samplelength * numchannels);
                wr.Write(samplelength * numchannels);
                wr.Write((ushort)(8 * samplelength));
                wr.Write(System.Text.Encoding.ASCII.GetBytes("data"));
                wr.Write(numsamples * samplelength);

                // for now, just a square wave
                Waveform a = new Waveform(440, 50);

                double t = 0.0;
                for (int i = 0; i < numsamples; i++, t += 1.0 / samplerate)
                {
                    wr.Write((byte)((a.sample(t) + (samplelength == 1 ? 128 : 0)) & 0xff));
                }
            }

        }
        */








    }
}
