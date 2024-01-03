#pragma once

#include "Krystal/Core/Core.h"

#ifdef KRYS_PLATFORM_WINDOWS

extern Krys::Application* Krys::CreateApplication();

int main(int argc, char** argv)
{
  Krys::Log::Init();

  Krys::Application* application = Krys::CreateApplication();
  application->Run();
  delete application;
}

#endif