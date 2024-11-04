#pragma once

namespace Krys
{
#define NO_DISCARD [[nodiscard]]

#define NO_COPY_AND_ASSIGN(Class)                                                                                      \
  Class(const Class &) = delete;                                                                                       \
  Class &operator=(const Class &) = delete;
}