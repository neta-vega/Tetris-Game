#ifndef _BOARD_H
#define _BOARD_H

class Shape;
enum Input;

class Board
{
	bool win = false;

public:
	Board()
	{
		for (int i = 0; i < 18; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				board[i][j] = ' ';
			}
		}
	}

	char board[18][12];
	void printBoard(int which_board)const;
	void removeFullLine();
	void dropShape(Shape& curr_shape);
	void lowerShape(Shape& curr_shape);
	void updateBoard(Shape& curr_shape, Input direction);
	void move(Shape& curr_shape, Input direction);
	void setWin(bool _win) { win = _win; }
	bool getWin() const { return win; }

};

#endif // _BOARD_H