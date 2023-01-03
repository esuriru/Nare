#pragma once

#include "Nare/Input.h"

namespace Nare
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool get_key_down_(int keycode) override;
		virtual bool get_mouse_button_down_(int button) override;
		virtual Vector2 get_mouse_position_() override;

	};
}