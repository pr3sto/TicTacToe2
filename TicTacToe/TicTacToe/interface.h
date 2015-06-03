// interface.h - console interface of game

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <iostream>
#include <iomanip> // std::setw
#include <string>
#include "game_components.h"

// color of symbols in console 
enum ConsoleColor
{
	BLACK = 0,
	BLUE = 1,
	LIGHT_GRAY = 7,
	LIGHT_RED = 12,
	WHITE = 15
};

// interface of game
class Interface
{
private:
	GameComponents* game_components;

	void Logo() const;         // shows game logotip ("X vs O")
	void GamingField() const;  // shows gaming field (just lines, without figures)
	void PlayingInfo() const;  // shows info to the left of gaming field when play
	void MainMenu() const;     // shows main menu of game
	
	
	void SettingsMenuSession() const; // shows settings menu and call other menus 
									  // for parametrs (size_of_field, size_of_win_row,..)
	void SettingsMenu() const;        // shows settings menu
	void SizeOfFieldMenu() const;     // shows menu for choosing size of field
	void SizeOfWinRowMenu() const;    // shows menu for choosing size of win row

	void ListOfBots() const;          // shows list of bots
	void ChoisePlayer1Menu() const;   // show menu for choosing player 1
	void ChoisePlayer2Menu() const;   // show menu for choosing player 2

	void BotsInfo() const;     // info from player->Info();
	void Info() const;         // about game

	// shows msg in console
	// @return number (min <= number <= max)
	int GetNumber(const std::string& msg, int min, int max) const;

public:
	Interface();
	Interface(GameComponents*);
	~Interface();

	// menu session
	// shows main menu and calls other menus
	// @return 0 - exit
	// @retrun 1 - play game
	int MenuSession() const;

	// shows menu when players play
	void PlayingMenu() const;

	// shows whose move now	
	// player = 1 / 2  -  player1's / player2's  move
	void PlayersMoveMenu(int player) const;

	// shows player figure on the field
	// player = 1 / 2  -  player1's / player2's  move
	void ShowPlayerMove(int player, COORD move) const;

	// when game finished shows how win (or shows draw)
	// player = 1 / 2  -  player1's / player2's
	// player = 0 - draw
	void GameOver(int player) const;
};

#endif // INTERFACE_H_