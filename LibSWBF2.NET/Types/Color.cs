using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    public unsafe class Color
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct _Color
        {
            public float r;
            public float g;
            public float b;
            public float a;
        }

        internal _Color* ptr;

        public float R
        {
            get { return ptr->r; }
            set { ptr->r = value; }
        }

        public float G
        {
            get { return ptr->g; }
            set { ptr->g = value; }
        }

        public float B
        {
            get { return ptr->b; }
            set { ptr->b = value; }
        }

        public float A
        {
            get { return ptr->a; }
            set { ptr->a = value; }
        }

        public void SetColor(Color newColor)
        {
            SetColor(newColor.R, newColor.G, newColor.B, newColor.A);
        }

        public void SetColor(float r, float g, float b, float a=1f)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
        
        internal Color(_Color* ptr)
        {
            if (ptr == null)
                throw new NullReferenceException("Given Pointer was NULL!");

            this.ptr = ptr;
        }
    }
}
