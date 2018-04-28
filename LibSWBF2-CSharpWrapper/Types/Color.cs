using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    public class Color
    {
        struct _Color
        {
            public float r;
            public float g;
            public float b;
            public float a;
        }

        IntPtr pointer;
        _Color color;

        public float R
        {
            get { return color.r; }
            set { color.r = value; }
        }

        public float G
        {
            get { return color.g; }
            set { color.g = value; }
        }

        public float B
        {
            get { return color.b; }
            set { color.b = value; }
        }

        public float A
        {
            get { return color.a; }
            set { color.a = value; }
        }

        public Color() : this(0f, 0f, 0f, 0f) { }

        public Color(float r, float g, float b) : this(r, g, b, 0f) { }

        public Color(float r, float g, float b, float a)
        {
            pointer = API.Color_Create(r, g, b, a);
            color = (_Color)Marshal.PtrToStructure(pointer, typeof(_Color));
        }

        ~Color()
        {
            API.Color_Delete(pointer);
            pointer = IntPtr.Zero;
        }
    }
}
