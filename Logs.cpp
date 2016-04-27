#include "main.h"

using namespace Engine;
using namespace Utils;

void Logs::addLog(Text item)
{
	if (items.size() >= LOG_LINES)
		items.pop_front();

	items.push_back(item);

	window->printLogs();
	refresh();
}

void Logs::save(std::ofstream& _out)
{
	//_out << items.size();
	io::write(_out, items.size());
	for (int i = 0; i < items.size(); i++)
	{
		int length = items.at(i).length();
		io::write(_out, length);
		io::writeString(_out, (char*)items.at(i));
	}
}

void Logs::load(std::ifstream& _in)
{
	int amount;
	io::read(_in, amount);

	for (int i = 0; i < amount; i++)
	{
		int length;
		io::read(_in, length);

		char* tmp = new char[length];
		io::readString(_in, tmp);
		tmp[length] = '\0';
		addLog(tmp);
	}
}

