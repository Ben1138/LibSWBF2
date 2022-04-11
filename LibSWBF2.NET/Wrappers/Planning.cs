using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Wrappers
{
    public sealed class Hub : NativeWrapper
    {
        public Name 
        {
            get 
            {
                CheckValidity();
                return Marshal
            }
        }

        public Vector3 Position
        {
            get 
            {
                CheckValidity();
                return //
            }   
        }

        public float Radius
        {
            get
            {
                CheckValidity();
                return //
            }
        }

        public byte[] ConnectionIndices
        {
            get 
            {
                CheckValidity();
                return //
            }
        }

        public byte[] ConnectionsPerLayer
        {
            get
            {
                CheckValidity();

            }
        }

        public byte[] QuantizedData
        {
            get 
            {
                CheckValidity();
            }
        }

        Hub(){}
    }




    public sealed class Connection : NativeWrapper
    {
        public Name 
        {
            get 
            {
                CheckValidity();
                return Marshal
            }
        }

        public byte Start
        {
            get 
            {
                CheckValidity();
                return //
            }   
        }

        public byte End
        {
            get
            {
                CheckValidity();
                return //
            }
        }

        public uint Flag1
        {
            get 
            {
                CheckValidity();
                return //
            }
        }

        public uint Flag2
        {
            get
            {
                CheckValidity();

            }
        }

        Connection(){}
    }






    public sealed class PlanSet : NativeWrapper
    {
        public Hub[] GetHubs()
        {

        }

        public Connection[] GetConnections()
        {

        }

        PlanSet(){}
    }
}
