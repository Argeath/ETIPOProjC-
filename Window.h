#pragma once

namespace Engine {
	class Window {
		static Window* activeWindow;

		char windowTab[20][20];

	public:
		int quit;
		double worldTime;
		ADialogBox *dialogBox;
		BaseGame* game;
		Logs* logs;
		bool hasColors;

		Utils::Vector2<int> windowSize;
		Utils::Vector2<int> centerPosition;
		Utils::Vector2<int> mapStart;
		Utils::Vector2<int> mapEnd;

		Window();
		~Window();

		int init();
		void loop();
		void renderWindow();
		void quitWindow();
		void showWindow(DialogBoxType type);
		void printLogs();

		static Window* getActiveWindow() {
			return activeWindow;
		}

		void setActive() {
			activeWindow = this;
		}
	};
}
