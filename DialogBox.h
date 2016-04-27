#pragma once

namespace Engine
{
	class Window;
	typedef void (*CallbackFunction)();

	class ADialogBox
	{
	protected:
		Window* window;
		Utils::Text answer;
		CallbackFunction successCallback;
		CallbackFunction failureCallback;
	public:
		virtual ~ADialogBox()
		{
		}


		ADialogBox(Window* w) : window(w), successCallback(nullptr), failureCallback(nullptr)
		{
		}

		void setAnswer(Utils::Text str)
		{
			answer = str;
		}

		void setSuccessCallback(CallbackFunction func)
		{
			successCallback = func;
		}

		void setFailureCallback(CallbackFunction func)
		{
			failureCallback = func;
		}

		virtual void handleKeys(char key) = 0;
		virtual void render() = 0;

		void renderWindow() const;
		void closeWindow();
	};

	class InputDialogBox : public ADialogBox
	{
	protected:
		int limitCharacters;
		Utils::Text inputText;
	public:

		InputDialogBox(Window* w) : ADialogBox(w), limitCharacters(15)
		{
		}

		void setLimitCharacters(int value)
		{
			limitCharacters = value;
		}

		Utils::Text getResultText() const
		{
			return inputText;
		}

		void handleKeys(char key) override;
		void render() override;
	};

	class InputNumbersDialogBox : public InputDialogBox
	{
		int number;
	public:

		InputNumbersDialogBox(Window* w) : InputDialogBox(w), number(0)
		{
		}

		int getResult() const
		{
			return number;
		}

		void handleKeys(char key) override;
		void render() override;
	};

	class InfoDialogBox : public ADialogBox
	{
	protected:
		char yesKey, noKey, thirdKey;
		Utils::Text yesText, noText, thirdText;

		CallbackFunction thirdCallback;
	public:
		InfoDialogBox(Window* w) : ADialogBox(w), yesKey(0), noKey(0), thirdKey(0), thirdCallback(nullptr)
		{
		}

		void setYesKey(char k)
		{
			yesKey = k;
		}

		void setNoKey(char k)
		{
			noKey = k;
		}

		void setYesText(Utils::Text str)
		{
			yesText = str;
		}

		void setNoText(Utils::Text str)
		{
			noText = str;
		}

		void setThirdKey(char k)
		{
			thirdKey = k;
		}

		void setThirdText(Utils::Text str)
		{
			thirdText = str;
		}

		void setThirdCallback(CallbackFunction func)
		{
			thirdCallback = func;
		}

		void handleKeys(char key) override;
		void render() override;
	};

	enum DialogBoxType
	{
		FinishGame,
		StartGame,
		InputFilenameSave,
		InputFilenameLoad,
		InputMapSizeX,
		InputMapSizeY
	};
}

