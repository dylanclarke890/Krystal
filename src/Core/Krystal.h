#pragma once

// --------- TYPES ----------
#include <stdint.h>
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float float32;
typedef double float64;
// --------- TYPES ----------

// -------- LOGGING ---------
#define VA_ARGS(...) , ##__VA_ARGS__
#ifdef KRYS_ENABLE_ASSERTS
#include "Logging/Logger.h"
#define KRYS_DEBUG(message, ...) Logger::Log(LogLevel::Debug, message VA_ARGS(__VA_ARGS__))
#define KRYS_INFO(message, ...) Logger::Log(LogLevel::Info, message VA_ARGS(__VA_ARGS__))
#define KRYS_WARN(message, ...) Logger::Log(LogLevel::Warning, message VA_ARGS(__VA_ARGS__))
#define KRYS_ERROR(message, ...) Logger::Log(LogLevel::Error, message VA_ARGS(__VA_ARGS__))
#define KRYS_CRITICAL(message, ...) Logger::Log(LogLevel::Fatal, message VA_ARGS(__VA_ARGS__))
#else
#define KRYS_DEBUG(message, ...)
#define KRYS_INFO(message, ...)
#define KRYS_WARN(message, ...)
#define KRYS_ERROR(message, ...)
#define KRYS_CRITICAL(message, ...)
#endif
// -------- LOGGING ---------

// ------- MISC/UTILS -------
#define BIT(x) (1 << x)
#define Kilobytes(value) ((value) * 1024)
#define Megabytes(value) (Kilobytes(value) * 1024)
#define Gigabytes(value) (Megabytes(value) * 1024)
#define KRYS_BIND_EVENT_FN(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
// ------- MISC/UTILS -------

// TODO: API structure