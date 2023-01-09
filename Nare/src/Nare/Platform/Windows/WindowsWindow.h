#pragma once

#include "Nare/Core/Window.h"
#include "Nare/Core/Core.h"
#include "Nare/Platform/OpenGL/OpenGLContext.h"

struct GLFWwindow;

namespace Nare
{
	class WindowsWindow : public Window
	{
	public:
		explicit WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		void SetVSyncEnabled(bool enabled) override;
		bool IsVSyncEnabled() const override;

#pragma region INLINE_FUNCTIONS
		inline unsigned int GetWidth() const override
		{
			return data_.Width;
		}
		
		inline unsigned int GetHeight() const override
		{
			return data_.Height;
		}

		inline void SetEventCallback(const EventCallback& cb) override
		{
			data_.EventCallback = cb;
		}

		inline virtual void* GetNativeWindow() const override
		{
			return window_;
		}

#pragma endregion INLINE_FUNCTIONS

	private:
#pragma region PRIVATE_FUNCTIONS
		virtual void Init(const WindowProps& props);
		virtual void Exit();
#pragma endregion PRIVATE_FUNCTIONS

#pragma region PRIVATE_DATA_MEMBERS
        GLFWwindow* window_;

		GraphicsContext* context_;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSyncEnabled = false;

			EventCallback EventCallback;
		};

		WindowData data_;
#pragma endregion PRIVATE_DATA_MEMBERS
	};
}
