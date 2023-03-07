#pragma once
#include "Colours.h"
#include <vector>
#include <string>
#include <bitset>

struct MenuArgs
{
	std::vector <std::wstring> options;
	wchar_t selectedOptionCharacter = L'*';
	std::u8string title = u8"";
	bool running = false;
	size_t selectedOptionIndex = 0;
	size_t previousOptionIndex = 0;
	std::string defaultColour = "Color 07";
	std::string selectedOptionColour = "Fblack BbrightWhite";
	std::string deselectedOptionColour = "Fwhite Bdefault";
};


class Menu
{
private:
	std::bitset <3> keysUp; // UpArrow, DownArrow, Enter
	std::vector <std::wstring> options;
	wchar_t selectedOptionCharacter;
	std::u8string title;
	bool running;
	size_t selectedOptionIndex;
	size_t previousOptionIndex;
	std::string defaultColour;
	std::wstring selectedOptionColour;
	std::wstring deselectedOptionColour;


public:
	Menu(const MenuArgs& args);

	void displayMenu();
	void updateSelected();
	void startMenu();
	//void quitMenu();
};

