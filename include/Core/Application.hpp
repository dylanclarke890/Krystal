#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/ApplicationContext.hpp"
#include "Core/ApplicationSettings.hpp"

namespace Krys
{
  /// @brief Base class for a Krystal application.
  class Application
  {
  public:
    /// @brief Constructs an `Application`.
    /// @param context Contains the various services provided to the application by default.
    /// @param width The width of the window.
    /// @param height The height of the window.
    Application(Unique<ApplicationContext> context) noexcept;

    virtual ~Application() noexcept = default;

    /// @brief Called once before the application starts running, after all services have been initialized.
    virtual void OnInit() noexcept;

    /// @brief Per-frame update method.
    /// @param dt Delta time since the last frame, in seconds.
    virtual void OnUpdate(float dt) noexcept;

    /// @brief Fixed rate update method.
    /// @param dt The fixed time step, in seconds. Does not change unless explicitly set.
    virtual void OnFixedUpdate(float dt) noexcept;

    /// @brief Per-frame render method.
    virtual void OnRender() noexcept;

    /// @brief Called once after the application stops running, before all services are shut down.
    virtual void OnShutdown() noexcept;

    /// @brief Runs the application. Will not return until the app stops running.
    void Run() noexcept;

    /// @brief Create a new `Application`.
    /// @tparam TApplication The derived `Application` type.
    /// @param argc Command line argument count.
    /// @param argv Command line arguments.
    /// @param settings Application settings.
    template <typename TApplication>
    static Unique<Application> Create(int argc, char **argv, const ApplicationSettings &settings) noexcept
    {
      static_assert(std::is_base_of_v<Application, TApplication>, "Must be derived from Krys::Application");
      auto appContext =
        CreateApplicationContext(argc, argv, std::forward<const ApplicationSettings &>(settings));
      return CreateUnique<TApplication>(std::move(appContext));
    }

  protected:
    bool _running;
    Unique<ApplicationContext> _context;

    static Unique<ApplicationContext> CreateApplicationContext(int argc, char **argv,
                                                               const ApplicationSettings &settings) noexcept;

  private:
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;
    Application(Application &&) = delete;
    Application &operator=(Application &&) = delete;
  };
}