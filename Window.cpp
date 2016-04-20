#include "main.h"

using namespace Utils;
using namespace Engine;

Window* Window::activeWindow = nullptr;

Window::Window() : dialogBox(nullptr) {
	quit = worldTime = 0;

	game = new Game::World(this);
}

Window::~Window() {

	if (dialogBox != nullptr)
		delete dialogBox;

	if(activeWindow == this)
		activeWindow = nullptr;

	if (game != nullptr)
		delete game;
}

int Window::init() {
	initscr();
	resize_term(((MAP_HEIGHT < MAX_HEIGHT) ? MAP_HEIGHT : MAX_HEIGHT) + 2, ((MAP_WIDTH < MAX_WIDTH) ? MAP_WIDTH : MAX_WIDTH) * 2 + 4);
	keypad(stdscr, true);
	noecho();

	hasColors = has_colors();

	if(hasColors)
	{
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_GREEN);
		init_pair(3, COLOR_RED, COLOR_GREEN);
		init_pair(4, COLOR_MAGENTA, COLOR_GREEN);
		init_pair(5, COLOR_YELLOW, COLOR_GREEN);
		init_pair(6, COLOR_WHITE, COLOR_RED);
		init_pair(7, COLOR_BLACK, COLOR_YELLOW);
		init_pair(8, COLOR_BLACK, COLOR_WHITE);
		init_pair(9, COLOR_CYAN, COLOR_YELLOW);
	}

	int row, col;
	getmaxyx(stdscr, row, col);

	centerPosition = V2(MAP_WIDTH / 2, MAP_HEIGHT / 2);
	windowSize = V2(col, row);
	mapStart = V2(2, 1);
	mapEnd = windowSize - V2(2, 1);

	renderWindow();
	refresh();

	return 0;
}

void Window::loop() {
	int input;
	game->render();
	refresh();

	while (!quit) {
		input = getch();
		if (dialogBox != nullptr)
			dialogBox->handleKeys(input);
		else
		{
			if (input == 'q')
				quitWindow();
		}
		game->update();
		refresh();
	}
	endwin();
}

void Window::renderWindow() {
	for (int iy = 0; iy < windowSize.y; iy++) {
		move(iy, 0);
		for (int ix = 0; ix < windowSize.x; ix++) {
			if (iy >= 1 && iy < windowSize.y - 1 && ix > 1 && ix < windowSize.x - 2) continue;
			if (iy >= 1 && iy < windowSize.y - 1 && ix > windowSize.x - 3) move(iy, ix);
			addch('#');
		}
	}
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