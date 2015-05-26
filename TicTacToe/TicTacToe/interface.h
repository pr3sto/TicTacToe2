// interface.h - console interface of game

#ifndef INTERFACE_H_
#define INTERFACE_H_


#include <iostream>
#include <iomanip> // std::setw
#include <string>
#include "game_components.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;


class Interface
{
private:
	GameComponentsPtr gameComponents;

	void ShowLogo() const;
	void ShowGamingField() const;
	void ShowMainMenu() const;

	// settings menu session
	void ShowSettingsMenu() const;
	void ShowSizeOfFieldMenu();
	void ShowSizeOfWinRowMenu();
	void ShowChoisePlayer1Menu();
	void ShowChoisePlayer2Menu();
	void SettingsMenuSession();

	// input methods
	u_int GetNumber(const string&, u_int, u_int) const;
	COORD GetCoord() const;

public:
	Interface() : gameComponents(GameComponentsPtr(nullptr)) { }
	Interface(GameComponentsPtr gameParams_) : gameComponents(gameParams_) { }
	~Interface() { }

	// menu session
	// @return 0 - exit
	// @retrun 1 - play game
	u_int MenuSession(); 
};

#endif // INTERFACE_H_