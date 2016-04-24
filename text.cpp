#include "main.h"

using namespace Utils;

Text::Text() {
	string = new char[1];
	//string = (char*)malloc(sizeof(char));
	string[0] = '\0';
}

Text::Text(const char* str) {
	int size = strlen(str);
	string = new char[size + 1];
	//string = (char*)malloc(sizeof(char) * (size + 1));
	strcpy(string, str);
}

Text::Text(char* str) {
	int size = strlen(str);
	string = new char[size + 1];
	//string = (char*)malloc(sizeof(char) * (size + 1));
	strcpy(string, str);
}

Text::Text(char c) {
	string = new char[2];
	//string = (char*)malloc(sizeof(char) * 2);
	string[0] = c;
	string[1] = '\0';
}

Text::Text(int i) {
	string = new char[12];
	//string = (char*)malloc(sizeof(int));
	itoa(i, string, 10);
}

Text::Text(const Text &str) {
	int size = strlen(str.string);
	string = new char[size + 1];
	//string = (char*)malloc(sizeof(char) * (size + 1));
	strcpy(string, str.string);
}

Text::~Text() {
	 delete[] string;
}

void Text::clear() {
	delete[] string;
	string = new char[1];
	//string = (char*)malloc(sizeof(char));
	string[0] = 0;
}

void Text::clearLastChar() {
	if (length() == 0)
		return;

	string[length() - 1] = '\0';
	cpy(string);
}

int Text::length() const
{
	return strlen(string);
}

bool Text::isEmpty() const
{
	return length() == 0;
}

void Text::cpy(char* str) {
	delete[] string;
	int size = strlen(str);
	string = new char[size + 1];
	//string = (char*)malloc(sizeof(char) * (size + 1));
	strcpy(string, str);
}

void Text::cat(char* str) {
	int size = length() + strlen(str);
	char* tmp = new char[size + 1];
	//char* tmp = (char*)malloc(sizeof(char) * (size + 1));

	strcpy(tmp, string);
	strcat(tmp, str);

	delete[] string;
	string = tmp;
}