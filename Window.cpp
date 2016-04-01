#include "main.h"

using namespace Utils;
using namespace Engine;

Window* Window::activeWindow = nullptr;

text_info* getTextInfo() {
	text_info* info = new text_info;
	gettextinfo(info);
	return info;
}

void Window::clearWindow()
{
	text_info* info = getTextInfo();

	for (int y = 1; y < info->screenheight; y++) {
		for (int x = 1; x < info->screenwidth; x++) {
			gotoxy(x, y);
			putch(' ');
		}
	}
	delete info;
}


Window::Window() : dialogBox(nullptr) {
	quit = worldTime = 0;

	game = new Game::World(this);
}

Window::~Window() {

	if (dialogBox != nullptr)
		delete dialogBox;

	if(activeWindow == this)
		activeWindow = nullptr;
}

int Window::init() {
	

	return 0;
}

void Window::loop() {
	int input;

	while (!quit) {
		if (kbhit() != 0)
		{
			input = getch();
			if (dialogBox != nullptr)
				dialogBox->handleKeys(input);
			else
			{
				if (input == 'q')
					quitWindow();

			}
		}
	}
}

void Window::renderWindow() {
	
}

void finishGameSuccess() {
	//delete Window::getInstance()->game;
	//Window::getInstance()->game = new World();

	delete Window::getActiveWindow()->dialogBox;
	Window::getActiveWindow()->dialogBox = nullptr;
}

void finishGameFailure() {
	delete Window::getActiveWindow()->dialogBox;
	Window::getActiveWindow()->dialogBox = nullptr;

	Window::getActiveWindow()->quitWindow();
}

void finishGameLoadSave() {
	//Window::getInstance()->game->loadGame();

	delete Window::getActiveWindow()->dialogBox;
	Window::getActiveWindow()->dialogBox = nullptr;
}

void Window::showWindow(DialogBoxType type) {
	switch (type) {
	case FinishGame: {
		InfoDialogBox* box = new InfoDialogBox();
		box->answer = "Czy chcesz zagrac ponownie?";
		box->size.x = 300;

		box->yesKey = 't';
		box->yesText = "Tak";
		box->noKey = 'n';
		box->noText = "Nie";
		box->thirdKey = 'l';
		box->thirdText = "Wczytaj";

		box->successCallback = &finishGameSuccess;
		box->failureCallback = &finishGameFailure;
		box->thirdCallback = &finishGameLoadSave;

		dialogBox = box;
		break;
	}
	/*case InputNameToRanking: {

		InputDialogBox* box = new InputDialogBox();
		box->answer = T("Zdobyles ") + T(game->points) + " punktow i osiagnales " + T(ranking->getPlace(game->points)) + " miejsce. Podaj imie:";
		box->size.x = 500;
		box->size.y = 80;

		box->successCallback = &rankingSuccess;
		box->failureCallback = &rankingFailure;

		dialogBox = box;
		break;
	}*/
	}
}

void Window::quitWindow() {
	quit = true;
}