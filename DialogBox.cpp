#include "main.h"

using namespace Utils;
using namespace Engine;

void DialogBox::renderWindow() const
{
	DrawRectangle((SCREEN_WIDTH - size.x) / 2, (SCREEN_HEIGHT - size.y) / 2, size.x, size.y, Color::fioletowy, Color::prawieCzarny);
}

void DialogBox::closeWindow() {
	if (Window::getActiveWindow()->dialogBox == this) {
		Window::getActiveWindow()->dialogBox = nullptr;
		delete this;
	}
}

void InputDialogBox::handleKeys(SDL_Keycode key) {
	if (inputText.length() < limitCharacters && ((key >= SDLK_0 && key <= SDLK_9) || (key >= SDLK_a && key <= SDLK_z) || key == SDLK_UNDERSCORE || key == SDLK_PERIOD || key == SDLK_MINUS)) {
		inputText += const_cast<char*>(SDL_GetKeyName(key));
	}
	else if (key == SDLK_BACKSPACE) {
		inputText.clearLastChar();
	}
	else if (key == SDLK_RETURN) {
		successCallback();
		closeWindow();
	}
	else if (key == SDLK_ESCAPE) {
		failureCallback();
		closeWindow();
	}
}

void InputDialogBox::render() {
	renderWindow();

	DrawString((SCREEN_WIDTH - size.x) / 2 + 20, (SCREEN_HEIGHT - size.y) / 2 + 20, answer);
	DrawString(SCREEN_WIDTH / 2 - 30, (SCREEN_HEIGHT - size.y) / 2 + 40, inputText);
	DrawString((SCREEN_WIDTH - size.x) / 2 + 20, (SCREEN_HEIGHT + size.y) / 2 - 15, "[Enter] Zatwierdz");
	DrawString((SCREEN_WIDTH + size.x) / 2 - 120, (SCREEN_HEIGHT + size.y) / 2 - 15, "[Esc] Odrzuc");
}

void InfoDialogBox::render() {
	renderWindow();

	DrawString((SCREEN_WIDTH - size.x) / 2 + 20, (SCREEN_HEIGHT - size.y) / 2 + 20, answer);

	if (!yesText.isEmpty())
		DrawString((SCREEN_WIDTH - size.x) / 2 + 20, (SCREEN_HEIGHT + size.y) / 2 - 15, T("[") + T(SDL_GetKeyName(yesKey)) + T("] ") + yesText);
	
	if (!noText.isEmpty())
		DrawString((SCREEN_WIDTH + size.x) / 2 - 70, (SCREEN_HEIGHT + size.y) / 2 - 15, T("[") + T(SDL_GetKeyName(noKey)) + T("] ") + noText);
	
	if( ! thirdText.isEmpty())
		DrawString(SCREEN_WIDTH / 2 - 40, (SCREEN_HEIGHT + size.y) / 2 - 15, T("[") + T(SDL_GetKeyName(thirdKey)) + T("] ") + thirdText);
}

void InfoDialogBox::handleKeys(SDL_Keycode key) {
	if (!yesText.isEmpty() && key == yesKey)
		successCallback();
	else if (!noText.isEmpty() && key == noKey)
		failureCallback();
	else if (!thirdText.isEmpty() && key == thirdKey)
		thirdCallback();
}