using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Utils;
using LibSWBF2.Enums;
using LibSWBF2.Types;

namespace LibSWBF2.Wrappers
{
    public sealed class Material : NativeWrapper
    {
        public EMaterialFlags MaterialFlags { get; private set; }
        public uint          SpecularExponent { get; private set; }
        public ReadOnlyCollection<string> Textures { get; private set; }
        public Vector3       SpecularColor { get; private set; }
        public Vector3       DiffuseColor { get; private set; }
        public string        AttachedLight { get; private set; }

        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            if (APIWrapper.Material_FetchAllFields(ptr, out IntPtr specular,
                                                out IntPtr diffuse, out IntPtr texNames,
                                                out int numTexes, out IntPtr attachedLightName,
                                                out uint matFlags, out uint specularExponent))
            {
                MaterialFlags = (EMaterialFlags) matFlags;

                SpecularColor = new Vector3(specular);
                DiffuseColor = new Vector3(diffuse);
                SpecularExponent = specularExponent;

                Textures = new ReadOnlyCollection<string>(MemUtils.IntPtrToStringList(texNames, numTexes));
                AttachedLight = Marshal.PtrToStringAnsi(attachedLightName);
            }
        }
    }
}