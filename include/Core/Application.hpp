#pragma once

#include "Base/Defines.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/ApplicationContext.hpp"

namespace Krys
{
  /// @brief Base class for a Krystal application.
  class Application
  {
  public:
    /// @brief Constructs an `Application`.
    /// @param context Contains the various services provided by the application by default.
    /// @param width The width of the window.
    /// @param height The height of the window.
    Application(Unique<ApplicationContext> context, uint32 width, uint32 height) noexcept;

    virtual ~Application() noexcept = default;

    /// @brief Runs the application. This method will not return until the app stops running.
    virtual void Run() noexcept;

    /// @brief Main update method. Called once per frame.
    /// @param dt Delta time since the last frame, in seconds.
    virtual void Update(float dt) noexcept = 0;

    template <typename TApplication>
    REQUIRES((std::is_base_of_v<Application, TApplication>))
    /// @brief Create a new `Application`.
    /// @tparam TApplication The derived `Application` type.
    /// @param argc Command line argument count.
    /// @param argv Command line arguments.
    /// @param width The desired width of the application.
    /// @param height The desired height of the application.
    static Unique<Application> Create(int argc, char **argv, uint32 width, uint32 height) noexcept
    {
      auto appContext = CreateApplicationContext(argc, argv);
      return CreateUnique<TApplication>(std::move(appContext), width, height);
    }

  protected:
    bool _running;
    Unique<ApplicationContext> _context;

    static Unique<ApplicationContext> CreateApplicationContext(int argc, char **argv) noexcept;
  };
}