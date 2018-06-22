using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    public class Color
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct _Color
        {
            public float r;
            public float g;
            public float b;
            public float a;
        }

        internal unsafe _Color* ptr;

        public float R
        {
            get { unsafe { return ptr->r; } }
            set { unsafe { ptr->r = value; } }
        }

        public float G
        {
            get { unsafe { return ptr->g; } }
            set { unsafe { ptr->g = value; } }
        }

        public float B
        {
            get { unsafe { return ptr->b; } }
            set { unsafe { ptr->b = value; } }
        }

        public float A
        {
            get { unsafe { return ptr->a; } }
            set { unsafe { ptr->a = value; } }
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
        
        internal unsafe Color(_Color* ptr)
        {
            if (ptr == null)
                throw new NullReferenceException("Given Pointer was NULL!");

            this.ptr = ptr;
        }
    }
}
