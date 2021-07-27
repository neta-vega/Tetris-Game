#include "player.h"
#include "human.h"
#include "Computer.h"
#include "board.h"
#include "game.h"
#include "menu.h"
#include "point.h"
#include "shape.h"
#include "utils.h"
#include "bomb.h"
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

constexpr char BOMB = 157;

void Bomb::startBomb(Board& board, int which_board, Player*& player)
{
	dropBomb(board);
	board.printBoard(which_board);
	while (!isBombStuck(board))
	{
		int j = 0;
		while (j < 20)
		{
			if (_kbhit())
			{
				char kbhit = getKeyboardHit();
				Input direction;
				if (((Human*)player)->setPlayerInput(kbhit))
				{
					direction = playerInput(kbhit, player, player);
					moveBomb(board, direction);
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
			j++;
		}
		moveBomb(board, DOWN);
		board.printBoard(which_board);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	explode(board);
	board.printBoard(which_board);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

}
bool Bomb::isBombStuck(Board& board)
{
	int x = coordinate.getX();
	int y = coordinate.getY();
	if (board.board[y + 1][x] == 35 || y >= 17) { return true; }
	return false;
}
void Bomb::dropBomb(Board& board)
{
	int x = 4, y = 0;
	setCoordinates(x, y);

	board.board[y][x] = BOMB;
}
void Bomb::moveBomb(Board& board, Input direction) //moving the bomb right, left and down
{
	int x = coordinate.getX();
	int y = coordinate.getY();
	if (!isBombCanMove(board, direction))
	{
		return;
	}
	if (direction == RIGHT)
	{
		board.board[y][x] = ' ';
		x++;
		coordinate.setValue(x, y);
		board.board[y][x] = BOMB;
	}
	if (direction == LEFT)
	{
		board.board[y][x] = ' ';
		x--;
		coordinate.setValue(x, y);
		board.board[y][x] = BOMB;
	}
	if (direction == DOWN)
	{
		board.board[y][x] = ' ';
		y++;
		coordinate.setValue(x, y);
		board.board[y][x] = BOMB;
	}
}
bool Bomb::isBombCanMove(Board& board, Input direction)
{
	int x = coordinate.getX();
	int y = coordinate.getY();

	if (direction == RIGHT)
	{
		if (board.board[y][x + 1] == 35 || x >= 11)
			return false;
	}
	if (direction == LEFT)
	{
		if (board.board[y][x - 1] == 35 || x <= 0)
			return false;
	}
	return true;
}
void Bomb::explode(Board& board)
{
	int x = coordinate.getX();
	int y = coordinate.getY();
	int i, j;
	if (x >= 4)
	{
		i = x - 4;
	}
	else {
		i = 0;
	}
	for (i; i <= x + 4 && i <= 11; i++)
	{
		if (y >= 9)
		{
			j = y - 4;
		}
		else {
			j = 0;
		}
		for (j; j <= y + 4 && j <= 17; j++)
		{
			board.board[j][i] = ' ';
		}
	}
}
Point Bomb::whereToExplode(Board& board)
{
	Point location;
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (board.board[i][j] == HASHTAG)
			{
				location.convert(j, i);
				return location;
			}
		}
	}
}
Input* Bomb::bombPath(Board& board, Point where_to_explode, int& path_size)
{
	vector<Input> input_path;
	Input* final_path;
	bool found = false;
	bool reach_to_top = false;
	Point origin_bomb(4, 0);
	bool left_option = true, right_option = true, up_option = true;

	int future_x = where_to_explode.getX();
	int future_y = where_to_explode.getY();
	int dif_x = where_to_explode.getX() - origin_bomb.getX();
	int dif_y = where_to_explode.getY() - origin_bomb.getY();
	while (!reach_to_top)
	{
		if (future_x == origin_bomb.getX() && future_y == origin_bomb.getY())
		{
			reach_to_top = true;
			found = true;
		}
		else
		{
			found = false;
			left_option = true, right_option = true, up_option = true;
		}
		while (!found)
		{
			if (dif_x > 0 || !up_option) //move left from the bottom
			{
				if (board.board[future_y][future_x - 1] == ' ')
				{
					found = true;
					input_path.push_back(RIGHT);
					future_x--;
					dif_x--;
				}
				else
				{
					left_option = false; //the bomb can't move left (left from the bottom - right from the top)
				}
			}
			if (dif_x < 0 || (!up_option && !left_option)) //move right from the bottom
			{
				if (board.board[future_y][future_x + 1] == ' ')
				{
					input_path.push_back(LEFT);
					future_x++;
					dif_x++;
					found = true;
				}
				else
				{
					right_option = false; //the bomb can't move left (left from the bottom - right from the top)
				}
			}
			if (dif_x == 0 || !left_option || !right_option)
			{
				if (board.board[future_y - 1][future_x] == ' ')
				{
					input_path.push_back(DOWN);
					future_y--;
					dif_y--;
					found = true;
				}
				else
				{
					up_option = false; //the bomb can't move left (left from the bottom - right from the top)
				}
			}
		}
	}
	path_size = input_path.size();
	final_path = new Input[path_size];
	for (int i = 0; i < path_size; i++)
	{
		final_path[i] = input_path.back();
		input_path.pop_back();
	}

	return final_path;
}