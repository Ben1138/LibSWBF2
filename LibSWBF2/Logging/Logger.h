#pragma once
#include "LoggerEntry.h"
#include "FileWriter.h"
#include "Types/LibString.h"
#include "Chunks/HeaderNames.h"
#include "Chunks/BaseChunk.h"
#include <memory>
#include <fmt/core.h>
#include <fmt/format.h>


namespace LibSWBF2::Logging
{
	typedef void(*LogCallback)(const LoggerEntry*);

	// Singleton
	// TODO: Make static class instead of singleton
	class Logger
	{
	public:
		Logger();	// do not call anywhere else!
		~Logger();

		const String LOG_FILE = "LibSWBF2.log";
		static std::unique_ptr<Logger>& GetInstance();

		LIBSWBF2_API static void SetLogCallback(const LogCallback Callback);
		LIBSWBF2_API static void SetLogfileLevel(const ELogType LogfileLevel);
		void Log(const std::string &message, const ELogType level, const unsigned long line, const char* file);

	private:
		static std::unique_ptr<Logger> m_Instance;
		LogCallback m_OnLogCallback = nullptr;
		FileWriter m_Writer;
		ELogType m_LogfileLevel = ELogType::Warning;
	};
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
#define LOG_INFO(...) LibSWBF2::Logging::Logger::GetInstance()->Log(fmt::format(__VA_ARGS__), ELogType::Info, __LINE__, __FILENAME__);
#define LOG_WARN(...) LibSWBF2::Logging::Logger::GetInstance()->Log(fmt::format(__VA_ARGS__), ELogType::Warning, __LINE__, __FILENAME__);
#define LOG_ERROR(...) LibSWBF2::Logging::Logger::GetInstance()->Log(fmt::format(__VA_ARGS__), ELogType::Error, __LINE__, __FILENAME__);