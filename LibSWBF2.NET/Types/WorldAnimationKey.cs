using System;
using System.Runtime.InteropServices;

using LibSWBF2.Types;
using LibSWBF2.Enums;


namespace LibSWBF2.Types
{
    [StructLayout(LayoutKind.Sequential, Pack=1)]
    public struct WorldAnimationKey
    {
        public float Time;
        public Vector3 Value; // For rotations this is in radians, in .ANM files they are in degrees 
        public EWorldAnimKeyTransitionType TransitionType;
        public Vector3 EaseOut;
        public Vector3 EaseIn;

        public override String ToString()
        {
            return String.Format(
                "Time: {0}, Value: {1}, TransitionType: {2}, EaseOut: {3}, EaseIn: {4}",
                Time, Value.ToString(), TransitionType.ToString(), EaseOut.ToString(), EaseIn.ToString()
            );
        }
    }
}