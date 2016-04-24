#pragma once

namespace Engine {
	class Window;
	typedef void(*CallbackFunction)();

	class ADialogBox {
	public:
		virtual ~ADialogBox() {}

		Window* window;
		Utils::Text answer;
		Utils::Vector2<int> size;
		CallbackFunction successCallback;
		CallbackFunction failureCallback;

		ADialogBox(Window* w) : window(w), size(V2(600, 60)), successCallback(nullptr), failureCallback(nullptr) {}

		virtual void handleKeys(char key) = 0;
		virtual void render() = 0;
		void renderWindow() const;
		void closeWindow();
	};

	class InputDialogBox : public ADialogBox {
	public:
		Utils::Text inputText;
		int limitCharacters;

		InputDialogBox(Window* w) : ADialogBox(w), limitCharacters(15) {}

		void handleKeys(char key) override;
		void render() override;
	};

	class InfoDialogBox : public ADialogBox {
	public:
		char yesKey, noKey, thirdKey;
		Utils::Text yesText, noText, thirdText;

		CallbackFunction thirdCallback;

		InfoDialogBox(Window* w) : ADialogBox(w) {}

		void handleKeys(char key) override;
		void render() override;
	};

	enum DialogBoxType {
		FinishGame, Info, StartGame
	};
}