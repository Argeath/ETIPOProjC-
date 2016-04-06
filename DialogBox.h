#pragma once

namespace Engine {

	typedef void(*CallbackFunction)();

	class ADialogBox {
	public:
		virtual ~ADialogBox() {}

		Utils::Text answer;
		Utils::Vector2<int> size;
		CallbackFunction successCallback;
		CallbackFunction failureCallback;

		ADialogBox() : size(V2(600, 60)), successCallback(nullptr), failureCallback(nullptr) {}

		virtual void handleKeys(char key) = 0;
		virtual void render() = 0;
		void renderWindow() const;
		void closeWindow();
	};

	class InputDialogBox : public ADialogBox {
	public:
		Utils::Text inputText;
		int limitCharacters;

		InputDialogBox() : limitCharacters(15) {}

		void handleKeys(char key) override;
		void render() override;
	};

	class InfoDialogBox : public ADialogBox {
	public:
		char yesKey, noKey, thirdKey;
		Utils::Text yesText, noText, thirdText;

		CallbackFunction thirdCallback;

		InfoDialogBox() {}

		void handleKeys(char key) override;
		void render() override;
	};

	enum DialogBoxType {
		FinishGame, Info, InputNameToRanking
	};
}