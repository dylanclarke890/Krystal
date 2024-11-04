#pragma once

#include "Core/Attributes.hpp"
#include "Core/StringId.hpp"

namespace Krys
{
  typedef StringId EventType;

#define KRYS_EVENT_CLASS_TYPE(eventTypeName)                                                                           \
  static NO_DISCARD EventType GetStaticType() noexcept                                                                 \
  {                                                                                                                    \
    return SID(eventTypeName);                                                                                         \
  }                                                                                                                    \
  virtual NO_DISCARD EventType GetEventType() const noexcept override                                                  \
  {                                                                                                                    \
    return GetStaticType();                                                                                            \
  }

  class Event
  {
  public:
    Event() noexcept = default;
    virtual ~Event() = default;
    virtual NO_DISCARD EventType GetEventType() const noexcept = 0;
  };
}