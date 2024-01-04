#include "krys-pch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Krystal/Core/KeyCodes.h"
#include "Krystal/Core/MouseCodes.h"

#include "Krystal/Events/ApplicationEvent.h"
#include "Krystal/Events/KeyEvent.h"
#include "Krystal/Events/MouseEvent.h"

#include "Krystal/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Krys
{
	static uint8_t s_GLFWWindowCount = 0;
	
	static void GLFWErrorCallback(int error, const char* description)
	{
		KRYS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		KRYS_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		KRYS_PROFILE_FUNCTION();
		
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		KRYS_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		if (s_GLFWWindowCount == 0)
		{
			KRYS_CORE_INFO("Start Up: Initialising GLFW.");
			{
				KRYS_PROFILE_SCOPE("glfwInit");

				int success = glfwInit();
				KRYS_CORE_ASSERT(success, "Could not intialise GLFW!");
			}
			KRYS_CORE_INFO("Start Up: GLFW initialised.");
		}

		{
			KRYS_PROFILE_SCOPE("glfwCreateWindow");

#ifdef KRYS_DEBUG
			if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		}

		if (s_GLFWWindowCount++ == 0)
			KRYS_CORE_INFO("Start Up: Creating Window:", props.Title, props.Width, props.Height);
		else
			KRYS_CORE_INFO("Creating Window:", props.Title, props.Width, props.Height);
		KRYS_CORE_INFO("- Title: {0}", props.Title);
		KRYS_CORE_INFO("- Size: {0} x {1}", props.Width, props.Height);

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Height = height;
				data.Width = width;
				
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) 
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(static_cast<KeyCode>(key), 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(static_cast<KeyCode>(key));
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(static_cast<KeyCode>(key), 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(static_cast<KeyCode>(key));
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) 
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(static_cast<MouseCode>(button));
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPosition, double yPosition)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPosition, (float)yPosition);
				data.EventCallback(event);
			});

		glfwSetErrorCallback(GLFWErrorCallback);
	}

	void WindowsWindow::Shutdown()
	{
		KRYS_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);

		if (--s_GLFWWindowCount == 0)
		{
			KRYS_CORE_INFO("Shut Down: Terminating GLFW.");
			{

			}
			glfwTerminate();
			KRYS_CORE_INFO("Shut Down: GLFW Terminated.");
		}
	}

	void WindowsWindow::OnUpdate()
	{
		KRYS_PROFILE_FUNCTION();
		
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		KRYS_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}