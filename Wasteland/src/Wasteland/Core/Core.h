#pragma once

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
/* Windows x64/x86 */
#ifdef _WIN64
/* Windows x64 */
#define WL_PLATFORM_WINDOWS
#else
/* Windows x64 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all platforms
so we must check all of them (in this order)
to ensure that we're running on MAC
and nor some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define WL_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define WL_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
/* We also have to check __ANDROID__ before __linux__
since android is based on the linux kernel
it has __linux__ defined */
#elif defined(__ANDROID__)
#define WL_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define WL_PLATFORM_LINUX
#error "Linux is not supported!"
#else
/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection

// DLL support
#ifdef WL_PLATFORM_WINDOWS
#if WL_DYNAMIC_LINK
#ifdef WL_BUILD_DLL
#define WL_API __declspec(dllexport)
#else
#define WL_API __declspec(dllimport)
#endif
#else
#define WL_API
#endif
#else
#error Wasteland only supports Windows!
#endif // End of DLL support

#ifdef WL_DEBUG
#if defined(WL_PLATFORM_WINDOWS)
#define WL_DEBUGBREAK() __debugbreak()
#elif defined(WL_PLATFORM_LINUX)
#include <signal.h>
#define WL_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define WL_ENABLE_ASSERTS
#else
#define WL_DEBUGBREAK()
#endif

#ifdef WL_ENABLE_ASSERTS
#define WL_ASSERT(x, ...) { if(!(x)) { WL_ERROR("Assertion Failed: {0}", __VA_ARGS__); WL_DEBUGBREAK(); } }
#define WL_CORE_ASSERT(x, ...) { if(!(x)) { WL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); WL_DEBUGBREAK(); } }
#else
#define WL_ASSERT(x, ...)
#define WL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define WL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Wasteland {

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