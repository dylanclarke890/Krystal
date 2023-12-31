#include "krys-pch.h"
#include "Krystal/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Krys
{
  RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}