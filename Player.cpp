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

void Player::executeAction(Shape& curr_shape, Board& board, Input action)
{ //validating borders in order to execute user's action
	int x = curr_shape.getCoordinateX();
	int y = curr_shape.getCoordinateY();
	int l = curr_shape.firstOccurenceOfCurrShapeL(curr_shape);
	int max_sides = x + l + curr_shape.getWidth();

	Shape temp_shape; //checking how the shape looks after rotation in order to check if a rotation is valid 
	temp_shape = curr_shape;
	temp_shape.rotate(temp_shape, board, action);
	int _x = temp_shape.getCoordinateX();
	int _y = temp_shape.getCoordinateY();
	int _k = temp_shape.firstOccurenceOfCurrShapeK(temp_shape);
	int _l = temp_shape.firstOccurenceOfCurrShapeL(temp_shape);
	int _max_sides = _x + _l + temp_shape.getWidth();


	switch (action)
	{
	case LEFT:
	{
		if (x + l > 0)
		{
			board.move(curr_shape, LEFT);
			break;
		}
		break;


	}
	case RIGHT:
	{
		if (max_sides < 12)
		{
			board.move(curr_shape, RIGHT);
			break;
		}
		break;


	}
	case CLOCKWISE:
	{
		if (x <= 6)
		{
			if (_x + _l > 0)
			{
				curr_shape.rotate(curr_shape, board, CLOCKWISE);
				board.updateBoard(curr_shape, CLOCKWISE);
			}
		}

		if (x > 6)
		{
			if (_max_sides < 12)
			{
				curr_shape.rotate(curr_shape, board, CLOCKWISE);
				board.updateBoard(curr_shape, CLOCKWISE);
			}
		}

		break;
	}
	case COUTERCLOCKWISE:
	{
		if (x <= 6)
		{
			if (_x + _l > 0)
			{
				curr_shape.rotate(curr_shape, board, COUTERCLOCKWISE);
				board.updateBoard(curr_shape, COUTERCLOCKWISE);
			}
		}
		if (x > 6)
		{
			if (_max_sides <= 12)
			{
				curr_shape.rotate(curr_shape, board, COUTERCLOCKWISE);
				board.updateBoard(curr_shape, COUTERCLOCKWISE);
			}
		}

		break;
	}
	}
}