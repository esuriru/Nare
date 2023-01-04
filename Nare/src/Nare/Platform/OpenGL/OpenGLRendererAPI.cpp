#include "OpenGLRendererAPI.h"
#include "Nare/Renderer/VertexArray.h"
#include "Nare/Mathf/Vector4.h"

#include <GLAD/glad.h>

namespace Nare
{
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SetClearColour(const Vector4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}


}
