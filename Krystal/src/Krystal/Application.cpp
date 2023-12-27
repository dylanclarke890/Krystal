#include "krys-pch.h"
#include "Application.h"
#include "Input.h"

// TODO: Temporary
#include <glad/glad.h>

namespace Krys
{
  Application* Application::s_Instance = nullptr;

  Application::Application(): m_Running(true)
  {
    KRYS_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    std::string vertexSource = R"(
      #version 330 core
      
      layout (location = 0) in vec3 a_Position;
      layout (location = 1) in vec4 a_Color;

      out vec3 v_Position; 
      out vec4 v_Color; 

      void main()
      {
        v_Position = a_Position;
        gl_Position = vec4(a_Position, 1.0);
        v_Color = a_Color;
      }
    )";

    std::string fragmentSource = R"(
      #version 330 core
      
      layout (location = 0) out vec4 color;

      in vec3 v_Position; 
      in vec4 v_Color; 

      void main()
      {
        color = vec4(v_Position * 0.5 + 0.5, 1.0);
        color = v_Color;
      }
    )";

    std::string blueShaderVertexSource = R"(
      #version 330 core
      
      layout (location = 0) in vec3 a_Position;

      void main()
      {
        gl_Position = vec4(a_Position, 1.0);
      }
    )";

    std::string blueShaderFragmentSource = R"(
      #version 330 core
      
      layout (location = 0) out vec4 color;

      void main()
      {
        color = vec4(0.2, 0.3, 0.8, 1.0);
      }
    )";

    float triangleVertices[3 * 7] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
       0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
       0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    float squareVertices[3 * 4] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.5f,  0.5f, 0.0f,
      -0.5f,  0.5f, 0.0f
    };

    unsigned int triangleIndices[3] = { 0, 1, 2 };
    unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    std::shared_ptr<VertexBuffer> triangleVertexBuffer;
    std::shared_ptr<IndexBuffer> triangleIndexBuffer;

    m_Shader.reset(new Shader(vertexSource, fragmentSource));
    m_TriangleVertexArray.reset(VertexArray::Create());
    triangleVertexBuffer.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
    triangleIndexBuffer.reset(IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));

    triangleVertexBuffer->SetLayout({
      { ShaderDataType::Float3, "a_Position" },
      { ShaderDataType::Float4, "a_Color" }
    });
    m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
    m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);


    std::shared_ptr<VertexBuffer> squareVertexBuffer;
    std::shared_ptr<IndexBuffer> squareIndexBuffer;

    m_BlueShader.reset(new Shader(blueShaderVertexSource, blueShaderFragmentSource));
    m_SquareVertexArray.reset(VertexArray::Create());
    squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    
    squareVertexBuffer->SetLayout({ { ShaderDataType::Float3, "a_Position" } });
    m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
    m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);
  }
  
  Application::~Application() {}

  void Application::Run()
  {
    while (m_Running) 
    {
      // TODO: Temporary
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      m_BlueShader->Bind();
      m_SquareVertexArray->Bind();
      glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

      m_Shader->Bind();
      m_TriangleVertexArray->Bind();
      glDrawElements(GL_TRIANGLES, m_TriangleVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

      for (Layer* layer : m_LayerStack)
        layer->OnUpdate();

      m_ImGuiLayer->Begin();
      for (Layer* layer : m_LayerStack)
        layer->OnImGuiRender();
      m_ImGuiLayer->End();

      m_Window->OnUpdate();
    }
  }

  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(KRYS_BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
    {
      (*--it)->OnEvent(e);
      if (e.Handled)
        break;
    }
  }

  void Application::PushLayer(Layer* layer)
  {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* overlay)
  {
    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
  }

  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    m_Running = false;
    return true;
  }
}