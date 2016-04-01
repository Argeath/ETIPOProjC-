#include "main.h"

using namespace Utils;
using namespace Engine;

void DialogBox::renderWindow() const
{

}

void DialogBox::closeWindow() {
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
	/*
	DrawString((SCREEN_WIDTH - size.x) / 2 + 20, (SCREEN_HEIGHT - size.y) / 2 + 20, answer);
	DrawString(SCREEN_WIDTH / 2 - 30, (SCREEN_HEIGHT - size.y) / 2 + 40, inputText);
	DrawString((SCREEN_WIDTH - size.x) / 2 + 20, (SCREEN_HEIGHT + size.y) / 2 - 15, "[Enter] Zatwierdz");
	DrawString((SCREEN_WIDTH + size.x) / 2 - 120, (SCREEN_HEIGHT + size.y) / 2 - 15, "[Esc] Odrzuc");
	*/
}

void InfoDialogBox::render() {
	renderWindow();
	/*
	DrawString((SCREEN_WIDTH - size.x) / 2 + 20, (SCREEN_HEIGHT - size.y) / 2 + 20, answer);

	if (!yesText.isEmpty())
		DrawString((SCREEN_WIDTH - size.x) / 2 + 20, (SCREEN_HEIGHT + size.y) / 2 - 15, T("[") + T(SDL_GetKeyName(yesKey)) + T("] ") + yesText);
	
	if (!noText.isEmpty())
		DrawString((SCREEN_WIDTH + size.x) / 2 - 70, (SCREEN_HEIGHT + size.y) / 2 - 15, T("[") + T(SDL_GetKeyName(noKey)) + T("] ") + noText);
	
	if( ! thirdText.isEmpty())
		DrawString(SCREEN_WIDTH / 2 - 40, (SCREEN_HEIGHT + size.y) / 2 - 15, T("[") + T(SDL_GetKeyName(thirdKey)) + T("] ") + thirdText);*/
}

void InfoDialogBox::handleKeys(char key) {
	if (!yesText.isEmpty() && key == yesKey)
		successCallback();
	else if (!noText.isEmpty() && key == noKey)
		failureCallback();
	else if (!thirdText.isEmpty() && key == thirdKey)
		thirdCallback();
}