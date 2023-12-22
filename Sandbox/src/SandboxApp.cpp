#include <Krystal.h>

class ExampleLayer : public Krys::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		KRYS_INFO("ExampleLayer::Update");
	}

	void OnEvent(Krys::Event& event) override
	{
		KRYS_TRACE("{0}", event);
	}
};

class Sandbox : public Krys::Application
{
public:
  Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Krys::ImGuiLayer());
	}

  ~Sandbox() {}
};

Krys::Application* Krys::CreateApplication()
{
  return new Sandbox();
}
