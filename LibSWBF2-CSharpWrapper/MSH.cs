using System;
using System.Runtime.InteropServices;
using LibSWBF2.Types;

namespace LibSWBF2
{
    public class MSH
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct _MSH
        {
            public Color._Color color;
        }

        internal unsafe _MSH* ptr;

        public Color Color { get; private set; }


        public unsafe MSH(string path)
        {
            ptr = API.MSH_LoadFromFile(path);

            if (ptr == null)
                throw new ArgumentException("File not found?");

            Color = new Color(&ptr->color);
        }

        unsafe ~MSH()
        {
            API.MSH_Delete(ptr);
        }
    }
}
