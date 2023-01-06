#include "OpenGLRendererAPI.h"
#include "Nare/Renderer/VertexArray.h"
#include "Nare/Mathf/Vector4.h"

#include <GLAD/glad.h>

namespace Nare
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, static_cast<GLint>(vertexArray->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SetClearColour(const Vector4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}


}
