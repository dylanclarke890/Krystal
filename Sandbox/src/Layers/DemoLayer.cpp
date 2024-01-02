#include "DemoLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h" // TODO: TEMPORARY

DemoLayer::DemoLayer() 
  : Layer("Example"),
  m_CameraController(1280.0f / 720.0f, true),
  m_SquareColor(0.2f, 0.3f, 0.8f)
{
  std::string vertexSource = R"(
      #version 330 core
      
      layout (location = 0) in vec3 a_Position;
      layout (location = 1) in vec4 a_Color;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;

      out vec3 v_Position; 
      out vec4 v_Color; 

      void main()
      {
        v_Position = a_Position;
        v_Color = a_Color;
        gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

  std::string flatColorShaderVertexSource = R"(
      #version 330 core
      
      layout (location = 0) in vec3 a_Position;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;

      void main()
      {
        gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
      }
    )";

  std::string flatColorShaderFragmentSource = R"(
      #version 330 core
      
      layout (location = 0) out vec4 color;

      uniform vec3 u_Color;

      void main()
      {
        color = vec4(u_Color, 1.0f);
      }
    )";

  float triangleVertices[3 * 7] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
  };

  float squareVertices[5 * 4] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
  };

  unsigned int triangleIndices[3] = { 0, 1, 2 };
  unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

  Krys::Ref<Krys::VertexBuffer> triangleVertexBuffer;
  Krys::Ref<Krys::IndexBuffer> triangleIndexBuffer;

  m_Shader = Krys::Shader::Create("TriangleShader", vertexSource, fragmentSource);
  m_TriangleVertexArray = Krys::VertexArray::Create();
  triangleVertexBuffer = Krys::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
  triangleIndexBuffer = Krys::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));

  triangleVertexBuffer->SetLayout({
    { Krys::ShaderDataType::Float3, "a_Position" },
    { Krys::ShaderDataType::Float4, "a_Color" }
    });
  m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
  m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);

  Krys::Ref<Krys::VertexBuffer> squareVertexBuffer;
  Krys::Ref<Krys::IndexBuffer> squareIndexBuffer;

  m_FlatColorShader = Krys::Shader::Create("FlatColourShader", flatColorShaderVertexSource, flatColorShaderFragmentSource);
  m_SquareVertexArray = Krys::VertexArray::Create();
  squareVertexBuffer = Krys::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
  squareIndexBuffer = Krys::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

  squareVertexBuffer->SetLayout({
    { Krys::ShaderDataType::Float3, "a_Position" },
    { Krys::ShaderDataType::Float2, "a_TextureCoord" }
    });
  m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
  m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

  m_TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.krys");
  m_CheckerboardTexture = Krys::Texture2D::Create("assets/textures/Checkerboard.png");
  m_MGTexture = Krys::Texture2D::Create("assets/textures/MG.png");
  m_TextureShader->Bind();
  std::dynamic_pointer_cast<Krys::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
}

void DemoLayer::OnImGuiRender()
{
  ImGui::Begin("Settings");
  ImGui::ColorPicker3("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::End();
}

void DemoLayer::OnUpdate(Krys::TimeStep ts)
{
  m_CameraController.OnUpdate(ts);
  Krys::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
  Krys::RenderCommand::Clear();

  Krys::Renderer::BeginScene(m_CameraController.GetCamera());
  {
    static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    m_FlatColorShader->Bind();
    std::dynamic_pointer_cast<Krys::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

    for (int y = 0; y < 20; y++)
    {
      for (int x = 0; x < 20; x++)
      {
        glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

        Krys::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
      }
    }

    m_CheckerboardTexture->Bind();
    Krys::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    m_MGTexture->Bind();
    Krys::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

    // Triangle
    //Krys::Renderer::Submit(m_Shader, m_TriangleVertexArray);
  }
  Krys::Renderer::EndScene();
}

void DemoLayer::OnEvent(Krys::Event& e)
{
  m_CameraController.OnEvent(e);
}