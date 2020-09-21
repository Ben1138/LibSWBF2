// THis file should NEVER be included in exposed headers!
#pragma once
#include "Chunks/HeaderNames.h"
#include "Chunks/BaseChunk.h"
#include "Types/Vector4.h"
#include "Types/Matrix3x3.h"
#include "Types/List.h"
#include "Logging/Logger.h"
#include "Exceptions.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat3x3.hpp>
#include <fmt/core.h>
#include <fmt/format.h>

#include <unordered_map>


namespace LibSWBF2
{
	using Types::Vector2;
	using Types::Vector3;
	using Types::Vector4;
	using Types::Matrix3x3;
	using Types::List;
	using Types::String;

	Vector2 ToLib(const glm::vec2 vector);
	glm::vec3 ToGLM(const Vector3& vector);
	Vector3 ToLib(const glm::vec3 vector);
	glm::mat3 ToGLM(const Matrix3x3& matrix);
	Vector4 ToLib(const glm::quat& quaternion);

	// Convert an index buffer from Triangle Strip format to Triangle List format
	// optional: offset is added to each individual index.
	List<uint32_t> TriangleStripToTriangleList(List<uint16_t> indexBuffer, uint32_t offset=0);

	Vector4 MatrixToQuaternion(const Matrix3x3& matrix);

	std::string ToLower(String name);


	namespace Chunks::LVL::skel
	{
		struct skel;
	}

	namespace Wrappers
	{
		class MapsWrapper
		{
		public:
			std::unordered_map<std::string, size_t> TextureNameToIndex;
			std::unordered_map<std::string, size_t> ModelNameToIndex;
			std::unordered_map<std::string, size_t> WorldNameToIndex;
			std::unordered_map<std::string, size_t> TerrainNameToIndex;
			std::unordered_map<std::string, size_t> ScriptNameToIndex;
			std::unordered_map<std::string, size_t> LightNameToIndex;
			std::unordered_map<std::string, size_t> LocalizationNameToIndex;
			std::unordered_map<std::string, size_t> EntityClassTypeToIndex;
			std::unordered_map<std::string, Chunks::LVL::skel::skel*> SkeletonNameToSkel;
		};
	}
}

// adding custom fmt formatters
// see fmt documentation
template <>
struct fmt::formatter<LibSWBF2::Types::String> {
	constexpr auto parse(format_parse_context& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const LibSWBF2::Types::String& str, FormatContext& ctx)
	{
		return format_to(ctx.out(), "{}", str.Buffer());
	}
};

template <>
struct fmt::formatter<LibSWBF2::ChunkHeader> {
	constexpr auto parse(format_parse_context& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const LibSWBF2::ChunkHeader& header, FormatContext& ctx)
	{
		return format_to(ctx.out(), "{}", header.ToString().Buffer());
	}
};

template <>
struct fmt::formatter<LibSWBF2::Chunks::BaseChunk> {
	constexpr auto parse(format_parse_context& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const LibSWBF2::Chunks::BaseChunk& chunk, FormatContext& ctx)
	{
		return format_to(ctx.out(), "{}", chunk.GetHeader());
	}
};

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
//#define LOG(message, level) LibSWBF2::Logging::Logger::GetInstance()->Log(message, level, __LINE__, __FILENAME__);
#define LOG_INFO(...) LibSWBF2::Logging::Logger::GetInstance()->Log(fmt::format(__VA_ARGS__), LibSWBF2::ELogType::Info, __LINE__, __FILENAME__)
#define LOG_WARN(...) LibSWBF2::Logging::Logger::GetInstance()->Log(fmt::format(__VA_ARGS__), LibSWBF2::ELogType::Warning, __LINE__, __FILENAME__)
#define LOG_ERROR(...) LibSWBF2::Logging::Logger::GetInstance()->Log(fmt::format(__VA_ARGS__), LibSWBF2::ELogType::Error, __LINE__, __FILENAME__)

#define THROW(...) throw LibException(fmt::format("{} - IN {} {}", fmt::format(__VA_ARGS__), __LINE__, __FILENAME__))
#define LOCK(MutexLock) std::lock_guard<std::mutex> _SomeUnusualLockName(MutexLock)

#ifdef _MSC_VER
#define STRNLEN(...) strnlen_s(__VA_ARGS__)
#define MEMCPY(...) memcpy_s(__VA_ARGS__)
#else
#define STRNLEN(...) strnlen(__VA_ARGS__)
#define MEMCPY(x,y,z,w) memcpy(x,z,w)
#endif