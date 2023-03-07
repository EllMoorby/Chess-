#include "templateTest.h"
#include <iostream>
#include <unordered_map>
#include "Menu.h"
#include "Console.h"

std::unordered_map<std::string, std::wstring> colours{
	{"Fblack BbrightWhite",L"\x1b[30;107m"},
	{"Fwhite Bdefault", L"\x1b[37;49m"}
};

Menu::Menu(const MenuArgs& args) :

	options{ args.options },
	selectedOptionCharacter{ args.selectedOptionCharacter },
	running{ args.running },
	title{ args.title },
	selectedOptionIndex{ args.selectedOptionIndex },
	previousOptionIndex{ args.previousOptionIndex },
	defaultColour{ args.defaultColour },
	selectedOptionColour{ colours[args.selectedOptionColour] },
	deselectedOptionColour{ colours[args.deselectedOptionColour] }

{}


void Menu::displayMenu() {


	setConsoleToVirtual();
	changeSystemColours(defaultColour);
	clearTerminal();

	std::wstring prefix{};
	if (title != u8"") {
		std::cout << title << std::endl;
	}

	for (size_t i{ 0 }; i < options.size(); i++) {
		if (i == selectedOptionIndex) {
			prefix = selectedOptionColour + selectedOptionCharacter;
		}
		else {
			prefix = deselectedOptionColour + L" ";
		}
		std::wcout << prefix << options[i] << std::endl;
	}
}

void Menu::updateSelected() {
	if (GetKeyState(VK_UP) & 0x8000 && keysUp[0])
	{
		keysUp.reset(0);
		selectedOptionIndex = selectedOptionIndex-- > 0 ? selectedOptionIndex : 0;
	}
	else if (!(GetKeyState(VK_UP) & 0x8000)) {
		keysUp.set(0);

	}

	if (GetKeyState(VK_DOWN) & 0x8000 && keysUp[1])
	{
		keysUp.reset(1);
		selectedOptionIndex = selectedOptionIndex++ < options.size() - 1 ? selectedOptionIndex : options.size() - 1;
	}
	else if (!(GetKeyState(VK_DOWN) & 0x8000)) {
		keysUp.set(1);

	}

	if (GetKeyState(VK_ACCEPT) & 0x8000 && keysUp[2])
	{
		keysUp.reset(2);
	}
	else if (!(GetKeyState(VK_ACCEPT) & 0x8000)) {
		keysUp.set(2);
	}
}



void Menu::startMenu() {
	running = true;
	displayMenu();
	while (running) {
		updateSelected();
		if (selectedOptionIndex != previousOptionIndex) {
			previousOptionIndex = selectedOptionIndex;
			displayMenu();
		}
	}
}



