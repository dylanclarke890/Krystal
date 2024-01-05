#pragma once

#include <memory>

// --- PLATFORM DETECTION ---
#if defined(_WIN32)																							  // Windows platform detection
	#if defined(_WIN64)
		#define KRYS_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif

#elif defined(__APPLE__) || defined(__MACH__)											// Apple platform detection
	#include <TargetConditionals.h>
	// TARGET_OS_MAC exists on all platforms, not just on MacOS.
	// Use this order of checks to determine the specific platform. 
	#if defined(TARGET_IPHONE_SIMULATOR)
		#error "IOS simulator is not supported!"
	#elif defined(TARGET_OS_IPHONE)
		#define KRYS_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif defined(TARGET_OS_MAC)
		#define KRYS_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif

// Linux platform detection
#elif defined(__linux__)																				  // Apple platform detection
	// __linux__ exists on both android and linux.
	// Check for __ANDROID__ to determine the platform.
	#if defined(__ANDROID__)
		#define KRYS_PLATFORM_ANDROID
		#error "Android is not supported!"
	#else
		#define KRYS_PLATFORM_LINUX
		#error "Linux is not supported!"
	#endif
#else
	#error "Unknown platform!"
#endif
// --- PLATFORM DETECTION ---

// ---- CONFIG SETTINGS -----
#ifdef KRYS_DEBUG
	#define KRYS_ENABLE_DEBUG_BREAK
	#define KRYS_ENABLE_PROFILING
	#define KRYS_ENABLE_ASSERTS
#endif

#ifdef KRYS_RELEASE
	#define KRYS_ENABLE_PROFILING
	#define KRYS_ENABLE_ASSERTS
#endif

#ifdef KRYS_PUBLISH
#endif
// ---- CONFIG SETTINGS -----

// ------ DEBUG BREAK -------
#ifdef KRYS_ENABLE_DEBUG_BREAK
	#if defined(KRYS_PLATFORM_WINDOWS)
		#define KRYS_DEBUG_BREAK() __debugbreak()
	#elif defined(KRYS_PLATFORM_LINUX)
		#include <signal.h>
		#define KRYS_DEBUG_BREAK() raise(SIGTRAP)
	#else
		#error "KRYS_DEBUG_BREAK is not supported for your platform!"
	#endif
#endif
// ------ DEBUG BREAK -------

// -------- ASSERTS ---------
#ifdef KRYS_ENABLE_ASSERTS
  #define KRYS_ASSERT(x, ...) { if(!(x)) { KRYS_ERROR("Assertion Failed: {0}", __VA_ARGS__); KRYS_DEBUG_BREAK(); } }
  #define KRYS_CORE_ASSERT(x, ...) { if(!(x)) { KRYS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); KRYS_DEBUG_BREAK(); } }
#else
  #define KRYS_ASSERT(x, ...)
  #define KRYS_CORE_ASSERT(x, ...)
#endif
// -------- ASSERTS ---------

// ------- FUNC NAME --------
// Resolve the best macro for a function signature, based on the compiler being used.
// Note: only gets resolved during preprocessing so your code editor may highlight the wrong one (i.e the 'else' branch) but should still work. 
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define __KRYS_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define __KRYS_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
	#define __KRYS_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define __KRYS_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define __KRYS_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define __KRYS_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define __KRYS_FUNC_SIG __func__
#else
	#define __KRYS_FUNC_SIG "__KRYS_FUNC_SIG unknown!"
#endif
// ------- FUNC NAME --------


// ------- PROFILING --------
#ifdef KRYS_ENABLE_PROFILING
	#define __KRYS_CONCAT_NUM_TO_STR(str, num) str  ## num

	#define KRYS_PROFILE_BEGIN_SESSION(name, filepath) ::Krys::Instrumentor::Get().BeginSession(name, filepath)
	#define KRYS_PROFILE_END_SESSION() ::Krys::Instrumentor::Get().EndSession()
	#define KRYS_PROFILE_SCOPE(name) __KRYS_CONCAT_NUM_TO_STR(::Krys::InstrumentationTimer timer, __LINE__) (name)
	#define KRYS_PROFILE_FUNCTION() KRYS_PROFILE_SCOPE(__KRYS_FUNC_SIG)

	#undef __KRYS_CONCAT_NUM_TO_STR
#else
	#define KRYS_PROFILE_BEGIN_SESSION(name)
	#define KRYS_PROFILE_END_SESSION()
	#define KRYS_PROFILE_SCOPE(name)
	#define KRYS_PROFILE_FUNCTION()
#endif
// ------- PROFILING --------

// ------- MISC/UTILS -------
#define KRYS_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIT(x) (1 << x)
// ------- MISC/UTILS -------

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