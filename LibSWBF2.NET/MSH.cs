using System;
using System.Runtime.InteropServices;
using LibSWBF2.Types;

namespace LibSWBF2
{
    public unsafe class MSH
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct _MSH
        {
            public Color._Color color;
        }

        internal _MSH* ptr;

        public Color Color { get; private set; }


        public MSH(string path)
        {
            ptr = API.MSH_LoadFromFile(path);

            if (ptr == null)
                throw new ArgumentException("File not found?");

            Color = new Color(&ptr->color);
        }

        ~MSH()
        {
            API.MSH_Delete(ptr);
        }
    }
}
