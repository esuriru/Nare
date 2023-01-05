#pragma once

#include "Nare/Events/Event.h"
#include "Nare/Mathf/Vector2.h"

namespace Nare
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		/// <summary>
		/// Constructor for window properties.
		/// </summary>
		/// <param name="title">: Title for window</param>
		/// <param name="width">: Window width</param>
		/// <param name="height">: Window height</param>
		WindowProps(
			std::string title = "Nare Engine",
			unsigned int width = 1280,
			unsigned int height = 720
			)
			: Title(std::move(title)), Width(width), Height(height)
		{}

	};

	class Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		inline virtual Vector2 GetSize()
		{
			return { GetWidth(), GetHeight() };
		}

		virtual void SetEventCallback(const EventCallback& cb) = 0;
		virtual void SetVSyncEnabled(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		virtual void* GetNativeWindow() const = 0;
		
		static Window* Create(const WindowProps& props = WindowProps());
	};
}
