#pragma once
#include "spdlog/spdlog.h"

namespace StratEngine
{
    class Log
    {
        public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };

        private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define STRAT_CORE_TRACE(...)   ::StratEngine::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define STRAT_CORE_INFO(...)    ::StratEngine::Log::GetCoreLogger()->info(__VA_ARGS__);
#define STRAT_CORE_WARN(...)    ::StratEngine::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define STRAT_CORE_ERROR(...)   ::StratEngine::Log::GetCoreLogger()->error(__VA_ARGS__);
#define STRAT_CORE_FATAL(...)   ::StratEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__);

#define STRAT_CLIENT_TRACE(...)   ::StratEngine::Log::GetClientLogger()->trace(__VA_ARGS__);
#define STRAT_CLIENT_INFO(...)    ::StratEngine::Log::GetClientLogger()->info(__VA_ARGS__);
#define STRAT_CLIENT_WARN(...)    ::StratEngine::Log::GetClientLogger()->warn(__VA_ARGS__);
#define STRAT_CLIENT_ERROR(...)   ::StratEngine::Log::GetClientLogger()->error(__VA_ARGS__);
#define STRAT_CLIENT_FATAL(...)   ::StratEngine::Log::GetClientLogger()->fatal(__VA_ARGS__);