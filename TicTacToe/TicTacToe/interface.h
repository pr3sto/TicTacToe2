// interface.h - console interface of game

#ifndef INTERFACE_H_
#define INTERFACE_H_


#include <iostream>
#include <iomanip> // std::setw
#include <string>
#include "game_components.h"

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	LightGray = 7,
	LightRed = 12,
	White = 15
};

class Interface
{
private:
	GameComponents* gameComponents;

	void ShowLogo() const;
	void ShowMainMenu() const;
	void ShowGamingField() const;
	void ShowPlayingInfo() const;


	void SettingsMenuSession() const;

	void ShowSettingsMenu() const;
	void ShowSizeOfFieldMenu() const;
	void ShowSizeOfWinRowMenu() const;

	void ShowBots() const;
	void ShowChoisePlayer1Menu() const;
	void ShowChoisePlayer2Menu() const;

	// input methods
	u_int GetNumber(const std::string&, u_int, u_int) const;

public:
	Interface();
	Interface(GameComponents*);
	~Interface();

	// menu session
	// @return 0 - exit
	// @retrun 1 - play game
	u_int MenuSession() const;

	// u_int = 1 / 2  -  player1's / player2's  move
	void ShowPlayingMenu(u_int) const;
	void ShowPlayerMove(u_int, COORD) const;
};

#endif // INTERFACE_H_