#pragma once
#ifndef _BOMB_H
#define _BOMB_H
class Point;
class Board;
enum Input;

class Bomb
{
	Point coordinate;
public:
	void dropBomb(Board& board);
	int getCoordinateX() const { return coordinate.getX(); };
	int getCoordinateY() const { return coordinate.getY(); };
	void setCoordinates(int& _x, int& _y) { coordinate.setValue(_x, _y); };
	void moveBomb(Board& board, Input direction); //moving the bomb right, left and down
	bool isBombStuck(Board& board);//returns true if the bomb meets shape
	bool isBombCanMove(Board& board, Input direction);
	void explode(Board& board);
	void startBomb(Board& board, int which_board, Player*& player);
	Point whereToExplode(Board& board); //returns the highest hashtag on the board
	Input* bombPath(Board& board, Point where_to_explode, int& path_size);


};

#endif //_BOMB_H