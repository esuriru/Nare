#pragma once


#pragma region HEADERS_FOR_CLIENT_USAGE

#include "Nare/Core/Application.h"
#include "Nare/Core/Log.h"
#include "Nare/Core/Layer.h"
#include "Nare/Core/Input.h"
#include "Nare/Core/Keycodes.h"
#include "Nare/Core/MouseButtonCodes.h"

#include "Nare/Core/Timestep.h"

// Math
#include "Nare/Core/NareMath.h"

// Entry point
#include "Nare/Core/Entry.hpp"

// Renderer
#include "Nare/Renderer/Renderer.h"
#include "Nare/Renderer/RenderCommand.h"
#include "Nare/Renderer/RendererAPI.h"
#include "Nare/Renderer/Buffer.h"
#include "Nare/Renderer/Shader.h"
#include "Nare/Platform/OpenGL/OpenGLShader.h"
#include "Nare/Renderer/VertexArray.h"
#include "Nare/Renderer/Texture.h"

// Events
#include "Nare/Events/Event.h"
#include "Nare/Events/EventDispatcher.h"

#pragma endregion HEADERS_FOR_CLIENT_USAGE For use in Nare Applications.