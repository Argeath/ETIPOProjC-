#pragma once

namespace Engine {
	class Window {
		static Window* activeWindow;

		char windowTab[20][20];

	public:
		int quit;
		double worldTime;
		DialogBox *dialogBox;
		BaseGame* game;

		Window();
		~Window();

		int init();
		void loop();
		void renderWindow();
		void pollEvents();
		void quitWindow();
		void showWindow(DialogBoxType type);

		static void clearWindow();

		static Window* getActiveWindow() {
			return activeWindow;
		}

		void setActive() {
			activeWindow = this;
		}
	};
}
