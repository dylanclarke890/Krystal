#pragma once

#include <type_traits>

#include "Core.h"
#include "Application.h"

namespace Krys
{
  class Engine
  {
  public:
    Unique<Application> App;

  public:
    Engine(Unique<Application> app)
        : App(std::move(app)) {}

    void Run()
    {
      KRYS_ASSERT(App, "App cannot be null", 0);
      KRYS_LOG("Starting up Application...");
      App->Startup();

      KRYS_LOG("Running Application...");
      App->Run();

      KRYS_LOG("Shutting down Application...");
      App->Shutdown();
    }
  };

  template <typename TApplication, typename... Args>
  static Unique<Engine> CreateEngine(Args &&...args)
  {
    static_assert(std::is_base_of_v<Application, TApplication>, "Application must derive from Krys::Application.");
    auto app = CreateUnique<TApplication>(std::forward<Args>(args)...);
    return CreateUnique<Engine>(std::move(app));
  }
}