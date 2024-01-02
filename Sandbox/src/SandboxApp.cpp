#include <Krystal.h>
#include <Krystal/Core/EntryPoint.h>
#include <imgui/imgui.h>

#include "Layers/Sandbox2DLayer.h"
#include "Layers/DemoLayer.h"

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
