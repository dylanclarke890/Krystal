#pragma once

#include "Core/Defines.hpp"
#include "Core/Pointers.hpp"
#include "Core/Types.hpp"
#include "Core/ApplicationContext.hpp"

namespace Krys
{
  class Application
  {
  public:
    Application(Unique<ApplicationContext> context, uint32 width, uint32 height) noexcept;
    virtual ~Application() noexcept = default;

    virtual void Run() noexcept;
    virtual void Update(float dt) noexcept = 0;

    template <typename TApplication>
    REQUIRES((std::is_base_of_v<Application, TApplication>))
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