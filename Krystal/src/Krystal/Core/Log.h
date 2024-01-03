#pragma once

#include "Krystal/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Krys
{
  class Log
  {
  private:
    static Ref<spdlog::logger> s_CoreLogger;
    static Ref<spdlog::logger> s_ClientLogger;
  public:
    static void Init();

    inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
    inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };
  };
}

#define KRYS_CORE_TRACE(...)    ::Krys::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KRYS_CORE_INFO(...)     ::Krys::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KRYS_CORE_WARN(...)     ::Krys::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KRYS_CORE_ERROR(...)    ::Krys::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KRYS_CORE_CRITICAL(...) ::Krys::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define KRYS_TRACE(...)         ::Krys::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KRYS_INFO(...)          ::Krys::Log::GetClientLogger()->info(__VA_ARGS__)
#define KRYS_WARN(...)          ::Krys::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KRYS_ERROR(...)         ::Krys::Log::GetClientLogger()->error(__VA_ARGS__)
#define KRYS_CRITICAL(...)      ::Krys::Log::GetClientLogger()->critical(__VA_ARGS__)