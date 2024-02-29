#include "gepch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace GE {

	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();

}