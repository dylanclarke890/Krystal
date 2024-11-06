#pragma once

namespace Krys
{
/// @brief Convenience macro for the attribute equivalent.
#define NO_DISCARD [[nodiscard]]

/// @brief Convenience macro for the attribute equivalent.
#define NO_RETURN [[noreturn]]

/// @brief Convenience macro for the attribute equivalent.
#define ALLOW_CASE_FALLTHROUGH [[fallthrough]]

/// @brief Convenience macro for the attribute equivalent.
#define BRANCH_LIKELY [[likely]]

/// @brief Convenience macro for the attribute equivalent.
#define BRANCH_UNLIKELY [[unlikely]]

/// @brief Deletes copy and assign constructors for the given class.
#define NO_COPY_AND_ASSIGN(Class)                                                                            \
  Class(const Class &) = delete;                                                                             \
  Class &operator=(const Class &) = delete;
}