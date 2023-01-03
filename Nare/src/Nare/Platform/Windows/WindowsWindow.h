#pragma once

#include "Nare/Window.h"

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

#pragma endregion INLINE_FUNCTIONS

	private:
#pragma region PRIVATE_FUNCTIONS
		virtual void Init(const WindowProps& props);
		virtual void Exit();
#pragma endregion PRIVATE_FUNCTIONS

#pragma region PRIVATE_DATA_MEMBERS
		GLFWwindow* gl_window_{};

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSyncEnabled;

			EventCallback EventCallback;
		};

		WindowData data_;
#pragma endregion PRIVATE_DATA_MEMBERS
	};
}
