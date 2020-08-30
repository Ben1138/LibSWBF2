﻿using LibSWBF2.Logging;
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
                else
                {
                    Children.Remove(childRef);
                }
            }
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

        public Model[] GetModels()
        {
            APIWrapper.Level_GetModels(NativeInstance, out IntPtr modelArr, out uint modelCount);
            IntPtr[] modelPtrs= new IntPtr[modelCount];
            Marshal.Copy(modelArr, modelPtrs, 0, (int)modelCount);

            Model[] models = new Model[modelCount];
            for (int i = 0; i < modelCount; i++)
            {
                models[i] = new Model(modelPtrs[i]);
                Children.Add(new WeakReference<NativeWrapper>(models[i]));
            }

            return models;
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

        public Terrain GetTerrain()
        {   
            IntPtr native = APIWrapper.Level_GetTerrain(NativeInstance);
            if (native == null)
            {
                return null;
            }

            Terrain ter = new Terrain(native);
            return ter;
        }

        public bool GetTexture(string name, out byte[] texBytes, out int width, out int height)
        {
            texBytes = null;
            bool result = APIWrapper.Level_GetTextureData(NativeInstance, name, out IntPtr bytesRaw, out width, out height);
            if (result)
            {
                texBytes = new byte[width * height * 4];
                Marshal.Copy(bytesRaw, texBytes, 0, width * height * 4);
            }
            return result;
        }
    }
}
