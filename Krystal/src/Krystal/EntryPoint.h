#pragma once

#ifdef KRYS_PLATFORM_WINDOWS

extern Krys::Application* Krys::CreateApplication();

int main(int argc, char** argv)
{
  Krys::Log::Init();

  KRYS_CORE_INFO("Initialised log");
  KRYS_ERROR("Hello");

  Krys::Application* application = Krys::CreateApplication();
  application->Run();
  delete application;
}

#endif