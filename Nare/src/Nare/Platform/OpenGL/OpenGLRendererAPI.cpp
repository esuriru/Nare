#include "OpenGLRendererAPI.h"
#include "Nare/Renderer/VertexArray.h"
#include "Nare/Mathf/Vector4.h"

#include <GLAD/glad.h>

namespace Nare
{
	void OpenGLRendererAPI::Init()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		// TODO - Might be better to make an overload of this function so that a if statement doesn't get run everytime we want to render something.
        // TODO - Wary about this vertex array bind.
        vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, static_cast<GLint>(count), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::SetClearColour(const Vector4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}


}
