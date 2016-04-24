#include "main.h"

using namespace Utils;
using namespace Engine;

void ADialogBox::renderWindow() const
{
	Vector2<int> s = window->windowSize;
	for (int iy = s.y / 2 - 5; iy < s.y / 2 + 5; iy++) {
		for (int ix = 5; ix < s.x - 5; ix++) {
			if (iy == s.y / 2 - 5 || iy == s.y / 2 + 4 || ix == 5 || ix == s.x - 6)
				mvaddch(iy, ix, '@');
			else
				mvaddch(iy, ix, ' ');
		}
	}
	refresh();
}

void ADialogBox::closeWindow() {
	if (Window::getActiveWindow()->dialogBox == this) {
		Window::getActiveWindow()->dialogBox = nullptr;
		delete this;
	}
}

void InputDialogBox::handleKeys(char key) {
	if (inputText.length() < limitCharacters && ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z') || key == '_' || key == '.' || key == '-')) {
		inputText += key;
	}
	else if (key == 8) {
		inputText.clearLastChar();
	}
	else if (key == 13) {
		successCallback();
		closeWindow();
	}
	else if (key == 27) {
		failureCallback();
		closeWindow();
	}
}

void InputDialogBox::render() {
	renderWindow();

	mvprintw(window->windowSize.y / 2 - 3, window->windowSize.x / 2 - 15, answer);
	mvprintw(window->windowSize.y / 2 - 1, window->windowSize.x / 2 - 5, inputText);
	mvprintw(window->windowSize.y / 2 + 3, 8, "[Enter] Zatwierdz");
	mvprintw(window->windowSize.y / 2 + 3, window->windowSize.x - 10, "[Esc] Odrzuc");
}

void InfoDialogBox::render() {
	renderWindow();


	mvprintw(window->windowSize.y / 2 - 2, window->windowSize.x / 2 - 15, answer);
	if(!yesText.isEmpty())
		mvprintw(window->windowSize.y / 2 + 3, 7, "[%c] %s", yesKey, yesText);
	
	if(!noText.isEmpty())
		mvprintw(window->windowSize.y / 2 + 3, window->windowSize.x - 16, "[%c] %s", noKey, noText);

	if(!thirdText.isEmpty())
		mvprintw(window->windowSize.y / 2 + 2, window->windowSize.x / 2 - 5, "[%c] %s", thirdKey, thirdText);
}

void InfoDialogBox::handleKeys(char key) {
	if (!yesText.isEmpty() && key == yesKey)
		successCallback();
	else if (!noText.isEmpty() && key == noKey)
		failureCallback();
	else if (!thirdText.isEmpty() && key == thirdKey)
		thirdCallback();
}