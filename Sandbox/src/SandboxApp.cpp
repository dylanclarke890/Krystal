#include <Krystal.h>
#include <imgui/imgui.h>

class ExampleLayer : public Krys::Layer
{
public:
	ExampleLayer() : Layer("Example") {}
	
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello");
		ImGui::End();
	}
};

class Sandbox : public Krys::Application
{
public:
  Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

  ~Sandbox() {}
};

Krys::Application* Krys::CreateApplication()
{
  return new Sandbox();
}
