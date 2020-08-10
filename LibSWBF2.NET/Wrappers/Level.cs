using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LibSWBF2.Wrappers
{
    public class Level
    {
        private IntPtr NativeLevel;

        // Make constructor private, so instantiation is only possible via FromFile
        private Level()
        {

        }

        ~Level()
        {
            APIWrapper.Level_Destroy(NativeLevel);
        }

        public static Level FromFile(string path)
        {
            IntPtr native = APIWrapper.Level_FromFile(path);
            if (native == null)
            {
                return null;
            }

            Level level = new Level();
            level.NativeLevel = native;
            return level;
        }

        public bool IsWorldLevel
        {
            get { return APIWrapper.Level_IsWorldLevel(NativeLevel); }
        }

        public Model[] GetModels()
        {
            APIWrapper.Level_GetModels(NativeLevel, out IntPtr modelArr, out uint modelCount);
            IntPtr[] modelPtrs= new IntPtr[modelCount];
            Marshal.Copy(modelArr, modelPtrs, 0, (int)modelCount);

            Model[] models = new Model[modelCount];
            for (int i = 0; i < modelCount; i++)
            {
                models[i] = new Model(modelPtrs[i]);
            }

            return models;
        }

        public Model GetModel(string modelName)
        {
            IntPtr modelPtr = APIWrapper.Level_GetModel(NativeLevel, modelName);
            if (modelPtr == null)
            {
                return null;
            }

            return new Model(modelPtr);
        }
    }
}
