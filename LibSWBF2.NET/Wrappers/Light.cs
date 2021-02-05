using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;
using LibSWBF2.Utils;
using LibSWBF2.Enums;
using LibSWBF2.Types;

namespace LibSWBF2.Wrappers
{
    public class Light : NativeWrapper
    {

        private void SetFields(IntPtr ptr)
        {
            name = Marshal.PtrToStringAnsi( APIWrapper.Light_GetAllFields(ptr, out IntPtr rotPtr,
                                        out IntPtr posPtr, out uint kind, 
                                        out IntPtr colPtr, out range,
                                        out IntPtr conePtr)
                                    );

            rotation = new Vector4(rotPtr);
            position = new Vector3(posPtr);
            color = new Vector3(colPtr);
            lightType = (LightType) kind;
            range = lightType == LightType.Dir ? 100.0f : range;
            spotAngles = lightType == LightType.Spot ? new Vector2(conePtr) : new Vector2();
        }

        internal Light(IntPtr lightPtr) : base(lightPtr)
        {
            SetFields(lightPtr);
        }

        internal override void SetPtr(IntPtr ptr)
        {
            SetFields(ptr);
            NativeInstance = ptr;            
        }

        public Light() : base(IntPtr.Zero){}

        public override string ToString()
        {
            return "Name: " + name                + 
            " Position: "   + position.ToString() +
            " Rotation: "   + rotation.ToString() +
            " Color: "      + color.ToString()    +
            " Type: "       + lightType.ToString();
        }

        public string name;
        public LightType lightType;

        public float range;

        public Vector2 spotAngles;
        public Vector3 position, color;
        public Vector4 rotation;
    }
}
