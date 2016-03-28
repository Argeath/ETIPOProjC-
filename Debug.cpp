#include "main.h"

using namespace Utils;
using namespace Engine;
using namespace std;

#ifdef DEBUG_MODE
void Debug::drawDebugElements()
{
	for (list<DebugElement*>::iterator iter = debugElements.begin(); iter != debugElements.end(); iter++)
	{
		(*iter)->debug();
	}
}
#endif