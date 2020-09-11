﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;
using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{
    public class Terrain : NativeWrapper
    {
        internal Terrain(IntPtr terrainPtr) : base(terrainPtr)
        {

        }

        public Terrain() : base(IntPtr.Zero){}


        public List<string> GetTextureNames()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetTexNames(NativeInstance, out uint numTextures, out IntPtr stringsPtr);
            return MemUtils.ptrToStringList(stringsPtr, (int) numTextures);   
        }

        /*
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
        */

        public void GetHeightMap(out uint dim, out uint dimScale, out float heightScale, out float[] data) 
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetHeights(NativeInstance, out dim, out dimScale, out heightScale, out IntPtr heightsNative);

            int dataLength = (int) (dim * dim);

            float[] heights = new float[dataLength];
            Marshal.Copy(heightsNative, heights, 0, dataLength);
            data = heights;
        }

        /*
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
        */

        public void GetBlendMap(out uint dim, out uint numLayers, out byte[] data)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Terrain_GetBlendMap(NativeInstance, out dim, out numLayers, out IntPtr bytesNative);

            int dataLength = (int) (dim * dim * numLayers);

            byte[] byteArray = new byte[dataLength];
            Marshal.Copy(bytesNative, byteArray, 0, dataLength);
            data = byteArray;  
        } 
    }
}
