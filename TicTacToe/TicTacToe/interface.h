// interface.h - console interface of game

#ifndef INTERFACE_H_
#define INTERFACE_H_


#include <iostream>
#include <iomanip> // std::setw
#include <string>
#include "game_parametrs.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;


class Interface
{
private:
	GameParamsPtr gameParams;

	void ShowLogo() const;

	void ShowGamingField() const;

	void ShowMainMenu() const;

	// settings menu session
	void ShowSettingsMenu() const;
	void ShowSizeOfFieldMenu();
	void ShowSizeOfWinRowMenu();
	void ShowGameModMenu();
	void ShowComplexityMenu();
	void ShowSymbolMenu();
	void SettingsMenuSession();

	// input methods
	u_int GetNumber(string, u_int, u_int) const;
	COORD GetCoord() const;

public:
	Interface() { gameParams = GameParamsPtr(nullptr); }
	Interface(GameParamsPtr gameParams_) { gameParams = gameParams_; }
	~Interface() { }

	// menu session; @return 0 - exit
	u_int MenuSession(); 
};

#endif // INTERFACE_H_