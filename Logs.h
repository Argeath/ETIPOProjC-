#pragma once

namespace Engine
{
	class Window;

	class Logs
	{
		std::deque<Utils::Text> items;
		Window* window;

	public:
		Logs(Window* w) : window(w)
		{
		}

		~Logs()
		{
			items.clear();
		}

		int size() const
		{
			return items.size();
		}

		Utils::Text at(int i) const
		{
			return items.at(i);
		}

		void addLog(Utils::Text item);
		void save(std::ofstream& _out);
		void load(std::ifstream& _in);
	};
}

