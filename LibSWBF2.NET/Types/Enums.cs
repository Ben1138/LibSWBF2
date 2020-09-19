using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibSWBF2.Enums
{

public enum LightType : uint
{
  Dir = 1,   
  Omni = 2, 
  Spot = 3, 
}


public enum  MaterialFlags : uint
{
	Normal = 1,
	Hardedged = 2,
	Transparent = 4,
	Glossmap = 8,
	Glow = 16,
	BumpMap = 32,
	Additive = 64,
	Specular = 128,
	EnvMap = 256,
	VertexLighting = 512,
	TiledNormalmap = 2048,
	Doublesided = 65536,

	Scrolling = 16777216,
	Energy = 33554432,
	Animated = 67108864,

	AttachedLight = 134217728,
}

}
