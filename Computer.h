#ifndef _COMPUTER_H
#define _COMPUTER_H
#include "player.h"
#include "point.h"
#include <vector>

class Computer : public Player
{
	int level;
public:
	void setLevel(int _level) { level = _level; }
	int getLevel() const { return level; }
	virtual const char* getType() const { return "Computer"; }
	int baseWidth(Shape& curr_shape); //returns the base width
	bool emptySpotsBelow(Board& board, Shape& curr_shape); //returns true if there are empty cells below the shape after it reached the bottom
	Input* futurePosition(Board& board, Shape& curr_shape, int& path_size);
	int heightDifference(Board& board, Shape& tmp_shape);
	int fullLines(Board& board, Shape& tmp_shape);
	int jailedSpaces(Board& board, Shape& tmp_shape);
	int bumpiness(Board& board, Shape& tmp_shape);
	bool isLegalPosition(Board& board, Shape& tmp_shape);
	bool pathFinding(Board& board, Shape& future_position, Point* origin_points, Input*& path, int& path_size);
	Input* chooseRandPosition(Board& board, Shape& curr_shape, int& path_size);
	void executeAction(Shape& curr_shape, Board& board, Input action);
};
#endif // _COMPUTER_H
