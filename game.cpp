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

void Game::game()
{
	Menu menu;
	int choice = menu.menuChoice(false); //game just started - no pause pressed 
	bool finish = false;
	Player* p1;
	Player* p2;
	if (getExit())
	{
		return;
	}

	while (!finish)
	{
		switch (choice)
		{
		case 1: //Human VS Human
		{

			p1 = new Human;
			p2 = new Human;
			this->startNewGame(p1, p2);
			break;
		}
		case 2://Human VS Computer
		{
			int level = menu.whichLevel();
			p1 = new Human;
			p2 = new Computer;
			((Computer*)p2)->setLevel(level);
			this->startNewGame(p1, p2);
			break;
		}
		case 3://Computer VS Computer
		{
			int level = menu.whichLevel();
			p1 = new Computer;
			((Computer*)p1)->setLevel(level);
			p2 = new Computer;
			((Computer*)p2)->setLevel(level);
			this->startNewGame(p1, p2);
			break;
		}
		case 8:
		{
			menu.instructions();
			break;
		}
		case 9:
		{
			finish = true;
			return;
		}
		}
		if (getExit())
		{
			return;
		}
		choice = menu.menuChoice(false);
	}
}
void Game::startNewGame(Player* p1, Player* p2)
{
	Bomb bomb_P1;
	Bomb bomb_P2;
	Board b_P1;
	Board b_P2;
	Shape s_P1;
	Shape s_P2;
	Menu menu;
	int cmp_input_index_1 = 0, cmp_path_size_1 = 0;
	int cmp_input_index_2 = 0, cmp_path_size_2 = 0;
	Input* cmp_path_1 = nullptr;
	Input* cmp_path_2 = nullptr;
	Input* cmp_rand_path_2 = nullptr;
	Input* cmp_rand_path_1 = nullptr;
	int counter_p1 = 0, counter_p2 = 0;
	bool flag = false;
	char p1_keys[10] = { 'a', 'A', 'd', 'D', 's', 'S', 'w', 'W', 'x', 'X' };
	char p2_keys[10] = { 'j', 'J', 'l', 'L', 'k', 'K', 'i', 'I', 'm', 'M' };

	if ((strcmp(p1->getType(), "Human") == 0))
	{
		((Human*)p1)->setKeys(p1_keys);
	}
	if ((strcmp(p2->getType(), "Human") == 0))
	{
		((Human*)p2)->setKeys(p2_keys);
	}
	clear_screen();


	b_P1.dropShape(s_P1);
	b_P2.dropShape(s_P2);
	b_P1.printBoard(1);
	b_P2.printBoard(2);

	while (!b_P1.getWin() && !b_P2.getWin()) //the game i stopping if someone won
	{
		while (1)
		{
			hideCursor();
			s_P1.ableToMove(s_P1, b_P1);
			s_P2.ableToMove(s_P2, b_P2);
			int i = 0;
			while (i < 20) //according to Amir, it's recommended to get more than one keyboard hit in each loop from both players
			{
				if (_kbhit())
				{
					KbHit(p1, p2, b_P1, b_P2, s_P1, s_P2, menu, *this);
					if (getExit())
					{
						return;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
				}
				i++;
			}
			if ((strcmp(p1->getType(), "Computer") == 0) && cmp_path_size_1 == 0) // the second condition is to init path only once for the curr shape
			{
				cmp_path_1 = ((Computer*)p1)->futurePosition(b_P1, s_P1, cmp_path_size_1);
				cmp_input_index_1 = 0;
			}
			if ((strcmp(p2->getType(), "Computer") == 0) && cmp_path_size_2 == 0)
			{
				cmp_path_2 = ((Computer*)p2)->futurePosition(b_P2, s_P2, cmp_path_size_2);
				cmp_input_index_2 = 0;
			}
			s_P1.ableToMove(s_P1, b_P1);
			s_P2.ableToMove(s_P2, b_P2);

			if (((strcmp(p1->getType(), "Computer") == 0) && (cmp_input_index_1 == (cmp_path_size_1))) || ((strcmp(p1->getType(), "Human") == 0) && !s_P1.getCanMove()))//empty array of computer's move or human shape cannot move 
			{
				b_P1.removeFullLine();
				counter_p1++;
				if (counter_p1 % 20 == 0 && counter_p1 > 0)
				{
					if (strcmp(p1->getType(), "Computer") == 0)
					{
						Point where_to_explode = bomb_P1.whereToExplode(b_P1);
						int bomb_path_size = 0;
						Input* bomb_path = bomb_P1.bombPath(b_P1, where_to_explode, bomb_path_size);
						bomb_P1.dropBomb(b_P1);
						b_P1.printBoard(1);
						for (int i = 0; i < bomb_path_size; i++)
						{
							bomb_P1.moveBomb(b_P1, bomb_path[i]);
							b_P1.printBoard(1);
							std::this_thread::sleep_for(std::chrono::milliseconds(50));
						}
						bomb_P1.explode(b_P1);
						delete[] bomb_path;
					}
					else
					{
						bomb_P1.startBomb(b_P1, 1, p1);
					}
				}
				b_P1.dropShape(s_P1);
				delete[] cmp_path_1;
				cmp_path_size_1 = 0;
				cmp_input_index_1 = 0;
				if (((Computer*)p1)->getLevel() == 2 && counter_p1 % 40 == 0)
				{
					cmp_path_1 = ((Computer*)p1)->chooseRandPosition(b_P1, s_P1, cmp_path_size_1);
				}
				else if (((Computer*)p1)->getLevel() == 3 && counter_p1 % 11 == 0)
				{
					cmp_path_1 = ((Computer*)p1)->chooseRandPosition(b_P1, s_P1, cmp_path_size_1);
				}
				flag = true;
				s_P1.setCanMove(flag);
			}
			else
			{
				if ((strcmp(p1->getType(), "Computer") == 0))
				{
					if (cmp_path_1[cmp_input_index_1] == DOWN)
					{
						b_P1.lowerShape(s_P1);
						cmp_input_index_1++;
					}
					else
					{
						((Computer*)p1)->executeAction(s_P1, b_P1, cmp_path_1[cmp_input_index_1]);
						cmp_input_index_1++;
					}
				}
				else
				{
					b_P1.lowerShape(s_P1);
				}
			}

			if (((strcmp(p2->getType(), "Computer") == 0) && (cmp_input_index_2 == (cmp_path_size_2))) || ((strcmp(p2->getType(), "Human") == 0) && !s_P2.getCanMove()))
			{
				b_P2.removeFullLine();
				counter_p2++;
				if (counter_p2 % 20 == 0 && counter_p2 > 0)
				{
					if (strcmp(p2->getType(), "Computer") == 0)
					{
						Point where_to_explode = bomb_P2.whereToExplode(b_P2);
						int bomb_path_size = 0;
						Input* bomb_path = bomb_P2.bombPath(b_P2, where_to_explode, bomb_path_size);
						bomb_P2.dropBomb(b_P2);
						b_P2.printBoard(2);
						for (int i = 0; i < bomb_path_size; i++)
						{
							bomb_P2.moveBomb(b_P2, bomb_path[i]);
							b_P2.printBoard(2);
							std::this_thread::sleep_for(std::chrono::milliseconds(50));

						}
						bomb_P2.explode(b_P2);
						delete[] bomb_path;
					}
					else
					{
						bomb_P2.startBomb(b_P2, 2, p2);
					}
				}

				b_P2.dropShape(s_P2);
				delete[] cmp_path_2;
				cmp_path_size_2 = 0;
				cmp_input_index_2 = 0;
				if (((Computer*)p2)->getLevel() == 2 && counter_p2 % 40 == 0)
				{
					cmp_path_2 = ((Computer*)p2)->chooseRandPosition(b_P2, s_P2, cmp_path_size_2);
				}
				else if (((Computer*)p2)->getLevel() == 3 && counter_p2 % 11 == 0)
				{
					cmp_path_2 = ((Computer*)p2)->chooseRandPosition(b_P2, s_P2, cmp_path_size_2);
				}
				flag = true;
				s_P2.setCanMove(flag);
			}
			else
			{
				if ((strcmp(p2->getType(), "Computer") == 0))
				{
					if (cmp_path_2[cmp_input_index_2] == DOWN)
					{
						b_P2.lowerShape(s_P2);
						cmp_input_index_2++;
					}
					else
					{
						((Computer*)p2)->executeAction(s_P2, b_P2, cmp_path_2[cmp_input_index_2]);
						cmp_input_index_2++;
					}

				}
				else
				{
					b_P2.lowerShape(s_P2);
				}

			}

			if (b_P1.getWin() || b_P2.getWin())
			{
				break;
			}

			b_P1.printBoard(1);
			b_P2.printBoard(2);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
	clear_screen();

	if (b_P1.getWin())
	{
		cout << "Player 2 is the winner!" << endl;
	}
	if (b_P2.getWin())
	{
		cout << "Player 1 is the winner!" << endl;
	}

	cout << "Press any key to continue" << endl;

	while (!_kbhit())
	{
		if (_kbhit())
			break;
	}
	clear_screen();

	return;
}