#include "DemoLayer.h"

#include <Krystal.h>
#include <imgui/imgui.h>


class Sandbox : public Krys::Application
{
public:
  Sandbox() 
	{
		PushLayer(new DemoLayer());
	}

  ~Sandbox() {}
};

Krys::Application* Krys::CreateApplication()
{
  return new Sandbox();
}
