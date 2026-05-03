#include "wlpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Wasteland {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}