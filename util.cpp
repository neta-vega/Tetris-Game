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
#include<ios> 
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
#include<limits>

void hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}
void clear_screen()
{
	system("cls");
}
void sleep(double seconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

}
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
bool isValidCell(Shape& curr_shape, Board& board, Input direction)
{//checking if the shape can move to the sides or rotate - if the board isn't empty on the future location it will return false
	bool flag = true;
	int x = curr_shape.getCoordinateX();
	int y = curr_shape.getCoordinateY();
	int k = curr_shape.firstOccurenceOfCurrShapeK(curr_shape);

	if (direction == RIGHT)
	{
		for (int i = y + k; i >= y + curr_shape.getHeight() - 1; i--)
		{
			for (int j = x + 3; j >= x; j--)
			{
				if (board.board[i][j] == HASHTAG)
				{
					if (board.board[i][j + 1] == HASHTAG)
					{
						return false;
					}
					break;
				}
			}
		}
	}
	else if (direction == LEFT)
	{

		for (int i = y + k; i >= y + curr_shape.getHeight() - 1; i--)
		{
			for (int j = x; j <= x + 3; j++)
			{
				if (board.board[i][j] == HASHTAG)
				{
					if (board.board[i][j - 1] == HASHTAG)
					{
						return false;
					}
					break;
				}
			}
		}
	}
	else if (direction == CLOCKWISE || direction == COUTERCLOCKWISE)
	{
		Shape temp_shape;
		temp_shape = curr_shape;
		temp_shape.rotate(temp_shape, board, direction); //creating a new object to compare with the existing board

		for (int i = y + 3 - (4 - curr_shape.getHeight()), kk = 3 - (4 - curr_shape.getHeight()); i >= y; i--, kk--)
		{
			for (int j = x + 3, l = 3; j >= x; j--, l--)
			{
				if (board.board[i][j] == HASHTAG && curr_shape.curr_shape[kk][l] == ' ' && temp_shape.curr_shape[kk][l] == HASHTAG)
				{ //checking if the shape after rotation (temp shape is the same as curr shape after rotation)
					//is colliding with another shape on the board. it makes sure that even if 
					//ther's a collision, it's not with the curr shape itself(which will change)
					flag = false;
					break;
				}
				else
				{
					flag = true;
					break;
				}
			}
		}

	}


	return flag;
}
bool isStuck(Shape& curr_shape, Board& board)
{//this function is checking wether the shape has reached the bottom of the board - if so returns true
	int x = curr_shape.getCoordinateX();
	int y = curr_shape.getCoordinateY();
	if (y >= 14)
	{
		for (int k = 3; k >= 0; k--)
		{
			for (int l = 0; l <= 3; l++)
			{
				if (curr_shape.curr_shape[k][l] == HASHTAG)
				{
					if ((k + y) >= 17)//k is the lowest row in curr shape that has c, so k+y is the bottom of our shape
					{
						return true;
					}
				}
			}
		}
	}
	return false;

}
bool isColliding(Shape& curr_shape, Board& board)
{ //checking if there's a shape below the curr shape we want to lower
	int x = curr_shape.getCoordinateX();
	int y = curr_shape.getCoordinateY();
	int k = curr_shape.firstOccurenceOfCurrShapeK(curr_shape);
	int l = curr_shape.firstOccurenceOfCurrShapeL(curr_shape);

	for (int i = y + k + 1, m = k; i >= y + 1; i--, m--)
	{
		for (int j = x + l, n = l; j <= x + 3; j++, n++)
		{
			if (board.board[i][j] == HASHTAG && curr_shape.curr_shape[m][n] == HASHTAG)//compares the shape with the row below it in the board
			{
				if (m < 3 && curr_shape.curr_shape[m + 1][n] == ' ') //making sure the shape below is not part of curr shape
				{
					return true;
				}
				if (m == 3)
				{
					return true;
				}
			}
		}
	}
	return false;

}
char getKeyboardHit()
{
	char input = (char)getch();
	return input;
}
Input playerInput(char input, Player*& p1, Player*& p2)
{
	if (((Human*)p1)->setPlayerInput(input))
	{
		switch (input)
		{
		case 'a':
		{
			return LEFT;
		}
		case 'A':
		{
			return LEFT;
		}
		case 'd':
		{
			return RIGHT;
		}
		case 'D':
		{
			return RIGHT;
		}
		case 's':
		{
			return CLOCKWISE;
		}
		case 'S':
		{
			return CLOCKWISE;
		}
		case 'w':
		{
			return COUTERCLOCKWISE;
		}
		case 'W':
		{
			return COUTERCLOCKWISE;
		}
		case 'x':
		{
			return DOWN;
		}
		case 'X':
		{
			return DOWN;
		}
		}
	}
	if (((Human*)p2)->setPlayerInput(input))
	{
		switch (input)
		{
		case 'j':
		{
			return LEFT;
		}
		case 'J':
		{
			return LEFT;
		}
		case 'l':
		{
			return RIGHT;
		}
		case 'L':
		{
			return RIGHT;
		}
		case 'k':
		{
			return CLOCKWISE;
		}
		case 'K':
		{
			return CLOCKWISE;
		}
		case 'i':
		{
			return COUTERCLOCKWISE;
		}
		case 'I':
		{
			return COUTERCLOCKWISE;
		}
		case 'm':
		{
			return DOWN;
		}
		case 'M':
		{
			return DOWN;
		}
		}
	}
}
void KbHit(Player*& p1, Player*& p2, Board& board_p1, Board& board_p2, Shape& shape_p1, Shape& shape_p2, Menu& menu, Game& game)
{
	int choice; //will contain the menu choice - 1 if the player decided to start a new game and 2 to continue
	char input = getKeyboardHit();
	if (input == 27) //ascii for esc
	{
		clear_screen();
		choice = menu.menuChoice(true);
		if (choice == 1) //the player has chose to start a new game - Human vs Human
		{
			delete p1;
			delete p2;
			p1 = new Human;
			p2 = new Human;
			game.startNewGame(p1, p2);
			if (game.getExit())
				return;
		}
		if (choice == 2)//the player has chose to start a new game - Human vs Computer
		{
			delete p1;
			delete p2;
			p1 = new Human;
			p2 = new Computer;
			int level = menu.whichLevel();
			((Computer*)p2)->setLevel(level);
			game.startNewGame(p1, p2);
			if (game.getExit())
				return;
		}
		if (choice == 3)//the player has chose to start a new game - Computer vs Computer
		{
			delete p1;
			delete p2;
			p1 = new Computer;
			p2 = new Computer;
			int level = menu.whichLevel();
			((Computer*)p2)->setLevel(level);
			((Computer*)p1)->setLevel(level);
			game.startNewGame(p1, p2);
			if (game.getExit())
				return;
		}

		if (choice == 4) //continue the paused game
		{
			clear_screen();
			return;
		}
		else if (choice == 9) //exit the game
		{
			game.setExit(true);
			return;
		}
		else if (choice == 8) //display instructions
		{
			menu.instructions();
		}

	}
	else {
		if (((Human*)p1)->setPlayerInput(input))
		{
			Input direction = playerInput(input, p1, p2);
			if (isValidCellV2(shape_p1, board_p1, direction))
			{
				p1->executeAction(shape_p1, board_p1, direction);
			}
			if (direction == DOWN)
			{
				shape_p1.ableToMove(shape_p1, board_p1);
				if (shape_p1.getCanMove())
				{
					board_p1.lowerShape(shape_p1);
				}
			}
		}
		else if (((Human*)p2)->setPlayerInput(input))
		{
			Input direction = playerInput(input, p1, p2);
			if (isValidCellV2(shape_p2, board_p2, direction))
			{
				p2->executeAction(shape_p2, board_p2, direction); // it was p1
			}
			if (direction == DOWN)
			{
				shape_p2.ableToMove(shape_p2, board_p2);
				if (shape_p2.getCanMove())
				{
					board_p2.lowerShape(shape_p2);
				}
			}
		}
	}
}
bool isValidCellV2(Shape& curr_shape, Board& board, Input direction) // left, right,  CLOCKWISE/COUTERCLOCKWISE , board limits (not board bottom)
{
	bool flag = false;
	if (direction == RIGHT)
	{

		for (int i = 0; i < 4; i++)
		{
			flag = false;
			int _x = curr_shape.getPointArr()[i].getX() + 1;
			int _y = curr_shape.getPointArr()[i].getY();
			if (board.board[_y][_x] == HASHTAG)
			{
				for (int j = 0; j < 4; j++)
				{
					if (curr_shape.getPointArr()[j].getX() == _x && curr_shape.getPointArr()[j].getY() == _y)
					{
						flag = true; // Right is valid action 
						break;
					}


				}
				if (!flag)
				{
					return flag;
				}

			}
			if (_x > 11)
			{
				return false; // Right is invalid action due to board limits 
			}

		}
		return true; // Right is valid action
	}
	if (direction == LEFT)
	{
		for (int i = 0; i < 4; i++)
		{
			flag = false;
			int _x = curr_shape.getPointArr()[i].getX() - 1;
			int _y = curr_shape.getPointArr()[i].getY();
			if (board.board[_y][_x] == HASHTAG)
			{
				for (int j = 0; j < 4; j++)
				{
					if (curr_shape.getPointArr()[j].getX() == _x && curr_shape.getPointArr()[j].getY() == _y)
					{
						flag = true; // Left is valid action 
						break;
					}


				}
				if (!flag)
				{
					return flag;
				}

			}
			if (_x < 0)
			{
				return false; // Left is invalid action due to board limits 
			}
		}
		return true; // Left is valid action
	}
	if (direction == CLOCKWISE || direction == COUTERCLOCKWISE)
	{
		Shape temp_shape = curr_shape;
		temp_shape.rotate(temp_shape, board, direction);
		for (int i = 0; i < 4; i++)
		{
			flag = false;
			int _x = temp_shape.getPointArr()[i].getX();
			int _y = temp_shape.getPointArr()[i].getY();
			if (board.board[_y][_x] == HASHTAG)
			{
				for (int j = 0; j < 4; j++)
				{
					if (curr_shape.getPointArr()[j].getX() == _x && curr_shape.getPointArr()[j].getY() == _y)
					{
						flag = true; // CLOCKWISE/COUTERCLOCKWISE is valid action 
						break;
					}
				}
				if (!flag)
				{
					return flag;
				}

			}
			if (_x < 0 || _x > 12)
			{
				return false; //  CLOCKWISE/COUTERCLOCKWISE is invalid action due to board limits 
			}
		}
		return true; //  CLOCKWISE/COUTERCLOCKWISE is valid action
	}



}
bool isStuckV2(Shape& curr_shape, Board& board) // return true if the shape met other shape or arrived to the bottom
{
	bool flag = true;
	for (int i = 0; i < 4; i++)
	{
		flag = true;
		int _x = curr_shape.getPointArr()[i].getX();
		int _y = curr_shape.getPointArr()[i].getY() + 1;
		if (board.board[_y][_x] == HASHTAG)
		{
			for (int j = 0; j < 4; j++)
			{
				if (curr_shape.getPointArr()[j].getX() == _x && curr_shape.getPointArr()[j].getY() == _y)
				{
					flag = false; // You found yourself, continue
					break;
				}


			}
			if (flag)
			{
				return true;
			}

		}
		if (_y > 17)
		{
			return true; // shape arrived to the bottom 
		}

	}
	return false;
}