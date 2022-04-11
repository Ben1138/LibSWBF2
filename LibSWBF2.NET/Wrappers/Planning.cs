using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

using LibSWBF2.Utils;
using LibSWBF2.Types;
using LibSWBF2.Wrappers;



namespace LibSWBF2.Wrappers
{
    public sealed class Hub : NativeWrapper
    {
        public string Name 
        {
            get 
            {
                CheckValidity();
                return Marshal.PtrToStringAnsi(APIWrapper.Hub_GetFieldPtr(NativeInstance, 0, out _));
            }
        }

        public Vector3 Position
        {
            get 
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<Vector3>(APIWrapper.Hub_GetFieldPtr(NativeInstance, 1, out _));
            }   
        }

        public float Radius
        {
            get
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<float>(APIWrapper.Hub_GetFieldPtr(NativeInstance, 2, out _));
            }
        }

        public byte[] ConnectionIndices
        {
            get 
            {
                CheckValidity();
                return MemUtils.IntPtrToArray<byte>(APIWrapper.Hub_GetFieldPtr(NativeInstance, 3, out _), 8);
            }
        }

        public byte[] ConnectionsPerLayer
        {
            get
            {
                CheckValidity();
                return MemUtils.IntPtrToArray<byte>(APIWrapper.Hub_GetFieldPtr(NativeInstance, 4, out _), 5);
            }
        }

        public byte[] QuantizedWeights
        {
            get 
            {
                CheckValidity();
                IntPtr bufPtr = APIWrapper.Hub_GetFieldPtr(NativeInstance, 5, out int bufSize);
                return MemUtils.IntPtrToArray<byte>(bufPtr, bufSize);                
            }
        }


        string ConIndsToString()
        {
            string rep = "[";

            foreach (byte b in ConnectionIndices)
            {
                rep += b.ToString() + ",";
            }

            rep += "]";
            return rep;
        }

        string ConsPerLayerToString()
        {
            string rep = "[";

            foreach (byte b in ConnectionsPerLayer)
            {
                rep += b.ToString() + ",";
            }

            rep += "]";
            return rep;   
        }

        public override string ToString()
        {
            return String.Format("Name: {0}, Position: {1}, Radius: {2}, ConInds: {3}, ConsPerLayer: {4}, Length buffer: {5}", Name, Position.ToString(), Radius, ConIndsToString(), ConsPerLayerToString(), QuantizedWeights.Length);
        }

        public Hub(){}
    }




    public sealed class Connection : NativeWrapper
    {
        public string Name 
        {
            get 
            {
                CheckValidity();
                return Marshal.PtrToStringAnsi(APIWrapper.Connection_GetFieldPtr(NativeInstance, 0));
            }
        }

        public byte Start
        {
            get 
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<byte>(APIWrapper.Connection_GetFieldPtr(NativeInstance, 1));
            }   
        }

        public byte End
        {
            get
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<byte>(APIWrapper.Connection_GetFieldPtr(NativeInstance, 2));
            }
        }

        public uint Flag1
        {
            get 
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<uint>(APIWrapper.Connection_GetFieldPtr(NativeInstance, 3));
            }
        }

        public uint Flag2
        {
            get
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<uint>(APIWrapper.Connection_GetFieldPtr(NativeInstance, 4));
            }
        }

        public override string ToString()
        {
            return String.Format("Name: {0}, StartIndex: {1}, EndIndex: {2}, Flag1: {3}, Flag2: {4}", Name, Start, End, Flag1, Flag2);
        }

        public Connection(){}
    }






    public sealed class PlanSet : NativeWrapper
    {
        public Hub[] GetHubs()
        {
            CheckValidity();
            APIWrapper.PlanSet_GetChildWrappers(NativeInstance, 0, out IntPtr listPtr, out int listSize, out int elSize);
            return MemUtils.IntPtrToWrapperArray<Hub>(listPtr, listSize, elSize);        
        }

        public Connection[] GetConnections()
        {
            CheckValidity();
            APIWrapper.PlanSet_GetChildWrappers(NativeInstance, 1, out IntPtr listPtr, out int listSize, out int elSize);        
            return MemUtils.IntPtrToWrapperArray<Connection>(listPtr, listSize, elSize);        
        }


        public List<Tuple<float, Connection>> GetBranchWeights(string StartHubName, string DestHubName, int Layer)
        {
            List<Tuple<float, Connection>> WeightConPairs = new List<Tuple<float, Connection>>();

            Hub[] hubs = GetHubs();
            Connection[] cons = GetConnections();

            int startIndex = -1;
            int destIndex = -1;

            for (int i = 0; i < hubs.Length; i++)
            {
                if (startIndex < 0 && hubs[i].Name == StartHubName)
                {
                    startIndex = i;
                }

                if (destIndex < 0 && hubs[i].Name == DestHubName)
                {
                    destIndex = i;
                }
            }

            if (startIndex < 0 || destIndex < 0)
            {
                return null;
            }

            Hub StartHub = hubs[startIndex];

            byte[] ConInds = StartHub.ConnectionIndices;
            byte[] ConsPerLayer = StartHub.ConnectionsPerLayer;
            byte[] Weights = StartHub.QuantizedWeights;

            int WeightsOffset = destIndex;
            int LayerWeightsLength = 0;
            for (int j = 0; j < 5; j++)
            {
                if (Layer == j)
                {
                    LayerWeightsLength = hubs.Length * ConsPerLayer[j];
                    break;
                }
                else 
                {
                    WeightsOffset += (ConsPerLayer[j] * hubs.Length);
                }
            }

            for (int k = WeightsOffset; k < WeightsOffset + LayerWeightsLength; k+=hubs.Length)
            {
                WeightConPairs.Add(Tuple.Create(((Weights[k] >> 3) / 31.0f), cons[ConInds[Weights[k] & 0x3]]));
            }

            return WeightConPairs;
        }


        public PlanSet(){}
    }
}
