// interface.cpp - console interface of game

#include "interface.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;

Interface::Interface()
{
	game_components = nullptr;
}

Interface::Interface(GameComponents* game_comps)
{
	if (game_comps == nullptr)
	{
		std::string err = "Incorrect argument";
		std::string func = "Interface::Interface(GameComponents* game_comps)";
		std::string info = "game_comps = NULL pointer";
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	game_components = game_comps;
}

Interface::~Interface() 
{}


void Interface::Logo() const 
{
	cout << setw(75) << R"(  _____    ______                                      _________    )" << endl;
	cout << setw(75) << R"(  \  \ \  /   / /                                    /        \ \   )" << endl;
	cout << setw(75) << R"(   \  \ \/   / /     ___     ____    ________       /    ___   \ \  )" << endl;
	cout << setw(75) << R"(    \  \/   / /      \  \   /  / /  /  ____/_/     |    /|  |   | | )" << endl;
	cout << setw(75) << R"(    |   _   | |       \  \_/  / /  /  /____        |   | |  |   | | )" << endl;
	cout << setw(75) << R"(   /   / \   \ \       \     / /   \____  \ \      |   |_|_/    | | )" << endl;
	cout << setw(75) << R"(  /   / / \   \ \       \   / /     ____\  \ \      \          / /  )" << endl;
	cout << setw(75) << R"( /___/_/   \___\_\       \_/_/     /_______/_/       \________/_/   )" << endl;
	cout << endl;
}

void Interface::GamingField() const
{
	SetConsoleOutputCP(866); // for border's symbols
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // for color changing

	int size_of_field = game_components->field()->size_of_field();
	
	int space = (10 - size_of_field) * 2; // to locate field in the middle

	// to locate field in the middle
	cout << endl;
	if (size_of_field < 9)
		cout << endl;
	if (size_of_field < 7)
		cout << endl;
	if (size_of_field < 5)
		cout << endl;

	// top of field
	cout << setw(38 + space) << "\xda" << "\xc4\xc4\xc4";
	for (int i = 1; i < size_of_field; ++i) cout << "\xc2" << "\xc4\xc4\xc4";
	cout << "\xbf" << endl;

	// middle of field
	for (int i = 0; i < size_of_field; ++i)
	{
		cout << setw(38 + space) << "\xb3";
		for (int j = 0; j < size_of_field; ++j)
		{
			SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | BLUE));
			cout << j << "," << i;
			SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | LIGHT_GRAY));
			cout << "\xb3";
		}
		cout << endl;

		if (i == size_of_field - 1) break;

		cout << setw(38 + space) << "\xc3" << "\xc4\xc4\xc4";
		for (int j = 1; j < size_of_field; ++j) cout << "\xc5" << "\xc4\xc4\xc4";
		cout << "\xb4" << endl;
	}

	// bottom of field
	cout << setw(38 + space) << "\xc0" << "\xc4\xc4\xc4";
	for (int i = 1; i < size_of_field; ++i) cout << "\xc1" << "\xc4\xc4\xc4";
	cout << "\xd9" << endl;

	SetConsoleOutputCP(1251);
}

void Interface::PlayingInfo() const
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// coordinates of cursor
	COORD coord;

	coord.X = 11; coord.Y = 1;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "-  ИГРА  -";

	coord.X = 5; coord.Y = 4;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "Первый игрок (X):";
	coord.X = 23; coord.Y = 4;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << game_components->player1()->player_name();

	coord.X = 5; coord.Y = 6;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "Второй игрок (O):";
	coord.X = 23; coord.Y = 6;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << game_components->player2()->player_name();

	coord.X = 5; coord.Y = 8;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "Размер линии для победы: ";
	coord.X = 30; coord.Y = 8;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << game_components->field()->size_of_winning_row();
}

void Interface::PlayingMenu() const
{
	system("cls");

	this->GamingField();
	this->PlayingInfo();
}

void Interface::PlayersMoveMenu(int player) const
{
	if (player != 1 && player != 2)
	{
		std::string err = "Incorrect argument";
		std::string func = "void Interface::PlayersMoveMenu(int player) const";
		std::string info = "player = "; info += std::to_string(player);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written = 0;

	// coordinates of cursor
	COORD coord;
	coord.X = 5; coord.Y = 11;

	// clear line
	SetConsoleCursorPosition(hStdOut, coord);
	FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);

	cout << "Ход:";

	coord.X = 10; coord.Y = 11;
	SetConsoleCursorPosition(hStdOut, coord);

	if (player == 1)
		cout << game_components->player1()->player_name() << endl;
	
	else if (player == 2)
		cout << game_components->player2()->player_name() << endl;

	coord.X = 5; coord.Y = 13;
	SetConsoleCursorPosition(hStdOut, coord);
}

void Interface::ShowFigureOnField(int player, COORD cell, ConsoleColor color) const
{
	if (player != 1 && player != 2)
	{
		std::string err = "Incorrect argument (first)";
		std::string func = "void Interface::ShowFigureOnField(int player, COORD cell, ConsoleColor color) const";
		std::string info = "player = "; info += std::to_string(player);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}
	if (cell.X < 0 || cell.X >= game_components->field()->size_of_field() ||
		cell.Y < 0 || cell.Y >= game_components->field()->size_of_field())
	{
		std::string err = "Incorrect argument (second)";
		std::string func = "void Interface::ShowFigureOnField(int player, COORD cell, ConsoleColor color) const";
		std::string info = "cell = ";
		info += std::to_string(cell.X); info += ", "; info += std::to_string(cell.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position; // position of symbol

	int size_of_field = game_components->field()->size_of_field();
	int space = (10 - size_of_field) * 2 + 38;

	if (size_of_field < 5)
		position.Y = 5 + cell.Y * 2;
	else if (size_of_field < 7)
		position.Y = 4 + cell.Y * 2;
	else if (size_of_field < 9)
		position.Y = 3 + cell.Y * 2;
	else
		position.Y = 2 + cell.Y * 2;

	position.X = space + 4 * cell.X;

	// set cursor, set color and print symbol
	SetConsoleCursorPosition(hStdOut, position);
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | color));
	if (player == 1) cout << " X ";
	else if (player == 2) cout << " O ";
	// turn back to standart color
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | LIGHT_GRAY)); 
}

void Interface::ShowPlayerMove(int player, COORD move) const
{
	if (player != 1 && player != 2)
	{
		std::string err = "Incorrect argument (first)";
		std::string func = "void Interface::ShowPlayerMove(int player, COORD move) const";
		std::string info = "player = "; info += std::to_string(player);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}
	if (move.X < 0 || move.X >= game_components->field()->size_of_field() || 
		move.Y < 0 || move.Y >= game_components->field()->size_of_field() )
	{
		std::string err = "Incorrect argument (second)";
		std::string func = "void Interface::ShowPlayerMove(int player, COORD move) const";
		std::string info = "move = ";
		info += std::to_string(move.X); info += ", "; info += std::to_string(move.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// coordinates of cursor
	COORD coord;
	coord.X = 5; coord.Y = 13;

	SetConsoleCursorPosition(hStdOut, coord);
	cout << "Ход в клетку (" << move.X << ", " << move.Y << ") ";

	this->ShowFigureOnField(player, move, LIGHT_RED);

	coord.X = 24; coord.Y = 13;
	SetConsoleCursorPosition(hStdOut, coord);

	std::cin.get();
	cin.clear();
	_flushall();
}

void Interface::HighlightTheWinningRow(u_int player) const
{
	if (player != 1 && player != 2)
	{
		std::string err = "Incorrect argument";
		std::string func = "void Interface::HighlightTheWinningRow(u_int player) const";
		std::string info = "player = "; info += std::to_string(player);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	COORD start = game_components->field()->EndsOfWinningRow(player).first;
	COORD end = game_components->field()->EndsOfWinningRow(player).second;
	COORD tmp;

	// column
	if (start.X == end.X)
	{
		for (int i = start.Y; i <= end.Y; ++i)
		{
			tmp.X = start.X; tmp.Y = i;
			this->ShowFigureOnField(player, tmp, LIGHT_GREEN);
		}
	}
	// line
	else if (start.Y == end.Y)
	{
		for (int i = start.X; i <= end.X; ++i)
		{
			tmp.X = i; tmp.Y = start.Y;
			this->ShowFigureOnField(player, tmp, LIGHT_GREEN);
		}
	}
	// left to right diagonal
	else if (start.X < end.X)
	{
		int i = start.X;
		int j = start.Y;
		for ( ; i <= end.X; ++i, ++j)
		{
			tmp.X = i; tmp.Y = j;
			this->ShowFigureOnField(player, tmp, LIGHT_GREEN);
		}
	}
	// right to left diagonal
	else if (start.X > end.X)
	{
		int i = start.X;
		int j = start.Y;
		for (; i >= end.X; --i, ++j)
		{
			tmp.X = i; tmp.Y = j;
			this->ShowFigureOnField(player, tmp, LIGHT_GREEN);
		}
	}
}

void Interface::GameOver(int player) const
{
	if (player != 0 && player != 1 && player != 2)
	{
		std::string err = "Incorrect argument";
		std::string func = "void Interface::GameOver(int player) const";
		std::string info = "player = "; info += std::to_string(player);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written = 0;

	// coordinates of cursor
	COORD coord;
	coord.X = 5; coord.Y = 11;

	// set cursor + clean lines
	SetConsoleCursorPosition(hStdOut, coord);
	FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
	coord.Y += 2;
	SetConsoleCursorPosition(hStdOut, coord);
	FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);

	if (player != 0) // if not draw
		this->HighlightTheWinningRow(player);
	
	coord.X = 10; coord.Y = 12;
	SetConsoleCursorPosition(hStdOut, coord);

	cout << "Игра окончена";

	coord.X = 0; coord.Y = 14;
	SetConsoleCursorPosition(hStdOut, coord);

	std::string winner = "Победил(а) ";
	if (player == 1)
		winner += game_components->player1()->player_name();
	else if (player == 2)
		winner += game_components->player2()->player_name();
	else
		winner = "Ничья";
	winner += "!";
	cout << setw(17 + winner.size() / 2) << winner;

	cin.get();
	cin.clear();
	_flushall();
}


void Interface::MainMenu() const 
{
	this->Logo();
	
	cout << setw(49) << "  -  Меню:  -  " << endl << endl 
		<< setw(49) << "1. Играть -----" << endl << endl
		<< setw(49) << "2. Настройки --" << endl << endl
		<< setw(49) << "3. Статистика -" << endl << endl
		<< setw(49) << "4. Об игре ----" << endl << endl
		<< setw(49) << "5. Выход ------" << endl << endl
		<< endl;
}

void Interface::SettingsMenu() const 
{
	this->Logo();

	cout << setw(50) << "         -  Настройки:  - " << endl << endl;
	cout << setw(50) << "1. Размер поля            ";
	cout << setw(5) << "(" << game_components->field()->size_of_field() << "x"
		<< game_components->field()->size_of_field() << ")" << endl << endl;
	cout << setw(50) << "2. Размер линии для победы";
	cout << setw(5) << "(" << game_components->field()->size_of_winning_row() << ")" << endl << endl;
	cout << setw(50) << "3. Первый игрок           ";
	cout << setw(5) << "(" << game_components->player1()->player_name() << ")" << endl << endl;
	cout << setw(50) << "4. Второй игрок           ";
	cout << setw(5) << "(" << game_components->player2()->player_name() << ")" << endl << endl;

	cout << endl << setw(63) << "5. Назад                  " << endl << endl;
}

void Interface::SizeOfFieldMenu() const
{
	system("cls");
	this->Logo();

	cout << endl << endl << endl
	    << setw(48) << "Минимальный размер:   "
		<< game_components->field()->MIN_SIZE_OF_FIEFD 
		<< " x " 
		<< game_components->field()->MIN_SIZE_OF_FIEFD
		<< endl << endl;
	cout << setw(47) << "Максимальный размер: "
		<< game_components->field()->MAX_SIZE_OF_FIEFD
		<< " x "
		<< game_components->field()->MAX_SIZE_OF_FIEFD
		<< endl << endl << endl << endl;
		 
	game_components->field()->set_size_of_field(
		this->GetNumber("\t\t\t    Введите размер поля: ",
			game_components->field()->MIN_SIZE_OF_FIEFD,
			game_components->field()->MAX_SIZE_OF_FIEFD
		)
	);
}

void Interface::SizeOfWinningRowMenu() const
{
	system("cls");
	this->Logo();

	cout << endl
		<< setw(65) << "Размер линии для победы - это количество фигур," << endl
		<< setw(65) << "выстроенных в  ряд  по  горизонтали, вертикали " << endl
		<< setw(65) << "или диагонли, необходимое для победы.          " << endl
		<< endl << endl

		<< setw(50) << "Минимальный размер:  "
		<< game_components->field()->MIN_SIZE_OF_WINNING_ROW << endl << endl
		<< setw(50) << "Максимальный размер: "
		<< game_components->field()->size_of_field() << endl << endl << endl;

	game_components->field()->set_size_of_winning_row(
		this->GetNumber("\t\t\tВведите размер линии для победы: ",
			game_components->field()->MIN_SIZE_OF_WINNING_ROW,
			game_components->field()->size_of_field()
		)
	);
}

void Interface::ListOfBots() const
{
	int counter = 1;
	std::vector<Player*> tmp = game_components->vector_of_bots();

	for (auto i = tmp.begin(); i != tmp.end(); ++i, ++counter)
	{
		int width = 41 - (*i)->player_name().size() / 2;
		cout << setw(width) << counter << ". " << (*i)->player_name() << endl << endl;
	}
}

void Interface::ChoisePlayer1Menu() const
{
	system("cls");
	this->Logo();

	cout << endl
		<< setw(55) << "Первый игрок ходит первым." << endl << endl << endl
		<< setw(53) << "Выберите тип игрока: " << endl << endl
		<< setw(49) << "1. Человек ---" << endl << endl
		<< setw(49) << "2. Компьютер -" << endl << endl << endl
		<< setw(49) << "   3. Назад   " << endl << endl;
	
	int player_choise = this->GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 3);
	switch (player_choise)
	{
	case 1: // human
	{
		system("cls");
		this->Logo();

		cout << endl << endl << endl;
		cout << setw(60) << "Максимальное количество символов: 12" << endl << endl;
		cout << setw(44) << "Введите имя игрока: ";
		std::string tmp;  getline(cin, tmp);
		game_components->set_player1(game_components->vector_of_humans()[0]);
		game_components->player1()->set_player_name(tmp);
		break;
	}
	case 2: // bot
	{
		system("cls");
		this->Logo();

		cout << endl
			<< setw(50) << "Выберите бота: " << endl << endl;
		this->ListOfBots();
		cout << endl;

		// player_choise - 1, because of vector have numeration from 0
		int player_choise = this->GetNumber(
			"\t\t\t    Введите номер пункта меню: ",
			1,
			game_components->vector_of_bots().size()
			) - 1;

		game_components->set_player1(game_components->vector_of_bots()[player_choise]);
		break;
	}
	case 3: // back
		break;
	default:
		break;
	}
}

void Interface::ChoisePlayer2Menu() const
{
	system("cls");
	this->Logo();

	cout << endl
		<< setw(55) << "Второй игрок ходит вторым." << endl << endl << endl
		<< setw(53) << "Выберите тип игрока: " << endl << endl
		<< setw(49) << "1. Человек ---" << endl << endl
		<< setw(49) << "2. Компьютер -" << endl << endl << endl
		<< setw(49) << "   3. Назад   " << endl << endl;

	int player_choise = this->GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 3);
	switch (player_choise)
	{
	case 1: // human
	{
		system("cls");
		this->Logo();

		cout << endl << endl << endl;
		cout << setw(60) << "Максимальное количество символов: 12" << endl << endl;
		cout << setw(44) << "Введите имя игрока: ";
		std::string tmp;  getline(cin, tmp);
		game_components->set_player2(game_components->vector_of_humans()[1]);
		game_components->player2()->set_player_name(tmp);
		break;
	}
	case 2: // bot
	{
		system("cls");
		this->Logo();

		cout << endl
			<< setw(50) << "Выберите бота: " << endl << endl;
		this->ListOfBots();
		cout << endl;

		// player_choise - 1, because of vector have numeration from 0
		int player_choise = this->GetNumber(
			"\t\t\t    Введите номер пункта меню: ",
			1,
			game_components->vector_of_bots().size()
			) - 1;

		game_components->set_player2(game_components->vector_of_bots()[player_choise]);
		break;
	}
	case 3: // back
		break;
	default:
		break;
	}
}

void Interface::SettingsMenuSession() const
{
	while (true)
	{
		system("cls");
		this->SettingsMenu();

		int sett_choise = GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 5);

		switch (sett_choise)
		{
		case 1: // size of field
			this->SizeOfFieldMenu();
			break;			
		case 2: // size of winning row
			this->SizeOfWinningRowMenu();
			break;			
		case 3: // player 1
			this->ChoisePlayer1Menu();
			break;
		case 4: // player 2
			this->ChoisePlayer2Menu();
			break;			
		case 5: // back
			return;
		default:
			break;
		}
	}
}

void Interface::BotsInfo() const
{
	system("cls");
	cout << endl;
	cout << setw(46) << "-  Боты:  -" << endl << endl << endl;

	game_components->vector_of_humans()[0]->Info();
	cout << endl;

	int width;
	int counter = 2;

	auto bots = game_components->vector_of_bots();
	for (auto i = bots.begin(); i != bots.end(); ++i, ++counter)
	{
		width = 37 - (*i)->player_name().size() / 2;
		cout << setw(width) << counter << ". Бот " << (*i)->player_name() << endl << endl;
		(*i)->Info();
		cout << endl << endl << endl;
	}

	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// coordinates of cursor
	COORD coord;
	coord.X = 0; coord.Y = 0;
	SetConsoleCursorPosition(hStdOut, coord);

	cin.get();
	cin.clear();
	_flushall();
}

void Interface::Info() const
{
	system("cls");
	this->Logo();
	cout << endl;

	cout << setw(44) << "Об игре:" << endl << endl
		<< setw(75) << "Крестики - нолики  —  логическая  игра  между  двумя  противниками  " << endl << endl
		<< setw(75) << "на квадратном поле любого размера (вплоть до «бесконечного поля»).  " << endl << endl
		<< setw(75) << "Один из игроков играет  «крестиками» (X), второй — «ноликами» (O).  " << endl << endl
		<< endl << endl
		<< setw(46) << "Правила игры:" << endl << endl
		<< setw(75) << "Игроки  по  очереди ставят  на  свободные клетки  поля  знаки (один " << endl << endl
		<< setw(75) << "всегда крестики,  другой всегда нолики).  Первый, выстроивший в ряд " << endl << endl
		<< setw(75) << "N своих фигур по  вертикали, горизонтали или диагонали, выигрывает. " << endl << endl
		<< setw(75) << "Первый ход делает игрок, ставящий крестики.                         " << endl << endl
		<< endl << endl
		<< setw(46) << "Автор: pr3sto" << endl << endl
		<< setw(42) << "2015";

	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// coordinates of cursor
	COORD coord;
	coord.X = 0; coord.Y = 0;
	SetConsoleCursorPosition(hStdOut, coord);

	cin.get();
	cin.clear();
	_flushall();
}

void Interface::InfoMenu() const
{
	while (true)
	{
		system("cls");
		this->Logo();

		cout
			<< setw(51) << "  -  Об игре:  -  "
			<< endl << endl << endl << endl
			<< setw(47) << "1. Общее ---"
			<< endl << endl
			<< setw(47) << "2. О ботах -"
			<< endl << endl << endl
			<< setw(47) << "  3. Назад  "
			<< endl << endl << endl << endl;

		int choise = this->GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 3);

		switch (choise)
		{
		case 1: // general info
			this->Info();
			break;
		case 2: // bots info
			this->BotsInfo();
			break;
		case 3: // back
			return;
		default:
			break;
		}
	}
}

int Interface::MenuSession() const
{	
	while (true)
	{
		system("cls");
		this->MainMenu();

		int menu_choise = GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 5);

		switch (menu_choise)
		{
		case 1: // play
			return 1;
		case 2: // settings
			this->SettingsMenuSession();
			break;
		case 3: // statistic
			//TODO: write stats func
			break;
		case 4: // info
			this->InfoMenu();
			break;
		case 5: // exit
			return 0;
		default:
			break;
		}
	}
}

int Interface::GetNumber(const std::string& msg, int min, int max) const
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	DWORD Written = 0;

	// coordinates of cursor
	COORD coord;

	// retrun value
	int ret;

	while (true)
	{
		if (msg.empty())
			cout << "Введите число от " << min << " до " << max << ": ";
		else
			cout << msg;

		// get current coordinates of cursor
		GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
		coord.X = 0;
		coord.Y = csbiInfo.dwCursorPosition.Y;

		cin >> ret;
		if (cin.good() && ret != 0 && ret >= min && ret <= max)
		{
			cin.ignore(10, '\n');
			cin.clear();
			_flushall();
			break;
		}

		cin.clear();
		cin.ignore(10, '\n');

		// set cursor + clean next 2 lines
		SetConsoleCursorPosition(hStdOut, coord);
		FillConsoleOutputCharacter(hStdOut, ' ', 300, coord, &Written);
	}

	return ret;
}