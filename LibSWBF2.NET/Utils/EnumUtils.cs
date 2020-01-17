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
            if ((flags & (uint) MaterialFlags.Normal) != 0)
            {
                result += "Normal, ";
            }
            if ((flags & (uint) MaterialFlags.Hardedged) != 0)
            {
                result += "Hardedged, ";
            }
            if ((flags & (uint) MaterialFlags.Transparent) != 0)
            {
                result += "Transparent, ";
            }
            if ((flags & (uint) MaterialFlags.Glossmap) != 0)
            {
                result += "Glossmap, ";
            }
            if ((flags & (uint) MaterialFlags.Glow) != 0)
            {
                result += "Glow, ";
            }
            if ((flags & (uint) MaterialFlags.BumpMap) != 0)
            {
                result += "BumpMap, ";
            }
            if ((flags & (uint) MaterialFlags.Additive) != 0)
            {
                result += "Additive, ";
            }
            if ((flags & (uint) MaterialFlags.Specular) != 0)
            {
                result += "Specular, ";
            }
            if ((flags & (uint) MaterialFlags.EnvMap) != 0)
            {
                result += "EnvMap, ";
            }
            if ((flags & (uint) MaterialFlags.VertexLighting) != 0)
            {
                result += "VertexLighting, ";
            }
            if ((flags & (uint) MaterialFlags.TiledNormalmap) != 0)
            {
                result += "TiledNormalmap, ";
            }
            if ((flags & (uint) MaterialFlags.Doublesided) != 0)
            {
                result += "Doublesided, ";
            }
            if ((flags & (uint) MaterialFlags.Scrolling) != 0)
            {
                result += "Scrolling, ";
            }
            if ((flags & (uint) MaterialFlags.Energy) != 0)
            {
                result += "Energy, ";
            }
            if ((flags & (uint) MaterialFlags.Animated) != 0)
            {
                result += "Animated, ";
            }
            if ((flags & (uint) MaterialFlags.AttachedLight) != 0)
            {
                result += "AttachedLight, ";
            }
            
            return (result + "]").Replace(", ]","]");
        }
    }
}
