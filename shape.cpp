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

void Shape::setPointArr(Point p1, Point p2, Point p3, Point p4)
{
	point_arr[0] = p1;
	point_arr[1] = p2;
	point_arr[2] = p3;
	point_arr[3] = p4;
}
void Shape::setPrevPointArr(Point p1, Point p2, Point p3, Point p4)
{
	prev_point_arr[0] = p1;
	prev_point_arr[1] = p2;
	prev_point_arr[2] = p3;
	prev_point_arr[3] = p4;
}
void Shape::generateShapes(int random)
{
	const int two = 2, three = 3, one = 1, four = 4;
	Point point_arr[4];
	int point_index = 0;
	switch (random)
	{
	case 0: // J shape
		curr_shape[0][0] = HASHTAG; curr_shape[0][1] = HASHTAG; curr_shape[0][2] = HASHTAG; curr_shape[0][3] = ' ';
		curr_shape[1][0] = ' '; curr_shape[1][1] = ' '; curr_shape[1][2] = HASHTAG; curr_shape[1][3] = ' ';
		curr_shape[2][0] = ' '; curr_shape[2][1] = ' '; curr_shape[2][2] = ' '; curr_shape[2][3] = ' ';
		curr_shape[3][0] = ' '; curr_shape[3][1] = ' '; curr_shape[3][2] = ' '; curr_shape[3][3] = ' ';
		this->setHeightWidth(two, three);
		break;
	case 1: // I shape
		curr_shape[0][0] = HASHTAG; curr_shape[0][1] = HASHTAG; curr_shape[0][2] = HASHTAG; curr_shape[0][3] = HASHTAG;
		curr_shape[1][0] = ' '; curr_shape[1][1] = ' '; curr_shape[1][2] = ' '; curr_shape[1][3] = ' ';
		curr_shape[2][0] = ' '; curr_shape[2][1] = ' '; curr_shape[2][2] = ' '; curr_shape[2][3] = ' ';
		curr_shape[3][0] = ' '; curr_shape[3][1] = ' '; curr_shape[3][2] = ' '; curr_shape[3][3] = ' ';
		this->setHeightWidth(one, four);
		break;
	case 2: // L shape
		curr_shape[0][0] = HASHTAG; curr_shape[0][1] = HASHTAG; curr_shape[0][2] = HASHTAG; curr_shape[0][3] = ' ';
		curr_shape[1][0] = HASHTAG; curr_shape[1][1] = ' '; curr_shape[1][2] = ' '; curr_shape[1][3] = ' ';
		curr_shape[2][0] = ' '; curr_shape[2][1] = ' '; curr_shape[2][2] = ' '; curr_shape[2][3] = ' ';
		curr_shape[3][0] = ' '; curr_shape[3][1] = ' '; curr_shape[3][2] = ' '; curr_shape[3][3] = ' ';
		this->setHeightWidth(two, three);
		break;
	case 3: // [] shape
		curr_shape[0][0] = ' '; curr_shape[0][1] = HASHTAG; curr_shape[0][2] = HASHTAG; curr_shape[0][3] = ' ';
		curr_shape[1][0] = ' '; curr_shape[1][1] = HASHTAG; curr_shape[1][2] = HASHTAG; curr_shape[1][3] = ' ';
		curr_shape[2][0] = ' '; curr_shape[2][1] = ' '; curr_shape[2][2] = ' '; curr_shape[2][3] = ' ';
		curr_shape[3][0] = ' '; curr_shape[3][1] = ' '; curr_shape[3][2] = ' '; curr_shape[3][3] = ' ';
		this->setHeightWidth(two, two);
		break;
	case 4: // S shape
		curr_shape[0][0] = ' '; curr_shape[0][1] = HASHTAG; curr_shape[0][2] = HASHTAG; curr_shape[0][3] = ' ';
		curr_shape[1][0] = HASHTAG; curr_shape[1][1] = HASHTAG; curr_shape[1][2] = ' '; curr_shape[1][3] = ' ';
		curr_shape[2][0] = ' '; curr_shape[2][1] = ' '; curr_shape[2][2] = ' '; curr_shape[2][3] = ' ';
		curr_shape[3][0] = ' '; curr_shape[3][1] = ' '; curr_shape[3][2] = ' '; curr_shape[3][3] = ' ';
		this->setHeightWidth(two, three);
		break;
	case 5: // T shape
		curr_shape[0][0] = HASHTAG; curr_shape[0][1] = HASHTAG; curr_shape[0][2] = HASHTAG; curr_shape[0][3] = ' ';
		curr_shape[1][0] = ' '; curr_shape[1][1] = HASHTAG; curr_shape[1][2] = ' '; curr_shape[1][3] = ' ';
		curr_shape[2][0] = ' '; curr_shape[2][1] = ' '; curr_shape[2][2] = ' '; curr_shape[2][3] = ' ';
		curr_shape[3][0] = ' '; curr_shape[3][1] = ' '; curr_shape[3][2] = ' '; curr_shape[3][3] = ' ';
		this->setHeightWidth(two, three);
		break;
	case 6: // Z shape
		curr_shape[0][0] = HASHTAG; curr_shape[0][1] = HASHTAG; curr_shape[0][2] = ' '; curr_shape[0][3] = ' ';
		curr_shape[1][0] = ' '; curr_shape[1][1] = HASHTAG; curr_shape[1][2] = HASHTAG; curr_shape[1][3] = ' ';
		curr_shape[2][0] = ' '; curr_shape[2][1] = ' '; curr_shape[2][2] = ' '; curr_shape[2][3] = ' ';
		curr_shape[3][0] = ' '; curr_shape[3][1] = ' '; curr_shape[3][2] = ' '; curr_shape[3][3] = ' ';
		this->setHeightWidth(two, three);
		break;
	}
	//initializing the point array
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (curr_shape[i][j] == HASHTAG)
			{
				int jPlus4 = j + 4;
				point_arr[point_index].setValue(jPlus4, i);
				point_index++;
			}
		}
	}
	setPointArr(point_arr[0], point_arr[1], point_arr[2], point_arr[3]);
}
void Shape::rotate(Shape& actual_shape, Board& board, Input direction)
{//rotating the shape inside the shape's matrix
	Point point_arr[4];
	int point_index = 0;
	savePrevShape(actual_shape);
	if (direction == COUTERCLOCKWISE) //ROTATE counterclockwise
	{
		char temp = actual_shape.curr_shape[0][0];
		actual_shape.curr_shape[0][0] = actual_shape.curr_shape[3][0];
		actual_shape.curr_shape[3][0] = actual_shape.curr_shape[3][3];
		actual_shape.curr_shape[3][3] = actual_shape.curr_shape[0][3];
		actual_shape.curr_shape[0][3] = temp;

		temp = actual_shape.curr_shape[0][1];
		actual_shape.curr_shape[0][1] = actual_shape.curr_shape[2][0];
		actual_shape.curr_shape[2][0] = actual_shape.curr_shape[3][2];
		actual_shape.curr_shape[3][2] = actual_shape.curr_shape[1][3];
		actual_shape.curr_shape[1][3] = temp;

		temp = actual_shape.curr_shape[0][2];
		actual_shape.curr_shape[0][2] = actual_shape.curr_shape[1][0];
		actual_shape.curr_shape[1][0] = actual_shape.curr_shape[3][1];
		actual_shape.curr_shape[3][1] = actual_shape.curr_shape[2][3];
		actual_shape.curr_shape[2][3] = temp;

		temp = actual_shape.curr_shape[1][1];
		actual_shape.curr_shape[1][1] = actual_shape.curr_shape[2][1];
		actual_shape.curr_shape[2][1] = actual_shape.curr_shape[2][2];
		actual_shape.curr_shape[2][2] = actual_shape.curr_shape[1][2];
		actual_shape.curr_shape[1][2] = temp;
	}
	if (direction == CLOCKWISE) //ROTATE clockwise
	{
		char temp = actual_shape.curr_shape[3][3];
		actual_shape.curr_shape[3][3] = actual_shape.curr_shape[3][0];
		actual_shape.curr_shape[3][0] = actual_shape.curr_shape[0][0];
		actual_shape.curr_shape[0][0] = actual_shape.curr_shape[0][3];
		actual_shape.curr_shape[0][3] = temp;

		temp = actual_shape.curr_shape[1][3];
		actual_shape.curr_shape[1][3] = actual_shape.curr_shape[3][2];
		actual_shape.curr_shape[3][2] = actual_shape.curr_shape[2][0];
		actual_shape.curr_shape[2][0] = actual_shape.curr_shape[0][1];
		actual_shape.curr_shape[0][1] = temp;

		temp = actual_shape.curr_shape[2][3];
		actual_shape.curr_shape[2][3] = actual_shape.curr_shape[3][1];
		actual_shape.curr_shape[3][1] = actual_shape.curr_shape[1][0];
		actual_shape.curr_shape[1][0] = actual_shape.curr_shape[0][2];
		actual_shape.curr_shape[0][2] = temp;

		temp = actual_shape.curr_shape[1][2];
		actual_shape.curr_shape[1][2] = actual_shape.curr_shape[2][2];
		actual_shape.curr_shape[2][2] = actual_shape.curr_shape[2][1];
		actual_shape.curr_shape[2][1] = actual_shape.curr_shape[1][1];
		actual_shape.curr_shape[1][1] = temp;
	}
	int _x = coordinate.getX();
	int _y = coordinate.getY();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (actual_shape.curr_shape[i][j] == HASHTAG)
			{
				int newX = _x + j;
				int newY = _y + i;
				point_arr[point_index].setValue(newX, newY);
				point_index++;
			}
		}
	}
	actual_shape.setPointArr(point_arr[0], point_arr[1], point_arr[2], point_arr[3]);
	actual_shape.setHeightWidth(actual_shape.getWidth(), actual_shape.getHeight()); //switching the height and width as the shape rotates
}
int Shape::getHeight()
{
	return this->height;
}
int Shape::getWidth()
{
	return this->width;
}
void Shape::setHeightWidth(const int& h, const int& w)
{
	this->height = h;
	this->width = w;
}
void Shape::savePrevShape(Shape& actual_shape)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			actual_shape.prev_shape[i][j] = actual_shape.curr_shape[i][j];
		}
	}
	setPrevPointArr(point_arr[0], point_arr[1], point_arr[2], point_arr[3]);
}
int Shape::firstOccurenceOfCurrShapeK(Shape& curr_shape)
{ //returning the first occurence of the shape inside the shape's matrix from the bottom - in which row it occured
	for (int k = 3; k >= 0; k--)
	{
		for (int l = 0; l < 4; l++)
		{
			if (curr_shape.curr_shape[k][l] == HASHTAG)
			{
				return k;
			}
		}
	}
}
int Shape::firstOccurenceOfCurrShapeL(Shape& curr_shape)
{//returning the first occurence of the shape inside the shape's matrix from the left - in which column it occured
	for (int l = 0; l <= 3; l++)
	{
		for (int k = 0; k <= 3; k++)
		{
			if (curr_shape.curr_shape[k][l] == HASHTAG)
			{
				return l;
			}
		}
	}
}
void Shape::ableToMove(Shape& curr_shape, Board& board)
{
	if (isStuckV2(curr_shape, board))
	{
		canMove = false;
	}
}
