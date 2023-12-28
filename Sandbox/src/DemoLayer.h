#pragma once

#include <Krystal.h>
#include <imgui/imgui.h>

class DemoLayer : public Krys::Layer
{
private:
  std::shared_ptr<Krys::Shader> m_Shader;
  std::shared_ptr<Krys::Shader> m_BlueShader;
  std::shared_ptr<Krys::VertexArray> m_TriangleVertexArray;
  std::shared_ptr<Krys::VertexArray> m_SquareVertexArray;

  Krys::OrthographicCamera m_Camera;
public:
	DemoLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) 
  {
    std::string vertexSource = R"(
      #version 330 core
      
      layout (location = 0) in vec3 a_Position;
      layout (location = 1) in vec4 a_Color;

      uniform mat4 u_ViewProjection;

      out vec3 v_Position; 
      out vec4 v_Color; 

      void main()
      {
        v_Position = a_Position;
        v_Color = a_Color;
        gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

      uniform mat4 u_ViewProjection;

      void main()
      {
        gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
      -0.75f, -0.75f, 0.0f,
       0.75f, -0.75f, 0.0f,
       0.75f,  0.75f, 0.0f,
      -0.75f,  0.75f, 0.0f
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

    m_BlueShader.reset(new Krys::Shader(blueShaderVertexSource, blueShaderFragmentSource));
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
	
	virtual void OnUpdate() override
	{
    Krys::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Krys::RenderCommand::Clear();

    m_Camera.SetPosition({ 0.75f, 0.75f, 0.0f });
    m_Camera.SetRotation(69.0f);
    Krys::Renderer::BeginScene(m_Camera);
    {
      Krys::Renderer::Submit(m_BlueShader, m_SquareVertexArray);
      Krys::Renderer::Submit(m_Shader, m_TriangleVertexArray);
    }
    Krys::Renderer::EndScene();
	}
};
