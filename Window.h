#pragma once

namespace Engine
{
	class Window
	{
		static Window* activeWindow;

		int quit;
		Logs* logs;
		bool hasColors;
		BaseGame* game;
		ADialogBox* dialogBox;
		Utils::Vector2<int> mapEnd;
		Utils::Vector2<int> mapStart;
		Utils::Vector2<int> windowSize;
		Utils::Vector2<int> centerPosition;
	public:
		Utils::Text inputFilename;

		Utils::Vector2<int> newSize;


		Window();
		~Window();
		int init();
		void loop();
		void renderWindow() const;
		void quitWindow();
		void resize(Utils::Vector2<int> size);
		void showWindow(DialogBoxType type);
		void printLogs() const;

		void saveGame(Utils::Text filename) const;
		void loadGame(Utils::Text filename);

		Logs* getLogs() const
		{
			return logs;
		}

		BaseGame* getGame() const
		{
			return game;
		}

		void setGame(BaseGame* g)
		{
			game = g;
		}

		ADialogBox* getDialogBox() const
		{
			return dialogBox;
		}

		void killDialogBox()
		{
			if (dialogBox == nullptr) return;

			dialogBox->closeWindow();
			dialogBox = nullptr;
		}

		Utils::Vector2<int> getMapEnd() const
		{
			return mapEnd;
		}

		Utils::Vector2<int> getMapStart() const
		{
			return mapStart;
		}

		Utils::Vector2<int> getWindowSize() const
		{
			return windowSize;
		}

		Utils::Vector2<int> getCenterPos() const
		{
			return centerPosition;
		}

		void setCenterPos(Utils::Vector2<int> pos)
		{
			centerPosition = pos;
		}

		static Window* getActiveWindow()
		{
			return activeWindow;
		}

		void setActive()
		{
			activeWindow = this;
		}
	};
}

