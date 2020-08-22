using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;

namespace LibSWBF2.Wrappers
{
    public class Terrain : NativeWrapper
    {
        internal Terrain(IntPtr terrainPtr) : base(terrainPtr)
        {

        }

        public List<string> Names
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                APIWrapper.Terrain_GetTexNames(NativeInstance, out uint numTextures, out IntPtr strings);

                List<string> textureNames = new List<string>();

                if (numTextures > 0)
                {
                    IntPtr[] stringPointers = new IntPtr[numTextures];
                    Marshal.Copy(strings, stringPointers, 0, (int) numTextures);

                    for (uint i = 0; i < numTextures; i++)
                    {
                        string texName = Marshal.PtrToStringAnsi(stringPointers[i]);
                        textureNames.Add(texName);
                    }

                }  

                return textureNames;
            }
        }

        public float[] Vertices
        {
            get
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                APIWrapper.Terrain_GetVerts(NativeInstance, out uint numVerts, out IntPtr vertsNative);

                float[] rawVerts = new float[((int)numVerts) * 3];
                Marshal.Copy(vertsNative, rawVerts, 0, (int) numVerts * 3);
                return rawVerts;
            }
        }

        public int[] Indicies
        {
            get
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                APIWrapper.Terrain_GetIndicies(NativeInstance, out uint numInds, out IntPtr indiciesNative);

                int[] rawInds = new int[(int) numInds];
                Marshal.Copy(indiciesNative, rawInds, 0, (int) numInds);
                return rawInds;
            }
        }
    }
}
