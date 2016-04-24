#pragma once

namespace Engine
{
	class Window;

	class Logs
	{
	public:
		std::deque<Utils::Text> items;
		Window* window;

		Logs(Window* w) : window(w) {}

		void addLog(Utils::Text item);
	};
}