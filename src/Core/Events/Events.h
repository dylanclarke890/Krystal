#pragma once

#include "Core.h"
#include "Input/MouseButtons.h"

namespace Krys
{
  enum class EventType
  {
    None,
    Shutdown,
    Resize,
    MousePressed,
    MouseReleased,
    MouseMoved,
    MouseScrolled,
    KeyPressed,
    KeyReleased
  };

  enum EventCategory
  {
    EventCategoryNone,
    EventCategoryApp = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryMouse = BIT(2),
    EventCategoryKeyboard = BIT(3),
  };

#define EVENT_CLASS_TYPE(type)                                                \
  static EventType GetStaticType() { return EventType::type; }                \
  virtual EventType GetEventType() const override { return GetStaticType(); } \
  virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
  virtual int GetCategoryFlags() const override { return category; }

  class Event
  {
    friend class EventDispatcher;

  public:
    virtual ~Event() = default;

    bool Handled = false;
    virtual EventType GetEventType() const = 0;
    virtual const char *GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual const char *ToString() const { return GetName(); }
    bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
  };

  class EventDispatcher
  {
  private:
    Event &event;

  public:
    EventDispatcher(Event &event) : event(event) {}

    template <typename T, typename F> // F will be deduced by the compiler
    // TODO: events currently get handled as they come in, move to a queue system.
    bool Dispatch(const F &func)
    {
      if (!event.Handled && event.GetEventType() == T::GetStaticType())
      {
        event.Handled = func(static_cast<T &>(event));
        return true;
      }
      
      return false;
    }
  };
}
