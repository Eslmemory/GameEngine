#pragma once

#include "GameEngine/Core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace GE {

	class GE_API Log {
	public:
		
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		static void Init();

	public:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	#define GE_CORE_TRACE(...)		::GE::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define GE_CORE_INFO(...)		::GE::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define GE_CORE_DEBUG(...)		::GE::Log::GetCoreLogger()->debug(__VA_ARGS__)
	#define GE_CORE_WARN(...)		::GE::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define GE_CORE_ERROR(...)		::GE::Log::GetCoreLogger()->error(__VA_ARGS__)

	#define GE_TRACE(...)			::GE::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define GE_INFO(...)			::GE::Log::GetClientLogger()->info(__VA_ARGS__)
	#define GE_DEBUG(...)			::GE::Log::GetClientLogger()->debug(__VA_ARGS__)
	#define GE_WARN(...)			::GE::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define GE_ERROR(...)			::GE::Log::GetClientLogger()->error(__VA_ARGS__)

}