#include "main.h"

using namespace Utils;
using namespace Engine;

Window* Window::activeWindow = nullptr;

Window::Window() : dialogBox(nullptr) {
	quit = worldTime = 0;

	logs = new Logs(this);
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
	resize_term(((MAP_HEIGHT < MAX_HEIGHT) ? MAP_HEIGHT : MAX_HEIGHT) + 2 + LOG_LINES, ((MAP_WIDTH < MAX_WIDTH) ? MAP_WIDTH : MAX_WIDTH) * 2 + 4);
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
		init_pair(10, COLOR_WHITE, COLOR_MAGENTA);
	}

	int row, col;
	getmaxyx(stdscr, row, col);

	centerPosition = V2(MAP_WIDTH / 2, MAP_HEIGHT / 2);
	windowSize = V2(col, row - LOG_LINES);
	mapStart = V2(2, 1);
	mapEnd = windowSize - V2(2, 1);

	renderWindow();
	refresh();

	return 0;
}

void Window::loop() {
	int input;
	game->render();

	showWindow(StartGame);
	refresh();

	while (!quit) {
		input = getch();
		if (dialogBox != nullptr) {
			dialogBox->render();
			dialogBox->handleKeys(input);
		}
		else
		{
			if (input == 'q')
				quitWindow();
			else
				game->update(input);
		}
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
	delete Window::getActiveWindow()->game;
	Window::getActiveWindow()->game = new Game::World(Window::getActiveWindow());

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
		InfoDialogBox* box = new InfoDialogBox(this);
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
	case StartGame: {
		InfoDialogBox* box = new InfoDialogBox(this);
		box->answer = "Witaj w SimulETIrze swiata!";
		box->yesKey = 't';
		box->yesText = "Nowa gra";
		box->noKey = 'q';
		box->noText = "Wyjdz";
		box->thirdKey = 'l';
		box->thirdText = "Wczytaj";
		
		box->failureCallback = &finishGameFailure;
		box->successCallback = &finishGameSuccess;
		box->thirdCallback = &finishGameLoadSave; // TODO: Wczytaj gre

		dialogBox = box;
		break;
	}
	}
	if(dialogBox != nullptr)
		dialogBox->render();
	refresh();
}

void Window::printLogs()
{
	for (int i = 0; i < LOG_LINES; i++)
		for (int ix = 0; ix < windowSize.x; ix++)
			mvaddch(windowSize.y + i, ix, ' ');

	for (int i = 0; i < logs->items.size(); i++)
		mvprintw(windowSize.y + i, 0, "%d: %s", logs->items.size(), logs->items[i]);
}

void Window::quitWindow() {
	quit = true;
}
