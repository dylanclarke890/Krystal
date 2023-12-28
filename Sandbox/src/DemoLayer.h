#pragma once

#include <Krystal.h>
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>

class DemoLayer : public Krys::Layer
{
private:
  std::shared_ptr<Krys::Shader> m_Shader;
  std::shared_ptr<Krys::Shader> m_FlatColorShader;
  std::shared_ptr<Krys::VertexArray> m_TriangleVertexArray;
  std::shared_ptr<Krys::VertexArray> m_SquareVertexArray;

  Krys::OrthographicCamera m_Camera;
  glm::vec3 m_CameraPosition;
  float m_CameraRotation;
  float m_CameraMoveSpeed;
  float m_CameraRotateSpeed;

public:
	DemoLayer() : Layer("Example"),
    m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), 
    m_CameraPosition(0.0f),
    m_CameraMoveSpeed(5.0f),
    m_CameraRotateSpeed(180.0f),
    m_CameraRotation(0.0f)
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

      uniform vec4 u_Color;

      void main()
      {
        color = u_Color;
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

    std::shared_ptr<Krys::VertexBuffer> triangleVertexBuffer;
    std::shared_ptr<Krys::IndexBuffer> triangleIndexBuffer;

    m_Shader.reset(new Krys::Shader(vertexSource, fragmentSource));
    m_TriangleVertexArray.reset(Krys::VertexArray::Create());
    triangleVertexBuffer.reset(Krys::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
    triangleIndexBuffer.reset(Krys::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));

    triangleVertexBuffer->SetLayout({
      { Krys::ShaderDataType::Float3, "a_Position" },
      { Krys::ShaderDataType::Float4, "a_Color" }
      });
    m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
    m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);

    std::shared_ptr<Krys::VertexBuffer> squareVertexBuffer;
    std::shared_ptr<Krys::IndexBuffer> squareIndexBuffer;

    m_FlatColorShader.reset(new Krys::Shader(flatColorShaderVertexSource, flatColorShaderFragmentSource));
    m_SquareVertexArray.reset(Krys::VertexArray::Create());
    squareVertexBuffer.reset(Krys::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareIndexBuffer.reset(Krys::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

    squareVertexBuffer->SetLayout({ { Krys::ShaderDataType::Float3, "a_Position" } });
    m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
    m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);
  }

	virtual void OnImGuiRender() override
	{
	}
	
	virtual void OnUpdate(Krys::TimeStep ts) override
	{
    Krys::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Krys::RenderCommand::Clear();

    if (Krys::Input::IsKeyPressed(KRYS_KEY_A))
      m_CameraPosition.x -= m_CameraMoveSpeed * ts;
    else if (Krys::Input::IsKeyPressed(KRYS_KEY_D))
      m_CameraPosition.x += m_CameraMoveSpeed * ts;

    if (Krys::Input::IsKeyPressed(KRYS_KEY_W))
      m_CameraPosition.y += m_CameraMoveSpeed * ts;
    else if (Krys::Input::IsKeyPressed(KRYS_KEY_S))
      m_CameraPosition.y -= m_CameraMoveSpeed * ts;

    if (Krys::Input::IsKeyPressed(KRYS_KEY_Q))
      m_CameraRotation += m_CameraRotateSpeed * ts;
    else if (Krys::Input::IsKeyPressed(KRYS_KEY_E))
      m_CameraRotation -= m_CameraRotateSpeed * ts;

    m_Camera.SetPosition(m_CameraPosition);
    m_Camera.SetRotation(m_CameraRotation);

    Krys::Renderer::BeginScene(m_Camera);
    {
      static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

      glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
      glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

      for (int y = 0; y < 20; y++)
      {
        for (int x = 0; x < 20; x++)
        {
          glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
          glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
         
          m_FlatColorShader->Bind();

          if (x % 2 == 0)
            m_FlatColorShader->UploadUniformFloat4("u_Color", redColor);
          else
            m_FlatColorShader->UploadUniformFloat4("u_Color", blueColor);

          Krys::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
        }
      }

      Krys::Renderer::Submit(m_Shader, m_TriangleVertexArray);
    }
    Krys::Renderer::EndScene();
	}
};
