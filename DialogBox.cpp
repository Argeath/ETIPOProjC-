#include "main.h"

using namespace Utils;
using namespace Engine;

void ADialogBox::renderWindow() const
{
	Vector2<int> s = window->getWindowSize();
	for (int iy = s.y / 2 - 5; iy < s.y / 2 + 5; iy++)
		for (int ix = 5; ix < s.x - 5; ix++)
			if (iy == s.y / 2 - 5 || iy == s.y / 2 + 4 || ix == 5 || ix == s.x - 6)
				mvaddch(iy, ix, '@');
			else
				mvaddch(iy, ix, ' ');
	refresh();
}

void ADialogBox::closeWindow()
{
	if (Window::getActiveWindow()->getDialogBox() == this)
	{
		delete this;
	}
}

void InputDialogBox::handleKeys(char key)
{
	if (inputText.length() < limitCharacters && ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z') || key == '_' || key == '.' || key == '-'))
	{
		inputText += key;
	}
	else if (key == 8)
	{
		inputText.clearLastChar();
	}
	else if (key == 13 || key == 10)
	{
		successCallback();
		return;
	}
	else if (key == 27)
	{
		failureCallback();
		return;
	}
	render();
}

void InputDialogBox::render()
{
	renderWindow();

	Vector2<int> s = window->getWindowSize();

	mvprintw(s.y / 2 - 3, s.x / 2 - 15, answer);
	mvprintw(s.y / 2 - 1, s.x / 2 - 5, inputText);
	mvprintw(s.y / 2 + 3, 7, "[Enter] Zatwierdz");
	mvprintw(s.y / 2 + 3, s.x - 20, "[Esc] Odrzuc");
}

void InputNumbersDialogBox::handleKeys(char key)
{
	if (inputText.length() < limitCharacters && (key >= '0' && key <= '9'))
	{
		inputText += key;
	}
	else if (key == 8)
	{
		inputText.clearLastChar();
	}
	else if (key == 13 || key == 10)
	{
		number = atoi(inputText);
		successCallback();
		return;
	}
	else if (key == 27)
	{
		failureCallback();
		return;
	}
	render();
}

void InputNumbersDialogBox::render()
{
	InputDialogBox::render();
}

void InfoDialogBox::render()
{
	renderWindow();

	Vector2<int> s = window->getWindowSize();

	mvprintw(s.y / 2 - 2, s.x / 2 - 15, answer);

	if (yesKey != 0)
		mvprintw(s.y / 2 + 3, 7, "[%c] %s", yesKey, yesText);

	if (noKey != 0)
		mvprintw(s.y / 2 + 3, s.x - 16, "[%c] %s", noKey, noText);

	if (thirdKey != 0)
		mvprintw(s.y / 2 + 2, s.x / 2 - 5, "[%c] %s", thirdKey, thirdText);
}

void InfoDialogBox::handleKeys(char key)
{
	if (!yesText.isEmpty() && key == yesKey)
		successCallback();
	else if (!noText.isEmpty() && key == noKey)
		failureCallback();
	else if (!thirdText.isEmpty() && key == thirdKey)
		thirdCallback();
}

