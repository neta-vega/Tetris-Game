#ifndef _GAME_H
#define _GAME_H

class Shape;
class Point;
class Player;
class Board;
class Menu;


class Game
{
	bool exit = false;
public:
	bool getExit() const { return exit; };
	void setExit(bool _exit) { exit = _exit; };
	void game();
	void startNewGame(Player* p1, Player* p2);
};




#endif //_GAME_H


