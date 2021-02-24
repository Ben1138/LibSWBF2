using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Utils;
using LibSWBF2.Enums;
using LibSWBF2.Types;

namespace LibSWBF2.Wrappers
{
    public class Material : NativeWrapper
    {
        internal Material(IntPtr MaterialPtr) : base(MaterialPtr) { SetPtr(MaterialPtr); }
        public Material() : base(IntPtr.Zero){}


        internal override void SetPtr(IntPtr ptr)
        {
            if (APIWrapper.Material_FetchAllFields(ptr, out IntPtr specular,
                                                out IntPtr diffuse, out IntPtr texNames,
                                                out int numTexes, out IntPtr attachedLightName,
                                                out uint matFlags, out specularExponent))
            {
                NativeInstance = ptr;

                materialFlags = (MaterialFlags) matFlags;

                specularColor = new Vector3(specular);
                diffuseColor = new Vector3(diffuse);

                textures = MemUtils.IntPtrToStringList(texNames, numTexes);
                attachedLight = Marshal.PtrToStringAnsi(attachedLightName);
            }
        }

        public MaterialFlags materialFlags;
            
        public uint specularExponent;

        public List<string> textures;

        public Vector3 specularColor;
        public Vector3 diffuseColor;

        public string attachedLight;
    }
}