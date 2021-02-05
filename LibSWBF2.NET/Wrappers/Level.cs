using LibSWBF2.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

using LibSWBF2.Utils;
using LibSWBF2.Types;
using LibSWBF2.Enums;



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
            //Delete();
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

        internal static Level FromNative(IntPtr native)
        {
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


        public string name
        {
            get { return Marshal.PtrToStringAnsi(APIWrapper.Level_GetName(NativeInstance)); }
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
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Level_GetModels(NativeInstance, out IntPtr modelArr, out uint modelCount, out int inc);
            Model[] models = MemUtils.IntPtrToWrapperArray<Model>(modelArr, (int) modelCount, inc);

            for (int i = 0; i < modelCount; i++)
            {
                Children.Add(new WeakReference<NativeWrapper>(models[i]));
            }

            return models;
        }


        public EntityClass[] GetEntityClasses()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Level_GetEntityClasses(NativeInstance, out IntPtr classArr, out int classCount, out int inc);
            EntityClass[] classes = MemUtils.IntPtrToWrapperArray<EntityClass>(classArr, classCount, inc);
            return classes;
        }


        public World[] GetWorlds()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Level_GetWorlds(NativeInstance, out IntPtr worldArr, out uint worldCount);
            return MemUtils.IntPtrToWrapperArray<World>(worldArr, (int) worldCount);
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

        public Texture GetTexture(string name)
        {
            IntPtr texPtr = APIWrapper.Level_GetTexture(NativeInstance, name);
            if (texPtr == null)
            {
                return null;
            }
            return new Texture(texPtr);
        }

        public AnimationBank GetAnimationBank(string setName)
        {
            IntPtr SetPtr = APIWrapper.Level_GetAnimationBank(NativeInstance, setName);
            if (SetPtr == null)
            {
                return null;
            }

            AnimationBank animSet = new AnimationBank(SetPtr);
            return animSet;
        }

        public EntityClass GetEntityClass(string name)
        {
            IntPtr ptr = APIWrapper.Level_GetEntityClass(NativeInstance, name);
            if (ptr == IntPtr.Zero)
            {
                return null;
            }

            EntityClass ec = new EntityClass(ptr);
            return ec;   
        }


        public Config GetConfig(uint hash, ConfigType cfgType)
        {
            IntPtr ptr = APIWrapper.Level_GetConfig(NativeInstance, (uint) cfgType, hash);
            if (ptr == IntPtr.Zero)
            {
                return null;
            }
            return new Config(ptr);            
        }

        public Config GetConfig(string name, ConfigType cfgType)
        {
            return GetConfig(HashUtils.GetFNV(name), cfgType);
        }

        public List<Config> GetConfigs(ConfigType cfgType)
        {
            IntPtr ptr = APIWrapper.Level_GetConfigs(NativeInstance, (uint) cfgType, out int count);
            if (ptr == IntPtr.Zero)
            {
                return new List<Config>();
            }
            return new List<Config>(MemUtils.IntPtrToWrapperArray<Config>(ptr, count));
        }
    }
}
