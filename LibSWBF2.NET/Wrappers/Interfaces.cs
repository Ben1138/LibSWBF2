using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibSWBF2.Wrappers
{
    public interface ISWBFProperties
    {
        bool GetProperty(string propName, out string propValue);
        bool GetProperty(uint hashedPropName, out string propValue);
        bool GetProperty(string propName, out string[] propValues);
        bool GetProperty(uint hashedPropName, out string[] propValues);
        void GetOverriddenProperties(out uint[] properties, out string[] values);
    }
}
