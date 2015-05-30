// interface.h - console interface of game

#ifndef INTERFACE_H_
#define INTERFACE_H_


#include <iostream>
#include <iomanip> // std::setw
#include <string>
#include "game_components.h"

class Interface
{
private:
	GameComponents* gameComponents;

	void ShowLogo() const;
	void ShowMainMenu() const;

	// settings menu session
	void SettingsMenuSession() const;

	void ShowSettingsMenu() const;
	void ShowSizeOfFieldMenu() const;
	void ShowSizeOfWinRowMenu() const;

	void ShowBots() const;
	void ShowChoisePlayer1Menu() const;
	void ShowChoisePlayer2Menu() const;

	// input methods
	u_int GetNumber(const std::string&, u_int, u_int) const;
	COORD GetCoord() const;

public:
	Interface();
	Interface(GameComponents*);
	~Interface();

	// menu session
	// @return 0 - exit
	// @retrun 1 - play game
	u_int MenuSession() const;

	void ShowGamingField() const;
};

#endif // INTERFACE_H_