using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace LibSWBF2.Enums
{
    public enum ELoadStatus : byte
    {
        Uninitialized = 0,
		Loading = 1,
		Loaded = 2,
		Failed = 3
    }

    public enum EConfigType : uint
    {
        Lighting = 0x7468676c,
        Effect = 0x5f5f7866,
        Boundary = 0x5f646e62,
        Skydome = 0x5f796b73,
        Path = 0x68746170,
        Combo = 0x626d6f63,
        Music = 0x5f73756d,
        FoleyFX = 0x5f786666,
        Sound = 0x5f646e73,
        TriggerSoundRegion = 0x5f727374,
    }

    public enum ETopology : int
    {
        PointList = 1,
        LineList = 2,
        LineStrip = 3,
        TriangleList = 4,
        TriangleStrip = 5,
        TriangleFan = 6,
    }

    public enum ELightType : uint
    {
        Dir = 1,   
        Omni = 2, 
        Spot = 3, 
    }

    [Flags]
    public enum EMaterialFlags : uint
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

    public enum ETextureFormat : uint
    {
        D3DFMT_UNKNOWN = 0,

        D3DFMT_R8G8B8 = 20,
        D3DFMT_A8R8G8B8 = 21,
        D3DFMT_X8R8G8B8 = 22,
        D3DFMT_R5G6B5 = 23,
        D3DFMT_X1R5G5B5 = 24,
        D3DFMT_A1R5G5B5 = 25,
        D3DFMT_A4R4G4B4 = 26,
        D3DFMT_R3G3B2 = 27,
        D3DFMT_A8 = 28,
        D3DFMT_A8R3G3B2 = 29,
        D3DFMT_X4R4G4B4 = 30,
        D3DFMT_A2B10G10R10 = 31,
        D3DFMT_A8B8G8R8 = 32,
        D3DFMT_X8B8G8R8 = 33,
        D3DFMT_G16R16 = 34,
        D3DFMT_A2R10G10B10 = 35,
        D3DFMT_A16B16G16R16 = 36,

        D3DFMT_A8P8 = 40,
        D3DFMT_P8 = 41,

        D3DFMT_L8 = 50,
        D3DFMT_A8L8 = 51,
        D3DFMT_A4L4 = 52,

        D3DFMT_V8U8 = 60,
        D3DFMT_L6V5U5 = 61,
        D3DFMT_X8L8V8U8 = 62,
        D3DFMT_Q8W8V8U8 = 63,
        D3DFMT_V16U16 = 64,
        D3DFMT_A2W10V10U10 = 67,

        D3DFMT_UYVY = 0x59565955, 
        D3DFMT_R8G8_B8G8 = 0x47424752,
        D3DFMT_YUY2 = 0x32595559,
        D3DFMT_G8R8_G8B8 = 0x42475247,
        D3DFMT_DXT1 = 0x31545844,
        D3DFMT_DXT2 = 0x32545844,
        D3DFMT_DXT3 = 0x33545844,
        D3DFMT_DXT4 = 0x34545844,
        D3DFMT_DXT5 = 0x35545844,       

        D3DFMT_D16_LOCKABLE = 70,
        D3DFMT_D32 = 71,
        D3DFMT_D15S1 = 73,
        D3DFMT_D24S8 = 75,
        D3DFMT_D24X8 = 77,
        D3DFMT_D24X4S4 = 79,
        D3DFMT_D16 = 80,

        D3DFMT_D32F_LOCKABLE = 82,
        D3DFMT_D24FS8 = 83,
    }

    public enum EEntityClassType
    {
        GameObjectClass,
		OrdnanceClass,
		WeaponClass,
		ExplosionClass
    };

    [Flags]
    public enum ECollisionMaskFlags : uint
    {
        All = 0xffffffff,
		Ordnance = 1,
        Vehicle = 2,
        Building = 4,
        Terrain = 8,
        Soldier = 16,
        Flag = 32,
	};

    public enum ECollisionPrimitiveType : uint
    {
        Sphere = 1,
		Cylinder = 2,
		Empty = 3,
		Cube = 4,
	};

    public enum EWorldAnimKeyTransitionType : byte
    {
        Pop = 0,
        Linear = 1,
        Spline = 2,
    };

    public enum ESoundFormat : uint
    {
        PCM8 = 1,
        PCM16 = 2,
        VAG = 3,
        XADPCM = 4,
        IMAADPCM = 5
    };

    [Flags]
    public enum EArcFilterFlags : uint
    {
        Soldier = 1,
        Small = 2,
        Medium = 4,
        Hover = 8,
        Large = 16,
        Huge = 32,
    };

    [Flags]
    public enum EArcAttributeFlags : uint
    {
        OneWay = 1,
        Jump = 2,
        JetJump = 4,
    };
}
