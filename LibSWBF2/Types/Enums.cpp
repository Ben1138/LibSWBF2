#include "stdafx.h"
#include "Enums.h"
#include <string>
#include <fmt/format.h>

namespace LibSWBF2
{
	Types::String LogTypeToString(ELogType type)
	{
		switch (type)
		{
			case ELogType::Info:
				return "Info";
			case ELogType::Warning:
				return "Warning";
			case ELogType::Error:
				return "Error";
		}
		return fmt::format("Unknown Log Type: {}", type).c_str();
	}

	Types::String TopologyToString(ETopology topology)
	{
		switch (topology)
		{
			case ETopology::PointList:
				return "Point List";
			case ETopology::LineList:
				return "Line List";
			case ETopology::LineStrip:
				return "Line Strip";
			case ETopology::TriangleList:
				return "Triangle List";
			case ETopology::TriangleStrip:
				return "Triangle Strip";
			case ETopology::TriangleFan:
				return "Triangle Strip";
		}
		return fmt::format("Unknown Topology: {}", topology).c_str();
	}

	Types::String MaterialFlagsToString(EMaterialFlags flags)
	{
		std::string result = "[";
		if ((flags & EMaterialFlags::Normal) != 0)
		{
			result += "Normal, ";
		}
		if ((flags & EMaterialFlags::Hardedged) != 0)
		{
			result += "Hardedged, ";
		}
		if ((flags & EMaterialFlags::Transparent) != 0)
		{
			result += "Transparent, ";
		}
		if ((flags & EMaterialFlags::Glossmap) != 0)
		{
			result += "Glossmap, ";
		}
		if ((flags & EMaterialFlags::Glow) != 0)
		{
			result += "Glow, ";
		}
		if ((flags & EMaterialFlags::BumpMap) != 0)
		{
			result += "BumpMap, ";
		}
		if ((flags & EMaterialFlags::Additive) != 0)
		{
			result += "Additive, ";
		}
		if ((flags & EMaterialFlags::Specular) != 0)
		{
			result += "Specular, ";
		}
		if ((flags & EMaterialFlags::EnvMap) != 0)
		{
			result += "EnvMap, ";
		}
		if ((flags & EMaterialFlags::VertexLighting) != 0)
		{
			result += "VertexLighting, ";
		}
		if ((flags & EMaterialFlags::TiledNormalmap) != 0)
		{
			result += "TiledNormalmap, ";
		}
		if ((flags & EMaterialFlags::Doublesided) != 0)
		{
			result += "Doublesided, ";
		}
		if ((flags & EMaterialFlags::Scrolling) != 0)
		{
			result += "Scrolling, ";
		}
		if ((flags & EMaterialFlags::Energy) != 0)
		{
			result += "Energy, ";
		}
		if ((flags & EMaterialFlags::Animated) != 0)
		{
			result += "Animated, ";
		}
		if ((flags & EMaterialFlags::AttachedLight) != 0)
		{
			result += "AttachedLight, ";
		}

		result.resize(result.size() - 2);
		result += "]";
		return result.c_str();
	}

	Types::String EVBUFFlagsToString(EVBUFFlags flags)
	{
		std::string result = "[";
		if ((flags & EVBUFFlags::Position) != 0)
		{
			result += "Position, ";
		}
		if ((flags & EVBUFFlags::Unknown1) != 0)
		{
			result += "Unknown 1, ";
		}
		if ((flags & EVBUFFlags::BlendWeight) != 0)
		{
			result += "BlendWeight, ";
		}
		if ((flags & EVBUFFlags::Normal) != 0)
		{
			result += "Normal, ";
		}
		if ((flags & EVBUFFlags::Tangents) != 0)
		{
			result += "Tangents, ";
		}
		if ((flags & EVBUFFlags::Color) != 0)
		{
			result += "Color, ";
		}
		if ((flags & EVBUFFlags::StaticLighting) != 0)
		{
			result += "StaticLighting, ";
		}
		if ((flags & EVBUFFlags::TexCoord) != 0)
		{
			result += "TexCoord, ";
		}
		if ((flags & EVBUFFlags::PositionCompressed) != 0)
		{
			result += "PositionCompressed, ";
		}
		if ((flags & EVBUFFlags::BlendWeightCompressed) != 0)
		{
			result += "BlendInfoCompressed, ";
		}
		if ((flags & EVBUFFlags::NormalCompressed) != 0)
		{
			result += "NormalCompressed, ";
		}
		if ((flags & EVBUFFlags::TexCoordCompressed) != 0)
		{
			result += "TexCoordCompressed, ";
		}
		result.resize(result.size() - 2);
		result += "]";
		return result.c_str();
	}

	Types::String LIBSWBF2_API TerrainBufferTypeToString(ETerrainBufferType type)
	{
		switch (type)
		{
			case ETerrainBufferType::Geometry:
				return "Geometry";
			case ETerrainBufferType::Texture:
				return "Texture";
			case ETerrainBufferType::TextureExtra:
				return "TextureExtra";
			default:
				return fmt::format("Unknown ETerrainBufferType: {}", (int)type).c_str();
		}
	}
	
	EMaterialFlags operator &(EMaterialFlags lhs, EMaterialFlags rhs)
	{
		return static_cast<EMaterialFlags> (
			static_cast<std::underlying_type<EMaterialFlags>::type>(lhs) &
			static_cast<std::underlying_type<EMaterialFlags>::type>(rhs)
			);
	}

	bool operator ==(EMaterialFlags lhs, std::underlying_type<EMaterialFlags>::type rhs)
	{
		return static_cast<std::underlying_type<EMaterialFlags>::type>(lhs) == rhs;
	}

	bool operator !=(EMaterialFlags lhs, std::underlying_type<EMaterialFlags>::type rhs)
	{
		return static_cast<std::underlying_type<EMaterialFlags>::type>(lhs) != rhs;
	}

	EVBUFFlags operator &(EVBUFFlags lhs, EVBUFFlags rhs)
	{
		return static_cast<EVBUFFlags> (
			static_cast<std::underlying_type<EVBUFFlags>::type>(lhs) &
			static_cast<std::underlying_type<EVBUFFlags>::type>(rhs)
			);
	}

	bool operator ==(EVBUFFlags lhs, std::underlying_type<EVBUFFlags>::type rhs)
	{
		return static_cast<std::underlying_type<EVBUFFlags>::type>(lhs) == rhs;
	}

	bool operator !=(EVBUFFlags lhs, std::underlying_type<EVBUFFlags>::type rhs)
	{
		return static_cast<std::underlying_type<EVBUFFlags>::type>(lhs) != rhs;
	}
}
