#include "main.h"

using namespace Utils;
using namespace Engine;

Window* Window::activeWindow = nullptr;

Window::Window() : dialogBox(nullptr)
{
	quit = 0;

	logs = new Logs(this);
	game = new Game::World(this);
	game->init();
}

Window::~Window()
{
	if (dialogBox != nullptr)
		delete dialogBox;

	if (activeWindow == this)
		activeWindow = nullptr;

	if (game != nullptr)
		delete game;

	if(logs != nullptr)
		delete logs;
}

void Window::resize(Vector2<int> size)
{
	resize_term(((size.y < MAX_HEIGHT) ? size.y : MAX_HEIGHT) + 2 + LOG_LINES, ((size.x < MAX_WIDTH) ? size.x : MAX_WIDTH) * 2 + 4);

	int row, col;
	getmaxyx(stdscr, row, col);

	centerPosition = game->getSize() / 2;
	windowSize = V2(col, row - LOG_LINES);
	mapStart = V2(2, 1);
	mapEnd = windowSize - V2(2, 1);

	renderWindow();
}

int Window::init()
{
	initscr();
	resize(game->getSize());
	keypad(stdscr, true);
	noecho();

	hasColors = has_colors();

	if (hasColors)
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

	renderWindow();
	refresh();

	return 0;
}

void Window::loop()
{
	int input;
	game->render();

	showWindow(StartGame);
	refresh();

	while (!quit)
	{
		input = getch();
		if (dialogBox != nullptr)
		{
			dialogBox->render();
			dialogBox->handleKeys(input);
		}
		else
		{
			/*if (input == 'q')
				quitWindow();
			else*/
			if (input == 's')
				showWindow(InputFilenameSave);
			else if (input == 27)
				showWindow(StartGame);
			else if (input == ' ')
				((Game::World*)game)->player->castSpell();
			else if (input == KEY_UP || input == KEY_DOWN || input == KEY_LEFT || input == KEY_RIGHT)
				game->update(input);
		}
		refresh();
	}
	endwin();
}

void Window::renderWindow() const
{
	for (int iy = 0; iy < windowSize.y; iy++)
	{
		move(iy, 0);
		for (int ix = 0; ix < windowSize.x; ix++)
		{
			if (iy >= 1 && iy < windowSize.y - 1 && ix > 1 && ix < windowSize.x - 2) continue;
			if (iy >= 1 && iy < windowSize.y - 1 && ix > windowSize.x - 3) move(iy, ix);
			addch('#');
		}
	}
	for (int iy = windowSize.y; iy < windowSize.y + LOG_LINES; iy++)
	{
		move(iy, 0);
		for (int ix = 0; ix < windowSize.x; ix++)
			addch(' ');
	}
}

void closeDialogBox()
{
	Window::getActiveWindow()->killDialogBox();
	Window::getActiveWindow()->getGame()->render();
}

void finishGameSuccess()
{
	closeDialogBox();
	Window::getActiveWindow()->showWindow(InputMapSizeX);
}

void finishGameFailure()
{
	closeDialogBox();

	Window::getActiveWindow()->quitWindow();
}

void finishGameLoadSave()
{
	closeDialogBox();
	Window::getActiveWindow()->showWindow(InputFilenameLoad);
}

void inputFilenameLoadSuccess()
{
	Text filename = ((InputDialogBox*)Window::getActiveWindow()->getDialogBox())->getResultText();

	Window::getActiveWindow()->loadGame(filename);
	closeDialogBox();
}

void inputFilenameSaveSuccess()
{
	Text filename = ((InputDialogBox*)Window::getActiveWindow()->getDialogBox())->getResultText();

	Window::getActiveWindow()->saveGame(filename);
	Window::getActiveWindow()->getLogs()->addLog(T("File ") + filename + " saved.");
	closeDialogBox();
}

void inputMapSizeXSuccess()
{
	int number = ((InputNumbersDialogBox*)Window::getActiveWindow()->getDialogBox())->getResult();

	if(number < 20 || number > 60) {
		Window::getActiveWindow()->showWindow(InputMapSizeX);
	} else {
		Window::getActiveWindow()->newSize.x = number;
		Window::getActiveWindow()->showWindow(InputMapSizeY);
	}
}

void inputMapSizeYSuccess()
{
	int number = ((InputNumbersDialogBox*)Window::getActiveWindow()->getDialogBox())->getResult();
	if (number < 20 || number > 60) {
		Window::getActiveWindow()->showWindow(InputMapSizeY);
	}
	else {
		Window::getActiveWindow()->newSize.y = number;
		Window::getActiveWindow()->resize(Window::getActiveWindow()->newSize);

		delete Window::getActiveWindow()->getGame();
		Window::getActiveWindow()->setGame(new Game::World(Window::getActiveWindow(), Window::getActiveWindow()->newSize));
		Window::getActiveWindow()->getGame()->init();
		closeDialogBox();
	}
}

void Window::showWindow(DialogBoxType type)
{
	if (dialogBox != nullptr)
	{
		delete dialogBox;
		dialogBox = nullptr;
	}

	switch (type)
	{
	case FinishGame:
		{
			InfoDialogBox* box = new InfoDialogBox(this);
			box->setAnswer("Czy chcesz zagrac ponownie?");

			box->setYesKey('t');
			box->setYesText("Tak");
			box->setNoKey('n');
			box->setNoText("Nie");
			box->setThirdKey('l');
			box->setThirdText("Wczytaj");

			box->setSuccessCallback(&finishGameSuccess);
			box->setFailureCallback(&finishGameFailure);
			box->setThirdCallback(&finishGameLoadSave);

			dialogBox = box;
			break;
		}
	case StartGame:
		{
			InfoDialogBox* box = new InfoDialogBox(this);
			box->setAnswer("Witaj w SimulETIrze swiata!");

			box->setYesKey('t');
			box->setYesText("Nowa gra");
			box->setNoKey('q');
			box->setNoText("Wyjdz");
			box->setThirdKey('l');
			box->setThirdText("Wczytaj");

			box->setSuccessCallback(&finishGameSuccess);
			box->setFailureCallback(&finishGameFailure);
			box->setThirdCallback(&finishGameLoadSave);

			dialogBox = box;
			break;
		}
	case InputFilenameSave:
		{
			InputDialogBox* box = new InputDialogBox(this);
			box->setAnswer("Podaj nazwe pliku: ");

			box->setSuccessCallback(&inputFilenameSaveSuccess);
			box->setFailureCallback(&closeDialogBox);

			dialogBox = box;
			break;
		}
	case InputFilenameLoad:
		{
			InputDialogBox* box = new InputDialogBox(this);
			box->setAnswer("Podaj nazwe pliku: ");

			box->setSuccessCallback(inputFilenameLoadSuccess);
			box->setFailureCallback(closeDialogBox);

			dialogBox = box;
			break;
		}
	case InputMapSizeX:
		{
			InputNumbersDialogBox* box = new InputNumbersDialogBox(this);
			box->setAnswer("Podaj szerokosc mapy(20-60): ");

			box->setSuccessCallback(inputMapSizeXSuccess);
			box->setFailureCallback(closeDialogBox);

			dialogBox = box;
			break;
		}
	case InputMapSizeY:
		{
			InputNumbersDialogBox* box = new InputNumbersDialogBox(this);
			box->setAnswer("Podaj wysokosc mapy(20-60): ");

			box->setSuccessCallback(inputMapSizeYSuccess);
			box->setFailureCallback(closeDialogBox);

			dialogBox = box;
			break;
		}
	default: break;
	}
	if (dialogBox != nullptr)
		dialogBox->render();
	refresh();
}

void Window::printLogs() const
{
	for (int i = 0; i < LOG_LINES; i++)
		for (int ix = 0; ix < windowSize.x; ix++)
			mvaddch(windowSize.y + i, ix, ' ');

	for (int i = 0; i < logs->size(); i++)
		mvprintw(windowSize.y + i, 0, logs->at(i));
}

void Window::saveGame(Text filename) const
{
	std::ofstream file;
	file.open(filename + T(".map"), std::ios::out | std::ios::trunc | std::ios::binary);

	game->save(file);
	file.close();
}

void Window::loadGame(Utils::Text filename)
{
	std::ifstream file;
	file.open(filename + T(".map"), std::ios::in | std::ios::binary);

	try
	{
		if (!file.is_open())
			throw new LoadingMapException("File not found.");

		Game::World* world = Game::World::load(file, this);

		delete game;
		game = world;
	}
	catch (LoadingMapException* exception)
	{
		logs->addLog(T("Loading game failed: ") + exception->what());
		showWindow(StartGame);
	}
	file.close();
}

void Window::quitWindow()
{
	quit = true;
}

