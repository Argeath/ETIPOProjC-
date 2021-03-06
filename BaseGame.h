#pragma once

namespace Engine
{
	class Window;

	class BaseGame
	{
	public:
		Window* window;

		virtual ~BaseGame() {}

		BaseGame(Window* win) : window(win) {}

		virtual void update(double deltaTime) = 0;
		virtual void render() = 0;
	};
}
