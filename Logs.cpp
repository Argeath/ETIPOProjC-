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

