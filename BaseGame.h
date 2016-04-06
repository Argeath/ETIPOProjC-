#pragma once

namespace Engine
{
	class Window;

	class BaseGame
	{
	public:
		Window* window;
		char** buffer;

		virtual ~BaseGame()
		{
			for (int i = 0; i < MAP_HEIGHT; i++)
				delete[] buffer[i];
			delete[] buffer;
		}

		BaseGame(Window* win) : window(win)
		{
			buffer = new char*[MAP_HEIGHT];
			for (int i = 0; i < MAP_HEIGHT; i++)
				buffer[i] = new char[MAP_WIDTH];
		}

		virtual void update() = 0;
		virtual void render() = 0;
	};
}
