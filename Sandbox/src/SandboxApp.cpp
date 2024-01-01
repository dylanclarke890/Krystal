#include "DemoLayer.h"

#include <Krystal.h>
#include <imgui/imgui.h>

#include "Sandbox2DLayer.h"

class Sandbox : public Krys::Application
{
public:
  Sandbox() 
	{
		PushLayer(new Sandbox2DLayer());
	}

  ~Sandbox() {}
};

Krys::Application* Krys::CreateApplication()
{
  return new Sandbox();
}
