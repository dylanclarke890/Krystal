#pragma once
#include "Krystal.h"

// TODO: Events in Krystal are currently blocking, meaning when an event occurs it
// immediately gets dispatched and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event
// bus and process them during the "event" part of the update stage.
enum class EventType
{
  NoType,
  Shutdown,
  Mouse,
  MouseDown,
  MouseUp,
};

enum EventCategory
{
  NoCategory,
  EventCategoryApp = BIT(0),
  EventCategoryInput = BIT(1),
  EventCategoryMouse = BIT(2)
};

enum MouseButton
{
  NoButton,
  Primary = BIT(0),
  Secondary = BIT(1),
  Auxiliary = BIT(2),
  Fourth = BIT(3),
  Fifth = BIT(4)
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
  Event &_Event;

public:
  EventDispatcher(Event &event) : _Event(event) {}

  template <typename T, typename F> // F will be deduced by the compiler
  bool Dispatch(const F &func)
  {
    if (_Event.GetEventType() == T::GetStaticType())
    {
      _Event.Handled |= func(static_cast<T &>(_Event));
      return true;
    }
    return false;
  }
};