#include "main.h"

using namespace Utils;
using namespace Engine;

Window* Window::activeWindow = nullptr;

Window::Window() : dialogBox(nullptr) {
	frames = fpsTimer = fps = quit = worldTime = delta = t1 = t2 = rc = 0;
	screen = nullptr;
	scrtex = nullptr;
	window = nullptr;
	renderer = nullptr;

	resourceManager = new ResourceManager;
	game = nullptr;

	#ifdef DEBUG_MODE
	debug = new Debug();
	#endif
}

Window::~Window() {

	if (dialogBox != nullptr)
		delete dialogBox;

	#ifdef DEBUG_MODE
	delete debug;
	#endif

	if(activeWindow == this)
		activeWindow = nullptr;
}

int Window::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf( "SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}
	int flags = IMG_INIT_PNG;
	if (IMG_Init(IMG_INIT_PNG) & flags != flags) {
		printf("IMG_Init error: %s\n", IMG_GetError());
		return 1;
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "POGame - Dominik Kinal 160589");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	Color::init(screen);

	printf("abc");
	// wczytanie obrazka cs8x8.bmp
	try {
		int charsetId = resourceManager->AddResource("./images/cs8x8.bmp", "charset");

		SDL_SetColorKey(resourceManager->getResourceByIndex(charsetId)->source, true, 0x000000);

		resourceManager->AddResource("./images/grass.png", "grass");
		resourceManager->AddResource("./images/guarana.png", "guarana");
		resourceManager->AddResource("./images/wolfberry.png", "wolfberry");
		resourceManager->AddResource("./images/mlecz.png", "mlecz");
		resourceManager->AddResource("./images/wolf.png", "wolf");
		resourceManager->AddResource("./images/sheep.png", "sheep");
		resourceManager->AddResource("./images/sheep.png", "turtle");
		resourceManager->AddResource("./images/antelope.png", "antelope");
		resourceManager->AddResource("./images/knight.png", "knight");
	} catch(ResourceNotLoadedException ex)
	{
		printf("Exception: %s\n", ex.what());
		quitWindow();
		return 1;
	}

	t1 = SDL_GetTicks();

	printf("abc");

	return 0;
}

void Window::loop() {
	while (!quit) {
		t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		delta = (t2 - t1) * 0.001;
		t1 = t2;

		worldTime += delta;

		SDL_FillRect(screen, nullptr, Color::czarny);

		fpsTimer += delta;
		if (fpsTimer > 0.3) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.3;
		}

		DrawRectangle(0, 0, GAME_WIDTH, GAME_HEIGHT, Color::trawiasty, Color::trawiasty);

		DrawLine(0, 100, GAME_WIDTH, 1, 0, Color::czerwony);
		DrawLine(100, 0, GAME_HEIGHT, 0, 1, Color::czerwony);
		DrawSurface(resourceManager->getResourceByName("grass")->source, 100, 100);

		if (game != nullptr) {
			game->update(delta);

			game->render(screen, resourceManager);

			renderWindow();

			#ifdef DEBUG_MODE
			debug->drawDebugElements();
			#endif
		}

		if(dialogBox != nullptr)
			dialogBox->render();

		SDL_UpdateTexture(scrtex, nullptr, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, nullptr, nullptr);
		SDL_RenderPresent(renderer);

		pollEvents();
		
		frames++;
	}
}

void Window::renderWindow() {
	
}

void finishGameSuccess() {
	//delete Window::getInstance()->game;
	//Window::getInstance()->game = new Game();

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

		box->yesKey = SDLK_t;
		box->yesText = "Tak";
		box->noKey = SDLK_n;
		box->noText = "Nie";
		box->thirdKey = SDLK_l;
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

void Window::pollEvents() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN: {
			if (dialogBox != nullptr) dialogBox->handleKeys(event.key.keysym.sym);
			else if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
			//else game->handleKeys(event.key.keysym.sym);
			break;
		}
		case SDL_KEYUP:
			break;
		case SDL_QUIT:
			quit = 1;
			break;
		}
	}
}

void Window::quitWindow() {
	quit = true;

	delete resourceManager;

	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}