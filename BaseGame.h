#pragma once

namespace Engine
{
	class Window;

	class BaseGame
	{
	protected:
		Window* window;
		Utils::Vector2<int> size;
	public:

		virtual ~BaseGame()
		{
		}

		BaseGame(Window* win) : window(win)
		{
			size = V2(30, 30);
		}

		Window* getWindow() const
		{
			return window;
		}

		Utils::Vector2<int> getSize() const
		{
			return size;
		}

		virtual void init() = 0;
		virtual void update(int input) = 0;
		virtual void render() = 0;
		virtual void save(std::ofstream& _out) = 0;
	};
}

