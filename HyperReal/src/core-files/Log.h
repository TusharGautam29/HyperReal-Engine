#pragma once
#include <memory>
#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace HyperR {
	class HyperR_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}
// Core log macros
#define HR_CORE_TRACE(...)    ::HyperR::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HR_CORE_INFO(...)     ::HyperR::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HR_CORE_WARN(...)     ::HyperR::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HR_CORE_ERROR(...)    ::HyperR::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HR_CORE_FATAL(...)    ::HyperR::Log::GetCoreLogger()->fatal(__VA_ARGS__)
// Client log macros
#define HR_TRACE(...)	      ::HyperR::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HR_INFO(...)	      ::HyperR::Log::GetClientLogger()->info(__VA_ARGS__)
#define HR_WARN(...)	      ::HyperR::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HR_ERROR(...)	      ::HyperR::Log::GetClientLogger()->error(__VA_ARGS__)
#define HR_FATAL(...)	      ::HyperR::Log::GetClientLogger()->fatal(__VA_ARGS__)
