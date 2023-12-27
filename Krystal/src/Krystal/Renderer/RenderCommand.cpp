#include "krys-pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Krys
{
  RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}