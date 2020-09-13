using LibSWBF2.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Utils;


namespace LibSWBF2.Wrappers
{
    public class Level : NativeWrapper
    {
        private HashSet<WeakReference<NativeWrapper>> Children;

        // Make constructor private, so instantiation is only possible via FromFile
        private Level() : base(IntPtr.Zero)
        {
            Children = new HashSet<WeakReference<NativeWrapper>>();
        }

        ~Level()
        {
            Delete();
        }

        /// <summary>
        /// Don't use this method unless you know exactly what you're doing!
        /// This will delete the underlying native Level instance and invalidate this
        /// Level wrapper instance, as well as all its children of whom references might
        /// still float around somewhere.
        /// </summary>
        public void Delete()
        {
            if (!IsValid())
            {
                Logger.Log("Cannot delete invalid Level!", ELogType.Warning);
                return;
            }

            APIWrapper.Level_Destroy(NativeInstance);
            NativeInstance = IntPtr.Zero;

            foreach (WeakReference<NativeWrapper> childRef in Children)
            {
                if (childRef.TryGetTarget(out NativeWrapper child))
                {
                    child.Invalidate();
                }
            }
            Children.Clear();
        }

        public static Level FromFile(string path)
        {
            IntPtr native = APIWrapper.Level_FromFile(path);
            if (native == null)
            {
                return null;
            }

            Level level = new Level();
            level.NativeInstance = native;
            return level;
        }

        public bool IsWorldLevel
        {
            get { return APIWrapper.Level_IsWorldLevel(NativeInstance); }
        }

        
        public Terrain[] GetTerrains()
        {   
            APIWrapper.Level_GetTerrains(NativeInstance, out IntPtr terrainsArr, out uint numTerrains);
            Terrain[] terrains = MemUtils.IntPtrToWrapperArray<Terrain>(terrainsArr, (int) numTerrains);

            for (int i = 0; i < numTerrains; i++)
            {
                Children.Add(new WeakReference<NativeWrapper>(terrains[i]));
            }

            return terrains;
        }


        public Model[] GetModels()
        {
            APIWrapper.Level_GetModels(NativeInstance, out IntPtr modelArr, out uint modelCount);
            Model[] models = MemUtils.IntPtrToWrapperArray<Model>(modelArr, (int) modelCount);

            for (int i = 0; i < modelCount; i++)
            {
                Children.Add(new WeakReference<NativeWrapper>(models[i]));
            }

            return models;
        }


        public Light[] GetLights()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Level_GetLights(NativeInstance, out IntPtr LightArr, out uint LightCount);
            return MemUtils.IntPtrToWrapperArray<Light>(LightArr, (int) LightCount);
        }    


        public World[] GetWorlds()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Level_GetWorlds(NativeInstance, out IntPtr worldArr, out uint worldCount);
            return MemUtils.ptrsToObjects<World>(worldArr, (int) worldCount);
        }


        public Model GetModel(string modelName)
        {
            IntPtr modelPtr = APIWrapper.Level_GetModel(NativeInstance, modelName);
            if (modelPtr == null)
            {
                return null;
            }

            Model model = new Model(modelPtr);
            Children.Add(new WeakReference<NativeWrapper>(model));
            return model;
        }


        public Terrain[] GetTerrains()
        {   
            APIWrapper.Level_GetTerrains(NativeInstance, out IntPtr terrainsArr, out uint numTerrains);
            Terrain[] terrains = MemUtils.IntPtrToWrapperArray<Terrain>(terrainsArr, (int) numTerrains);

            for (int i = 0; i < numTerrains; i++)
            {
                Children.Add(new WeakReference<NativeWrapper>(terrains[i]));
            }

            return terrains;
        }


        public bool GetTexture(string name, out int width, out int height, out byte[] texBytes)
        {
            texBytes = null;
            bool result = APIWrapper.Level_GetTextureData(NativeInstance, name, out IntPtr bytesRaw, out width, out height);
            if (result)
            {
                texBytes = new byte[width * height * 4];
                Marshal.Copy(bytesRaw, texBytes, 0, width * height * 4);
            }
            Marshal.FreeHGlobal(bytesRaw); 
            return result;
        }
    }
}
