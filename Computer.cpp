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
#include <vector>
#include <math.h>
int Computer::baseWidth(Shape& curr_shape)
{
	int base_counter = 0;
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (curr_shape.curr_shape[i][j] == HASHTAG)
			{
				while (curr_shape.curr_shape[i][j] == HASHTAG)
				{
					base_counter++;
					j++;
				}
				return base_counter;
			}
		}
	}
}
bool Computer::emptySpotsBelow(Board& board, Shape& curr_shape)
{//we are getting the future position of curr shape and the current board
	for (int i = 0; i < 4; i++)
	{
		int x = curr_shape.getPointArr()[i].getX();
		int y = curr_shape.getPointArr()[i].getY();
		if (board.board[y + 1][x] == ' ')
		{
			return false; //we found an empty cell below our shape - not an ideal position
		}
	}
	return true;
}
bool Computer::isLegalPosition(Board& board, Shape& tmp_shape)
{
	for (int i = 0; i < 4; i++)
	{
		int x = tmp_shape.getPointArr()[i].getX();
		int y = tmp_shape.getPointArr()[i].getY();
		if (board.board[y][x] == HASHTAG || x < 0 || x > 11 || y > 17)
		{
			return false;
		}
	}
	return true;
}
Input* Computer::chooseRandPosition(Board& board, Shape& curr_shape, int& path_size)
{
	Shape tmp_shape = curr_shape;
	Point right_bottom(0, 0);
	Point position[4];
	int which_row = 17;
	int num_of_rotations;
	bool found = false;
	Board temp_board = board;
	Point save_point_arr[4];
	Input* path = nullptr;
	Input* curr_path = nullptr;
	int cols_arr[12];
	bool flag = false;




	for (int k = 0; k < 4; k++) //deleting the shape itself from the board after it dropped
	{
		int x = curr_shape.getPointArr()[k].getX();
		int y = curr_shape.getPointArr()[k].getY();
		temp_board.board[y][x] = ' ';
	}
	while (1)
	{
		for (int i = 0; i < 11; i++)
		{
			cols_arr[i] = -1; //initializing the cells of the array to a value that shouldn't exist
		}
		while (!found)
		{
			flag = false;
			num_of_rotations = rand() % 3;
			for (int i = 0; i < num_of_rotations; i++) //rotating the shape random times
			{
				tmp_shape.rotate(tmp_shape, temp_board, CLOCKWISE);
			}


			right_bottom.convert(0, 0);
			for (int l = 0; l < 4; l++) //saving the right bottom coordinates
			{
				save_point_arr[l] = tmp_shape.getPointArr()[l];
				if (tmp_shape.getPointArr()[l].getY() >= right_bottom.getY())
				{
					if (tmp_shape.getPointArr()[l].getY() > right_bottom.getY())
					{
						right_bottom = tmp_shape.getPointArr()[l];
					}
					if (tmp_shape.getPointArr()[l].getX() > right_bottom.getX())
					{
						right_bottom = tmp_shape.getPointArr()[l];
					}

				}
			}

			int rand_col = rand() % 12;
			int dif_x = rand_col - right_bottom.getX(); // where do we need to go in the board 
			int dif_y = which_row - right_bottom.getY(); // where do we need to go in the board 
			for (int m = 0; m < 4; m++) // init Point array with the future coordinates
			{
				int new_x = tmp_shape.getPointArr()[m].getX() + dif_x;
				int new_y = tmp_shape.getPointArr()[m].getY() + dif_y;
				tmp_shape.getPointArr()[m].setValue(new_x, new_y);
			}

			if (isLegalPosition(board, tmp_shape) && pathFinding(temp_board, tmp_shape, save_point_arr, curr_path, path_size))
			{
				found = true;
			}
			if (!found)
			{
				if (cols_arr[rand_col] != rand_col)
				{
					cols_arr[rand_col] = rand_col;
				}
			}
			for (int i = 0; i < 12; i++)
			{
				if (cols_arr[i] != i)
				{
					flag = true;
					break;
				}
			}
			if (!flag) break;
		}
		if (found) break;
		which_row--;
	}


	for (int t = 0; t < 4; t++)
	{
		tmp_shape.getPointArr()[t] = save_point_arr[t];
	}

	int new_size = path_size + num_of_rotations;
	path = new Input[new_size];
	for (int r = new_size - 1; r >= num_of_rotations; r--) //adding the rotations to the path_array
	{
		path[r] = curr_path[r - num_of_rotations];
	}

	for (int z = 0; z < num_of_rotations; z++)
	{
		path[z] = CLOCKWISE;
	}
	path_size = new_size;

	return path;

}
void Computer::executeAction(Shape& curr_shape, Board& board, Input action)
{
	switch (action)
	{
	case LEFT:
	{
		board.move(curr_shape, LEFT);
		break;

	}
	case RIGHT:
	{
		board.move(curr_shape, RIGHT);
		break;
	}
	case CLOCKWISE:
	{
		curr_shape.rotate(curr_shape, board, CLOCKWISE);
		board.updateBoard(curr_shape, CLOCKWISE);
		break;
	}
	case COUTERCLOCKWISE:
	{

		curr_shape.rotate(curr_shape, board, COUTERCLOCKWISE);
		board.updateBoard(curr_shape, COUTERCLOCKWISE);

		break;
	}
	}
}
bool Computer::pathFinding(Board& board, Shape& future_position, Point* origin_points, Input*& path, int& path_size)
{//in this function we are getting a point (called future_point) and ut's origin and we are building it's path in between.
	//we are going from the future location until the future shape meets the origin one.

	vector <Input> input_path;
	bool reach_to_top = false; bool left_option = true; bool right_option = true; bool up_option = true; bool found = false;
	Point future_right_bottom; Point origin_right_bottom;
	Shape temp_future_position = future_position;

	for (int l = 0; l < 4; l++) //updating the right bottom coordinates
	{
		if (future_position.getPointArr()[l].getY() >= future_right_bottom.getY())
		{
			if (future_position.getPointArr()[l].getY() > future_right_bottom.getY())
			{
				future_right_bottom = future_position.getPointArr()[l];
			}
			if (future_position.getPointArr()[l].getX() > future_right_bottom.getX())
			{
				future_right_bottom = future_position.getPointArr()[l];
			}
		}
		if (origin_points[l].getY() >= origin_right_bottom.getY())
		{
			if (origin_points[l].getY() > origin_right_bottom.getY())
			{
				origin_right_bottom = origin_points[l];
			}
			if (origin_points[l].getX() > origin_right_bottom.getX())
			{
				origin_right_bottom = origin_points[l];
			}
		}

	}
	int future_x = future_right_bottom.getX();
	int future_y = future_right_bottom.getY();
	int dif_x = future_right_bottom.getX() - origin_right_bottom.getX();
	while (!reach_to_top)
	{
		if (dif_x > 0 && (!input_path.empty() && (input_path.back() == LEFT))) //we want to avoid an iternal loop of left - right - left - right...
		{//if the shape is still to the left of the origin point, but the last move was RIGHT, it means that we couldnt go left in the last move. 
			//this is why we dont want to go left now - so we update the left_option flag to false
			left_option = false;
			right_option = true; up_option = true; found = false;
		}
		else if (dif_x < 0 && (!input_path.empty() && (input_path.back() == RIGHT))) //same explanation as the left option
		{
			right_option = false;
			left_option = true; up_option = true; found = false;
		}
		else
		{
			left_option = true; right_option = true; up_option = true; found = false;
		}
		if (future_x == origin_right_bottom.getX() && future_y == origin_right_bottom.getY())
		{
			reach_to_top = true;
			found = true;
		}
		while (!found)
		{
			if (((dif_x > 0) && left_option) || !up_option)  //move left
			{
				for (int i = 0; i < 4; i++)
				{
					int x = temp_future_position.getPointArr()[i].getX();
					int y = temp_future_position.getPointArr()[i].getY();

					if (board.board[y][x - 1] == HASHTAG || x <= 0) // can't move left
					{
						left_option = false;
						break;
					}
				}
				if (!left_option/* || !right_option*/)
				{

				}
				else
				{
					input_path.push_back(RIGHT);
					dif_x--;
					found = true;
					future_x--;
					future_right_bottom.setValue(future_x, future_y);
					for (int i = 0; i < 4; i++)
					{
						int temp_x = temp_future_position.getPointArr()[i].getX() - 1;
						int temp_y = temp_future_position.getPointArr()[i].getY();
						temp_future_position.getPointArr()[i].setValue(temp_x, temp_y);
					}
					break;
				}
			}
			if (((dif_x < 0) && right_option) || (!up_option && !left_option))//move right
			{
				for (int i = 0; i < 4; i++)
				{
					int x = temp_future_position.getPointArr()[i].getX();
					int y = temp_future_position.getPointArr()[i].getY();

					if (board.board[y][x + 1] == HASHTAG || x >= 11) // can't move left
					{
						right_option = false;
						break;
					}
				}
				if (right_option)
				{
					input_path.push_back(LEFT);
					dif_x++;
					found = true;
					future_x++;
					future_right_bottom.setValue(future_x, future_y);
					for (int i = 0; i < 4; i++)
					{
						int temp_x = temp_future_position.getPointArr()[i].getX() + 1;
						int temp_y = temp_future_position.getPointArr()[i].getY();
						temp_future_position.getPointArr()[i].setValue(temp_x, temp_y);
					}
					break;
				}
			}
			if (dif_x == 0 || !left_option || !right_option) //keep up 
			{
				for (int i = 0; i < 4; i++)
				{
					int x = temp_future_position.getPointArr()[i].getX();
					int y = temp_future_position.getPointArr()[i].getY();

					if (board.board[y - 1][x] == HASHTAG || y <= 0) // can't move up
					{
						up_option = false;
						break;
					}
				}

				if (up_option)
				{
					input_path.push_back(DOWN);
					found = true;
					future_y--;
					future_right_bottom.setValue(future_x, future_y);
					for (int i = 0; i < 4; i++)
					{
						int temp_x = temp_future_position.getPointArr()[i].getX();
						int temp_y = temp_future_position.getPointArr()[i].getY() - 1;
						temp_future_position.getPointArr()[i].setValue(temp_x, temp_y);
					}
					break;
				}
			}
			if (!up_option && !left_option && !right_option)
			{
				while (!input_path.empty())
				{
					input_path.pop_back();
				}
				return false; //the shape is stuck - so the position is not valid
			}
		}
	}
	path_size = input_path.size();
	path = new Input[path_size];
	for (int j = 0; j < path_size; j++)
	{
		path[j] = input_path.back();
		input_path.pop_back();
	}
	while (!input_path.empty())
	{
		input_path.pop_back();
	}

	return true;
}
Input* Computer::futurePosition(Board& board, Shape& curr_shape, int& path_size)// return location array of the best spot
{//in this function we are finding the ultimate position for the shape we just got to the board. 
	//we are checking 4 parameters to determine the best position: height differences between the columns(wether the shape has hightened the columns),
	//wether there are full lines we can clear, 
	//wether there are empty spots we cannot clear (jailes spaces) and bumpinness - height difference between all the columns.
	//each criteria gets a score, so we are saving the best score - and this is our best position.
	Shape tmp_shape = curr_shape;
	Point right_bottom(0, 0);
	int sum_score = 0, max_score = 0;
	Point best_position[4];
	int which_row = 17;
	bool flag_position = false;
	Point save_point_arr[4];
	Input* curr_path = nullptr;
	Input* curr_best_path = nullptr;
	int best_num_of_rotations;
	Board temp_board = board;
	int max_path_size = 0;
	int curr_path_size = 0;


	for (int k = 0; k < 4; k++) //clearing the temp board from the shape that has just dropped
	{
		int x = curr_shape.getPointArr()[k].getX();
		int y = curr_shape.getPointArr()[k].getY();
		temp_board.board[y][x] = ' ';
	}


	while (!flag_position)
	{
		for (int i = 0; i < 3; i++) //loop every rotation of the shape
		{
			right_bottom.convert(0, 0);
			tmp_shape.rotate(tmp_shape, temp_board, CLOCKWISE);
			for (int l = 0; l < 4; l++) //updating the right bottom coordinates
			{
				save_point_arr[l] = tmp_shape.getPointArr()[l];
				if (tmp_shape.getPointArr()[l].getY() >= right_bottom.getY())
				{
					if (tmp_shape.getPointArr()[l].getY() > right_bottom.getY())
					{
						right_bottom = tmp_shape.getPointArr()[l];
					}
					if (tmp_shape.getPointArr()[l].getX() > right_bottom.getX())
					{
						right_bottom = tmp_shape.getPointArr()[l];
					}
				}
			}
			for (int j = 11; j >= 0; j--) //going threw the bottom row to check which position is optimal
			{
				int dif_x = j - right_bottom.getX(); // where do we need to go in the board 
				int dif_y = which_row - right_bottom.getY(); // where do we need to go in the board 
				for (int m = 0; m < 4; m++) // init Point array with the future coordinates
				{
					int new_x = tmp_shape.getPointArr()[m].getX() + dif_x;
					int new_y = tmp_shape.getPointArr()[m].getY() + dif_y;
					tmp_shape.getPointArr()[m].setValue(new_x, new_y);
				}
				if (isLegalPosition(board, tmp_shape) && pathFinding(temp_board, tmp_shape, save_point_arr, curr_path, curr_path_size))
				{
					flag_position = true;
					sum_score = heightDifference(board, tmp_shape) + fullLines(board, tmp_shape)
						+ jailedSpaces(board, tmp_shape) + bumpiness(board, tmp_shape);
					if (sum_score >= max_score)
					{
						max_path_size = curr_path_size;
						max_score = sum_score;
						for (int n = 0; n < 4; n++)
						{
							best_position[n] = tmp_shape.getPointArr()[n]; //copying the best position to save it
						}
						best_num_of_rotations = i + 1;
						int new_size = max_path_size + best_num_of_rotations;
						curr_best_path = new Input[new_size];
						for (int p = 0; p < max_path_size; p++)
						{
							curr_best_path[p] = curr_path[p];
						}
						max_path_size = new_size;
						delete[] curr_path;
					}
				}
				for (int t = 0; t < 4; t++)
				{
					tmp_shape.getPointArr()[t] = save_point_arr[t];
				}
			}
		}
		which_row--;
	}

	Input* best_path = new Input[max_path_size];
	for (int r = max_path_size - 1; r >= best_num_of_rotations; r--) //adding the rotations to the path_array
	{
		best_path[r] = curr_best_path[r - best_num_of_rotations];
	}
	delete[] curr_best_path;

	for (int z = 0; z < best_num_of_rotations; z++)
	{
		best_path[z] = CLOCKWISE;
	}
	path_size = max_path_size;

	return best_path;
}
int Computer::heightDifference(Board& board, Shape& tmp_shape)
{
	int save_top_row = 0;
	bool found = false;
	int max_y = 0;
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (board.board[i][j] == HASHTAG)
			{
				save_top_row = i;
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}
	for (int l = 0; l < 4; l++)
	{
		if (tmp_shape.getPointArr()[l].getY() > max_y)
		{
			max_y = tmp_shape.getPointArr()[l].getY();
		}
	}

	int dif_height = save_top_row - max_y;
	if (abs(dif_height) > 2) return 1; // worst case
	if (abs(dif_height) <= 2 && abs(dif_height) > 0) return 5;
	if (abs(dif_height) == 0) return 10; //best case 


}
int Computer::fullLines(Board& board, Shape& tmp_shape) // return how many full lines we will get with the current postion
{
	Board tmp_board = board;
	int counter_full_line = 0;
	bool full_line = true;
	for (int l = 0; l < 4; l++)
	{
		int x = tmp_shape.getPointArr()[l].getX();
		int y = tmp_shape.getPointArr()[l].getY();
		tmp_board.board[y][x] = HASHTAG;
	}
	for (int i = 0; i < 18; i++)
	{
		full_line = true;
		for (int j = 0; j < 12; j++)
		{
			if (tmp_board.board[i][j] == ' ')
			{
				full_line = false;
				break;
			}
		}
		if (full_line)
		{
			counter_full_line++;
		}

	}

	if (counter_full_line == 0) return 1;
	if (counter_full_line == 1) return 5;
	if (counter_full_line > 1) return 10;

}
int Computer::jailedSpaces(Board& board, Shape& tmp_shape)
{
	Board tmp_board = board;
	int counter = 0, count_jailed_spaces = 0;
	for (int l = 0; l < 4; l++)
	{
		int x = tmp_shape.getPointArr()[l].getX();
		int y = tmp_shape.getPointArr()[l].getY();
		tmp_board.board[y][x] = HASHTAG;
	}

	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			counter = 0;
			if (tmp_board.board[i][j] == ' ')
			{
				if (tmp_board.board[i - 1][j] == HASHTAG)
				{
					if (tmp_board.board[i + 1][j] == HASHTAG || i + 1 > 17)
					{
						counter++;
					}
					if (tmp_board.board[i][j + 1] == HASHTAG || j + 1 > 11)
					{
						counter++;
					}
					if (tmp_board.board[i][j - 1] == HASHTAG || j - 1 < 0)
					{
						counter++;
					}
				}
			}
			if (counter > 1)
			{
				count_jailed_spaces++;
			}
		}
	}
	if (count_jailed_spaces > 1) return 1;
	if (count_jailed_spaces == 1) return 5;
	if (count_jailed_spaces == 0) return 10;


}
int Computer::bumpiness(Board& board, Shape& tmp_shape)
{
	Board tmp_board = board;
	int counter = 0, count_jailed_spaces = 0;
	int curr = 0, prev = 0;  // save height of two cloumn 
	int curr_dif = 0, sum_dif = 0;
	for (int l = 0; l < 4; l++)
	{
		int x = tmp_shape.getPointArr()[l].getX();
		int y = tmp_shape.getPointArr()[l].getY();
		tmp_board.board[y][x] = HASHTAG;
	}
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (tmp_board.board[j][i] == HASHTAG) // finding first occurence which present the height cloumn  
			{
				curr = j;
				break;
			}
		}
		curr_dif = curr - prev;
		sum_dif += abs(curr_dif);
	}
	if (sum_dif > 10) return 1;
	if (sum_dif < 10 && sum_dif > 7) return 5;
	if (sum_dif < 8) return 10;
}