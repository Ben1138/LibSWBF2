using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Runtime.InteropServices;
using System.Security;
using System.Runtime.InteropServices.WindowsRuntime;

using LibSWBF2.Enums;


namespace LibSWBF2.Utils
{
    public static class EnumUtils {

        public static string MaterialFlagsToString(uint flags)
        {
            string result = "[";
            if ((flags & (uint) EMaterialFlags.Normal) != 0)
            {
                result += "Normal, ";
            }
            if ((flags & (uint) EMaterialFlags.Hardedged) != 0)
            {
                result += "Hardedged, ";
            }
            if ((flags & (uint) EMaterialFlags.Transparent) != 0)
            {
                result += "Transparent, ";
            }
            if ((flags & (uint) EMaterialFlags.Glossmap) != 0)
            {
                result += "Glossmap, ";
            }
            if ((flags & (uint) EMaterialFlags.Glow) != 0)
            {
                result += "Glow, ";
            }
            if ((flags & (uint) EMaterialFlags.BumpMap) != 0)
            {
                result += "BumpMap, ";
            }
            if ((flags & (uint) EMaterialFlags.Additive) != 0)
            {
                result += "Additive, ";
            }
            if ((flags & (uint) EMaterialFlags.Specular) != 0)
            {
                result += "Specular, ";
            }
            if ((flags & (uint) EMaterialFlags.EnvMap) != 0)
            {
                result += "EnvMap, ";
            }
            if ((flags & (uint) EMaterialFlags.VertexLighting) != 0)
            {
                result += "VertexLighting, ";
            }
            if ((flags & (uint) EMaterialFlags.TiledNormalmap) != 0)
            {
                result += "TiledNormalmap, ";
            }
            if ((flags & (uint) EMaterialFlags.Doublesided) != 0)
            {
                result += "Doublesided, ";
            }
            if ((flags & (uint) EMaterialFlags.Scrolling) != 0)
            {
                result += "Scrolling, ";
            }
            if ((flags & (uint) EMaterialFlags.Energy) != 0)
            {
                result += "Energy, ";
            }
            if ((flags & (uint) EMaterialFlags.Animated) != 0)
            {
                result += "Animated, ";
            }
            if ((flags & (uint) EMaterialFlags.AttachedLight) != 0)
            {
                result += "AttachedLight, ";
            }
            
            return (result + "]").Replace(", ]","]");
        }
    }
}
