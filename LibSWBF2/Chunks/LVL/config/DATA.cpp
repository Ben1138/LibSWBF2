#include "stdafx.h"
#include "DATA.h"
#include "FileReader.h"
#include "InternalHelpers.h"

//#include "float.DATA.h"
//#include "string.DATA.h"

//#include <iostream>
// /#define COUT(x) std::cout << x << std::endl

namespace LibSWBF2::Chunks::LVL::config
{
	void DATA_CONFIG::RefreshSize()
	{
		THROW("Not implemented!");
	}
	
	void DATA_CONFIG::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void DATA_CONFIG::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_NameHash = stream.ReadUInt32();
        m_NumElements = stream.ReadByte();

        m_ContentSize = m_Size >= 5 ? m_Size - 5 : 0;

        p_Content = new uint8_t[m_ContentSize];
        stream.ReadBytes(p_Content, m_ContentSize);

        BaseChunk::EnsureEnd(stream);
	}

	
	bool DATA_CONFIG::GetFloat(float_t& floatMember, uint32_t index)
	{
		if (m_NumElements > index)
		{
			floatMember = *(((float_t *) p_Content) + index);
			return true;
		}

		return false;
	}

	
	bool DATA_CONFIG::GetVec2(Vector2 &vec2Out)
	{
		if (m_NumElements >= 2)
		{
			float_t *floatsPtr = (float_t *) p_Content;
			vec2Out = Vector2(floatsPtr[0], floatsPtr[1]);
			return true;
		}

		return false;
	}


	bool DATA_CONFIG::GetVec3(Vector3 &vec3Out)
	{
		if (m_NumElements >= 3)
		{
			float_t *floatsPtr = (float_t *) p_Content;
			vec3Out = Vector3(floatsPtr[0], floatsPtr[1], floatsPtr[2]);
			return true;
		}

		return false;
	}


	bool DATA_CONFIG::GetVec4(Vector4 &vec4Out)
	{
		if (m_NumElements >= 4)
		{
			float_t *floatsPtr = (float_t *) p_Content;
			vec4Out = Vector4(floatsPtr[0], floatsPtr[1], floatsPtr[2], floatsPtr[3]);
			return true;
		}

		return false;
	}


	bool DATA_CONFIG::GetString(String &stringOut, uint32_t index)
	{
		if (m_NumElements > index)
		{
			//uint32_t *intPtr = (uint32_t *) p_Content;
			//uint32_t numStrings = *(intPtr++);

			//LOG_WARN("Num strings = {0}", numStrings);

			//if (numStrings <= index) return false;
			
			//List<uint32_t> stringLengths;
			//for(uint32_t i = 0; i < numStrings; i++)
			//{
			//	LOG_WARN("\tString length {0} = {1}", i, *(intPtr));
			//	stringLengths.Add(*(intPtr++));
			//}

			//size_t stringLength = stringLengths[0]; //*(intPtr + 1 + numStrings);

			uint32_t stringLength = *((uint32_t *) (p_Content + 4 * m_NumElements));

			//LOG_WARN("\tFinal string length = {0}", stringLength);

			char *strBuffer = new char[stringLength + 1]();
			memcpy(strBuffer, (char *) (p_Content + 4 * m_NumElements + 4), stringLength);
			
			//LOG_WARN("\tFinal string = {0}", strBuffer);


			stringOut = strBuffer;
			delete[] strBuffer; 
			
			return true;
		}

		stringOut = "";
		return true;
	}
	


	String DATA_CONFIG::ToString()
	{
		String rep = fmt::format("Name hash: 0x{0:x}\nNum elements: {1}\n", m_NameHash, m_NumElements).c_str();
		String str;

		if (IsFloatData())
		{	
			rep = rep + (m_NumElements > 0 ? "Floats: " : "");
			float_t *floatData = (float_t *) p_Content;
			for (uint8_t i = 0; i < m_NumElements; i++)
			{
				rep = rep + fmt::format("{}{} ",floatData[i], i == m_NumElements - 1 ? "" : ",").c_str();
			}
		}
		else if (GetString(str)) 
		{
			rep = rep + fmt::format("String(s): {}", str.Buffer()).c_str();
		}
		else 
		{
			for (int i = 0; i < 4 && i < m_ContentSize; i++)
			{
				rep = rep + fmt::format("\nByte {0}: 0x{1:x}", i, *(p_Content + i)).c_str();
			}

			rep = rep + fmt::format("\nContent size: {0}", m_ContentSize).c_str();	
		}

		return rep;
	}


	bool DATA_CONFIG::IsFloatData()
	{
		return m_ContentSize == m_NumElements * sizeof(float_t) + 4;
	}


	DATA_CONFIG::~DATA_CONFIG()
	{
		delete p_Content;
	}


	FNVHash DATA_CONFIG::PeekDATAHash(FileReader& stream)
	{
		stream.SkipBytes(8);
		FNVHash hash = stream.ReadUInt32();
		stream.SetPosition(stream.GetPosition() - 12);
		return hash;
	}


	void DATA_CONFIG::ReadDATAChild(FileReader& stream, GenericBaseChunk *parent,  DATA_CONFIG*& ptr)
	{	
		FNVHash hash = PeekDATAHash(stream);

		/*
		switch (hash)
		{	
			//none hashes: 
			case 2818330081: //NoRegisterStep
			case 3890809582: //CastShadow
			case 3532702267: //Static

			//vec1 hashes: 
			case 3117817292: //MaxLodDist
			case 1648733854: //MinLodDist
			case 3418349355: //BoundingRadius
			case 1350823129: //FadeInTime
			case 1376955374: //Lifetime
			case 2190941297: //Scale
			case 2039334020: //FadeOutTime
			case 126278723: //MaxDecals
			case 2945169614: //Enable
			case 3450034177: //GammaBrightness
			case 1231019624: //GammaContrast
			case 1961239565: //MaxGodraysInWorld
			case 3613443421: //MaxGodraysOnScreen
			case 881869609: //OffsetAngle
			case 3663861647: //MaxViewDistance
			case 1441012502: //ParticleSize
			case 4208725202: //Range
			case 846470194: //Velocity
			case 1416179775: //VelocityRange
			case 3281256433: //ParticleDensity
			case 571797374: //ParticleDensityRange
			case 2402720889: //CameraCrossVelocityScale
			case 474309834: //CameraAxialVelocityScale
			case 4066474868: //RotationRange
			case 2795258650: //OceanEnable
			case 2155550083: //LODDecimation
			case 316906227: //OscillationEnable
			case 564937055: //Rotation
			case 3585981250: //Height
			case 597743964: //Size
			case 1298175864: //FlareOutSize
			case 3830693448: //NumFlareOuts
			case 3986070605: //InitialFlareOutAlpha
			case 2896882860: //SpikeSize
			case 1361572173: //Type
			case 1217487547: //CastSpecular
			case 2229429542: //PS2BlendMode
			case 2002084458: //EditorGlobalDirIconSize
			case 3244099680: //EnableFadeAdjustWithZoom
			case 18426747: //FarSceneRange
			case 2982141257: //PropClusterEnable
			case 2444365001: //PropClusterFadeAdj
			case 818094846: //PropClusterDensity
			case 2907980824: //Angle
			case 2304294106: //Softness
			case 4277677579: //SoftnessParam
			case 348705738: //Offset
			case 1037190881: //TopRange
			case 2490894231: //BottomRange
			case 1543663727: //BottomDrop
			case 49525662: //Enabled
			case 72098048: //Bidirectional

			//vec2 hashes: 
			case 2254265480: //MaxParticles
			case 2188171614: //StartDelay
			case 2029794068: //BurstDelay
			case 868987928: //BurstCount
			case 3817694041: //Hue
			case 4121092745: //Saturation
			case 1113510858: //Value
			case 1569418667: //Alpha
			case 1473805686: //PositionX
			case 1490583305: //PositionY
			case 1440250448: //PositionZ
			case 2683528128: //PositionScale
			case 2554085736: //VelocityScale
			case 3114538364: //InheritVelocityFactor
			case 1089765596: //Red
			case 18738364: //Green
			case 2197550541: //Blue
			case 571214881: //AlphaMinMax
			case 9451243: //PatchDivisions
			case 1899658441: //Tile
			case 3685129408: //SpeckleTile
			case 3921220200: //SpeckleScrollSpeed
			case 1860699991: //SpeckleCoordShift
			case 2588884161: //LightAzimAndElev
			case 2407332482: //FresnelMinMax
			case 3912774700: //SpecularMaskTile
			case 3717688388: //SpecularMaskScrollSpeed
			case 3219525030: //TileUV
			case 1791371201: //OffsetUV
			case 3477711060: //FogRange
			case 3711978346: //Cone

			//vec3 hashes: 
			case 1028452225: //StartRotation
			case 374034744: //RotationVelocity
			case 2644449008: //Accelerate
			case 168239634: //DustVelocity
			case 1031692888: //Color
			case 2471448074: //Position
			case 2802900028: //Top
			case 1319594794: //Bottom
			case 1347755162: //NearSceneRange
			case 1015336758: //NearSplitScreenRange
			case 2448016011: //ReflectionFogColor
			case 479609067: //Ambient
			case 1764866243: //TopColor
			case 2225769661: //BottomColor

			//vec4 hashes: 
			case 407568404: //Move
			case 1291669624: //Reach
			case 1047008029: //WaterRingColor
			case 966571351: //WaterWakeColor
			case 3265425126: //MinDiffuseColor
			case 1881240500: //MaxDiffuseColor
			case 1152683974: //BorderDiffuseColor
			case 31763191: //SpecularColor
			case 2796713136: //SpeckleSpecularColor
			case 3126818435: //SpeckleAmbientColor
			case 1520804797: //RefractionColor
			case 2323766923: //ReflectionColor
			case 908877823: //UnderwaterColor
			case 3116016744: //SpikeColor
			case 37429198: //FogColor
			case 839159738: //rotationspeed

				DATA_FLOAT *floatChunk;
				parent -> ReadChildExplicit(parent, stream, floatChunk);
				ptr = floatChunk;
				break;

			//string
			case 4202188459: //BlendMode
			case 1013213428: //Texture
			case 145714212: //BumpTexture
			case 900218179: //MainTexture
			case 3679873338: //Light1
			case 3663095719: //Light2
			case 711820689: //Geometry
			case 2845502287: //EnvTexture
			case 52100733: //Region
				DATA_STRING *strChunk;
				parent -> ReadChildExplicit(parent, stream, strChunk);
				ptr = strChunk;		
				break;

			default:
				parent -> ReadChildExplicit(parent, stream, ptr);
				break;
		}
		*/
	}
}
