#pragma once

#include "Base/Attributes.hpp"
#include "Core/StringId.hpp"

namespace Krys
{
  typedef StringId EventType;
  typedef StringIdHasher EventTypeHasher;

/// @brief Convenience macro for setting up the event type for a derived `Event`.
/// @param eventTypeName Must be a string literal. Must be unique across events.
#define KRYS_EVENT_CLASS_TYPE(eventTypeName)                                                                 \
  static NO_DISCARD EventType GetStaticType() noexcept                                                       \
  {                                                                                                          \
    return SID(eventTypeName);                                                                               \
  }                                                                                                          \
  virtual NO_DISCARD EventType GetEventType() const noexcept override                                        \
  {                                                                                                          \
    return GetStaticType();                                                                                  \
  }

  /// @brief Base event class.
  ///
  /// Custom events can easily be created simply by extending this class and specifying it's `EventType`.
  /// A macro has been provided to make this even easier, see `KRYS_EVENT_CLASS_TYPE()`.
  class Event
  {
  public:
    virtual ~Event() = default;

    /// @brief Gets this instance's `EventType`.
    virtual NO_DISCARD EventType GetEventType() const noexcept = 0;

  protected:
    /// @brief Constructs an `Event`.
    Event() noexcept = default;
  };
}