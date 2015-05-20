// interface.h - console interface of game

#ifndef INTERFACE_H_
#define INTERFACE_H_


#include <iostream>
#include <iomanip> // std::setw
#include <string>
#include <memory> // std::shared_ptr
#include "windows.h"
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

public:
	Interface() { gameParams = GameParamsPtr(nullptr); }
	Interface(GameParamsPtr gameParams_) { gameParams = gameParams_; }
	~Interface() { }

	void ShowLogo() const;
	void ShowGamingField() const;

	void ShowMainMenu() const;
	void ShowSettingsMenu() const;
	void ShowGameModMenu() const;
	void ShowComplexityMenu() const;
	void ShowSymbolMenu() const;

	u_int GetNumber(string, u_int = 0, u_int = MAXUINT) const;
	COORD GetCoord() const;
};

#endif // INTERFACE_H_