#pragma once

#define T(a) Utils::Text(a)

namespace Utils
{
	class Text
	{
	private:
		char* string;

	public:
		Text();
		Text(int i);
		Text(char c);
		Text(const char* str);
		Text(char* str);
		Text(const Text& str);

		~Text();

		void clear();
		void clearLastChar();

		int length() const;
		bool isEmpty() const;

		Text& operator=(const Text& obj)
		{
			cpy(obj.string);
			return *this;
		}

		Text& operator=(char* str)
		{
			cpy(str);
			return *this;
		}

		Text& operator+(const Text& str)
		{
			cat(str.string);
			return *this;
		}

		Text& operator+=(const Text& str)
		{
			cat(str.string);
			return *this;
		}

		Text& operator+(char* str)
		{
			cat(str);
			return *this;
		}

		friend bool operator==(const Text& t1, const Text& t2)
		{
			return strcmp(t1.string, t2.string) == 0;
		}

		friend bool operator!=(const Text& t1, const Text& t2)
		{
			return strcmp(t1.string, t2.string) != 0;
		}

		operator char*(void) const
		{
			return string;
		}

		operator const char*(void) const
		{
			return string;
		}

		const char* toChar() const
		{
			return string;
		}

	private:

		void cpy(char* str);
		void cat(char* str);
	};
}

