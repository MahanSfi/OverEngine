#pragma once

#include "OverEngine/Core/Core.h"

#include "KeyCodes.h"

namespace OverEngine
{
	class OVER_API Input
	{
	protected:
		Input() = delete;
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(KeyCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}