#pragma once

#include "Nare/Core/Core.h"
#include "Nare/Mathf/Vector2.h"

namespace Nare
{
	class Input
	{
	public:
		inline static bool GetKeyDown(int keycode)
		{
			return s_instance_->get_key_down_(keycode);
		}

		inline static bool GetMouseButtonDown(int button)
		{
			return s_instance_->get_mouse_button_down_(button);
		}

		inline static Vector2 GetMousePosition()
		{
			return s_instance_->get_mouse_position_();
		}

		// Internal functions
	protected:
		virtual bool get_key_down_(int keycode) = 0;
		virtual bool get_mouse_button_down_(int button) = 0;
		virtual Vector2 get_mouse_position_() = 0;

	private:
		static Input* s_instance_;
	};
}
