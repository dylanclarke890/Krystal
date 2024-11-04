#pragma once

#include "Core/Pointers.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class ApplicationContext;

  class Application
  {
  public:
    Application(Unique<ApplicationContext> context, uint32 width, uint32 height) noexcept;
    virtual ~Application() noexcept = default;

    virtual void Run() noexcept;
    virtual void Update(float dt) noexcept = 0;

    template <typename TApplication>
    static Unique<Application> Create(int argc, char **argv) noexcept
    {
      static_assert(std::is_base_of_v<Application, TApplication>,
                    "'TApplication' must derive from 'Krys::Application'.");

      auto appContext = CreateApplicationContext(argc, argv);
      return CreateUnique<TApplication>(std::move(appContext));
    }

  protected:
    bool _running;
    Unique<ApplicationContext> _context;

    static Unique<ApplicationContext> CreateApplicationContext(int argc, char **argv) noexcept;
  };
}