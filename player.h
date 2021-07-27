#ifndef _PLAYER_H
#define _PLAYER_H

enum Input //player input - during the game
{
	RIGHT = 0, LEFT = 1, DOWN = 2, CLOCKWISE = 3, COUTERCLOCKWISE = 4, PAUSE = 5
};
class Shape;
class Board;
class Player {
public:
	virtual const char* getType() const { return "Player"; }
	virtual void executeAction(Shape& curr_shape, Board& board, Input action);
};

#endif // _PLAYER_H