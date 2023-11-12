#pragma once

#ifdef KRYS_PLATFORM_WINDOWS

extern Krys::Application* Krys::CreateApplication();

int main(int argc, char** argv)
{
  Krys::Application* application = Krys::CreateApplication();
  application->Run();
  delete application;
}

#endif