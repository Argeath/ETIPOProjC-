#pragma once

namespace Engine {
	class Window {
		static Window* activeWindow;

	public:
		int t1, t2, quit, frames, rc;
		double delta, worldTime, fpsTimer, fps;
		SDL_Event event;
		SDL_Surface *screen;
		SDL_Texture *scrtex;
		SDL_Window *window;
		SDL_Renderer *renderer;
		DialogBox *dialogBox;
		ResourceManager* resourceManager;
		BaseGame* game;

		#ifdef DEBUG_MODE
		Debug *debug;
		#endif

		Window();
		~Window();

		int init();
		void loop();
		void renderWindow();
		void pollEvents();
		void quitWindow();
		void showWindow(DialogBoxType type);

		SDL_Surface* getCharset() const
		{
			return resourceManager->getResourceByName("charset")->source;
		}

		static Window* getActiveWindow() {
			return activeWindow;
		}

		void setActive() {
			activeWindow = this;
		}
	};
}
