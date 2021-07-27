#include "player.h"
#include "human.h"
#include "Computer.h"
#include "board.h"
#include "game.h"
#include "menu.h"
#include "point.h"
#include "shape.h"
#include "utils.h"
#pragma warning (disable:4996)
using namespace std;
#include <iostream>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

void Board::printBoard(int which_board)const
{
	char sides = 186;
	char base = 205;

	for (int k = 0; k < 18; k++)//drawing sides limits
	{
		gotoxy(0, k);
		cout << sides;
		gotoxy(13, k);
		cout << sides;
		gotoxy(26, k);
		cout << sides;
		gotoxy(39, k);
		cout << sides;
	}
	for (int l = 1; l < 13; l++)//drawing base limits
	{
		gotoxy(l, 18);
		cout << base;
		gotoxy(l + 26, 18);
		cout << base;
	}
	gotoxy(3, 20);
	cout << "PLAYER 1";
	gotoxy(29, 20);
	cout << "PLAYER 2";


	for (int i = 0; i < 18; i++)
	{
		if (which_board == 1)
		{
			gotoxy(1, i);

		}
		else if (which_board == 2)
		{
			gotoxy(27, i);
		}
		for (int j = 0; j < 12; j++)
		{
			cout << this->board[i][j];
		}
		cout << '\n';
	}

}
void Board::removeFullLine()
{//checking if a line is full - if so delete it and lower all the rows above it
	bool flag = true;
	int i, j, k, f;
	for (i = 0; i < 18; i++)
	{
		flag = true;
		for (j = 0; j < 12; j++)
		{
			if (board[i][j] == ' ')
			{
				flag = false;
				break;
			}

		}
		if (flag == true)
		{
			for (k = i; k > 0; k--)
			{
				for (f = 0; f < 12; f++)
				{
					board[k][f] = board[k - 1][f];
				}
			}
		}

	}

}
void Board::dropShape(Shape& curr_shape)
{ //at the beginning of the game or once a shape can't move anymore - this function will generate a new shape to the player's board
	int i, j, k;
	int o = 4, p = 0;
	curr_shape.setCoordinate(o, p);
	int x = curr_shape.getCoordinateX();
	srand((unsigned int)time(NULL));
	int random = std::rand() % 7;
	curr_shape.generateShapes(random);

	int row_to_check = curr_shape.getHeight() - 1;

	for (int i = 0; i < 11; i++)
	{
		if (this->board[row_to_check][i] != ' ')
		{
			setWin(true);
			return;
		}
	}
	for (i = 0; i < curr_shape.getHeight(); i++)
	{
		for (j = x, k = 0; j < x + 4; j++, k++)
		{
			this->board[i][j] = curr_shape.curr_shape[i][k];
		}
	}
}
void Board::lowerShape(Shape& curr_shape)
{//this function takes the current hape and lowers it on the board. it updates the board itself
	int x = curr_shape.getCoordinateX();
	int y = curr_shape.getCoordinateY();
	bool flag = true;

	for (int i = 0; i < 4; i++)
	{
		flag = true;
		int _x = curr_shape.getPointArr()[i].getX();
		int _y = curr_shape.getPointArr()[i].getY();
		for (int j = 0; j < i; j++)
		{
			if (curr_shape.getPointArr()[j].getX() == _x && curr_shape.getPointArr()[j].getY() == _y)
			{
				_y++;
				this->board[_y][_x] = HASHTAG;
				curr_shape.getPointArr()[i].setValue(_x, _y);
				flag = false;
			}

		}
		if (flag) // all points before me was differnet 
		{
			this->board[_y][_x] = ' ';
			_y++;
			this->board[_y][_x] = HASHTAG;
			curr_shape.getPointArr()[i].setValue(_x, _y);
		}

	}

	y++;
	curr_shape.setCoordinate(x, y);


}
void Board::updateBoard(Shape& curr_shape, Input direction)
{//after checking that the wanted move (right' left or rotation) is valid (no collision with other shapes on the board or the borders), 
	//this unction updates the board itself - moves the shape on the board - depending on the direction
	int x = curr_shape.getCoordinateX();
	int y = curr_shape.getCoordinateY();
	bool flag = true;


	if (direction == RIGHT)
	{
		for (int i = 0; i < 4; i++)
		{
			flag = true;
			int _x = curr_shape.getPointArr()[i].getX();
			int _y = curr_shape.getPointArr()[i].getY();
			for (int j = 0; j < i; j++)
			{
				if (curr_shape.getPointArr()[j].getX() == _x && curr_shape.getPointArr()[j].getY() == _y)
				{
					_x++;
					this->board[_y][_x] = HASHTAG;
					curr_shape.getPointArr()[i].setValue(_x, _y);
					flag = false;
				}

			}
			if (flag) // all points before me was differnet 
			{
				this->board[_y][_x] = ' ';
				_x++;
				this->board[_y][_x] = HASHTAG;
				curr_shape.getPointArr()[i].setValue(_x, _y);
			}

		}
	}


	else if (direction == LEFT)
	{
		for (int i = 0; i < 4; i++)
		{
			flag = true;
			int _x = curr_shape.getPointArr()[i].getX();
			int _y = curr_shape.getPointArr()[i].getY();
			for (int j = 0; j < i; j++)
			{
				if (curr_shape.getPointArr()[j].getX() == _x && curr_shape.getPointArr()[j].getY() == _y)
				{
					_x--;
					this->board[_y][_x] = HASHTAG;
					curr_shape.getPointArr()[i].setValue(_x, _y);
					flag = false;
				}

			}
			if (flag) // all points before me was differnet 
			{
				this->board[_y][_x] = ' ';
				_x--;
				this->board[_y][_x] = HASHTAG;
				curr_shape.getPointArr()[i].setValue(_x, _y);
			}
		}
	}
	else if (direction == CLOCKWISE || direction == COUTERCLOCKWISE)
	{
		for (int i = 0; i < 4; i++)
		{
			int prev_x = curr_shape.getPrevPointArr()[i].getX();
			int prev_y = curr_shape.getPrevPointArr()[i].getY();
			this->board[prev_y][prev_x] = ' ';
		}
		for (int j = 0; j < 4; j++)
		{
			int _x = curr_shape.getPointArr()[j].getX();
			int _y = curr_shape.getPointArr()[j].getY();
			this->board[_y][_x] = HASHTAG;
		}
	}
}
void Board::move(Shape& curr_shape, Input direction)
{//if the players has chose to move the shape to the right\left,
	//this function will update it's coordinates and call another function to present the change on the board
	int x = curr_shape.getCoordinateX();
	int y = curr_shape.getCoordinateY();

	if (direction == LEFT)
	{

		this->updateBoard(curr_shape, LEFT);
		x--;
		curr_shape.setCoordinate(x, y);

	}
	else if (direction == RIGHT)
	{

		this->updateBoard(curr_shape, RIGHT);
		x++;
		curr_shape.setCoordinate(x, y);

	}
}