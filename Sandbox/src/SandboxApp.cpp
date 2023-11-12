#include <Krystal.h>

class Sandbox : public Krys::Application
{
public:
  Sandbox() {}

  ~Sandbox() {}
};

Krys::Application* Krys::CreateApplication()
{
  return new Sandbox();
}
