#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/ApplicationContext.hpp"

namespace Krys
{
  struct ApplicationSettings final
  {
    string Title {"Krystal Application"};
    uint32 Width {800};
    uint32 Height {600};
    bool Resizable {false};
    bool VSync {true};
    float Fps {60.0f};
  };

  /// @brief Base class for a Krystal application.
  class Application
  {
  public:
    /// @brief Constructs an `Application`.
    /// @param context Contains the various services provided by the application by default.
    /// @param width The width of the window.
    /// @param height The height of the window.
    Application(Unique<ApplicationContext> context, const ApplicationSettings &settings) noexcept;

    virtual ~Application() noexcept = default;

    /// @brief Runs the application. This method will not return until the app stops running.
    void Run() noexcept;

    /// @brief Main update method. Called once per frame.
    /// @param dt Delta time since the last frame, in seconds.
    virtual void Update(float dt) noexcept = 0;

    /// @brief Main render method. Called once per frame.
    virtual void Render() noexcept = 0;

    template <typename TApplication>
    /// @brief Create a new `Application`.
    /// @tparam TApplication The derived `Application` type.
    /// @param argc Command line argument count.
    /// @param argv Command line arguments.
    /// @param width The desired width of the application.
    /// @param height The desired height of the application.
    static Unique<Application> Create(int argc, char **argv, const ApplicationSettings &settings) noexcept
    {
      static_assert(std::is_base_of_v<Application, TApplication>, "Must be derived from Krys::Application");
      auto appContext = CreateApplicationContext(argc, argv);
      return CreateUnique<TApplication>(std::move(appContext),
                                        std::forward<const ApplicationSettings>(settings));
    }

  protected:
    bool _running;
    Unique<ApplicationContext> _context;

    static Unique<ApplicationContext> CreateApplicationContext(int argc, char **argv) noexcept;

  private:
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;
    Application(Application &&) = delete;
    Application &operator=(Application &&) = delete;
  };
}