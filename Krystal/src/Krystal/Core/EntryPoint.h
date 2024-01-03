#pragma once

#include "Krystal/Core/Core.h"
#include "Krystal/Core/Log.h"
#include "Krystal/Core/Application.h"
#include "Krystal/Debug/Instrumentor.h"

#ifdef KRYS_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
  Krys::Log::Init();

  KRYS_PROFILE_BEGIN_SESSION("Startup", "KrystalProfile-Startup.json");
  auto application = Krys::CreateApplication();
  KRYS_PROFILE_END_SESSION();
  
  KRYS_PROFILE_BEGIN_SESSION("Runtime", "KrystalProfile-Runtime.json");
  application->Run();
  KRYS_PROFILE_END_SESSION();

  KRYS_PROFILE_BEGIN_SESSION("Shutdown", "KrystalProfile-Shutdown.json");
  delete application;
  KRYS_PROFILE_END_SESSION();
}

#endif