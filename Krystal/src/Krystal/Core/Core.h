#pragma once

#include <memory>

// -------- CONFIG --------
#define KRYS_ENABLE_PROFILING
// -------- CONFIG --------

#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define KRYS_PLATFORM_WINDOWS
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define KRYS_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define KRYS_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
	* since android is based on the linux kernel
	* it has __linux__ defined */
#elif defined(__ANDROID__)
#define KRYS_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define KRYS_PLATFORM_LINUX
#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection

#ifdef KRYS_ENABLE_ASSERTS
  #define KRYS_ASSERT(x, ...) { if(!(x)) { KRYS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
  #define KRYS_CORE_ASSERT(x, ...) { if(!(x)) { KRYS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
  #define KRYS_ASSERT(x, ...)
  #define KRYS_CORE_ASSERT(x, ...)
#endif

#define __KRYS_CONCAT_NUM_TO_STR(str, num) str  ## num

#ifdef KRYS_ENABLE_PROFILING
#define KRYS_PROFILE_BEGIN_SESSION(name, filepath) ::Krys::Instrumentor::Get().BeginSession(name, filepath)
#define KRYS_PROFILE_END_SESSION() ::Krys::Instrumentor::Get().EndSession()
#define KRYS_PROFILE_SCOPE(name) __KRYS_CONCAT_NUM_TO_STR(::Krys::InstrumentationTimer timer, __LINE__) (name)
#define KRYS_PROFILE_FUNCTION() KRYS_PROFILE_SCOPE(__FUNCSIG__)
#else
#define KRYS_PROFILE_BEGIN_SESSION(name)
#define KRYS_PROFILE_END_SESSION()
#define KRYS_PROFILE_SCOPE(name)
#define KRYS_PROFILE_FUNCTION()
#endif

#define KRYS_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#define BIT(x) (1 << x)

namespace Krys
{
  template<typename T>
  using Scope = std::unique_ptr<T>;
 
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

  template<typename T>
  using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}