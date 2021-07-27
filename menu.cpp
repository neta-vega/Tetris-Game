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
void Menu::getChoice(int& choice_num) const
{
	cin >> choice_num;
	cin.ignore(1, '\n'); //ignoring enter after menu choice
}
bool Menu::setChoice(int choice)
{ // validates user's choice
	if (choice > 0 && choice < 10 && choice != 5 && choice != 6 && choice != 7)
	{
		return true;
	}
	cout << "Please select a number between 1-4 or 8-9: " << endl;
	return false;
}
int Menu::menuChoice(bool pause)
{
	int choice;


	if (pause)
	{
		cout << "Tetris:\n Please select from the following: \n (1) start a new game- Human vs Human\n (2) start a new game- Human vs Computer\n (3) start a new game- Computer vs Computer\n (4) Continue a paused game\n (8) Present instructions and keys\n (9) EXIT\n" << endl;
	}
	else
	{
		cout << "Tetris:\n Please select from the following: \n (1) start a new game- Human vs Human\n (2) start a new game- Human vs Computer\n (3) start a new game- Computer vs Computer\n (8) Present instructions and keys\n (9) EXIT\n" << endl;
	}
	do {
		getChoice(choice);
	} while (!setChoice(choice));


	return choice;
}
void Menu::instructions()
{
	clear_screen();
	gotoxy(0, 4);
	cout << "Hi player 1! here are the instuctions for this Tetris game:";
	gotoxy(0, 5);
	cout << "Press A or a to move left";
	gotoxy(0, 6);
	cout << "Press D or d to move right";
	gotoxy(0, 7);
	cout << "Press S or s to rotate clockwise";
	gotoxy(0, 8);
	cout << "Press W or w to rotate counterclockwise";
	gotoxy(0, 9);
	cout << "Or press X or x to drop";

	gotoxy(0, 15);
	cout << "Hi player 2! here are the instuctions for this Tetris game:";
	gotoxy(0, 16);
	cout << "Press J or j to move left";
	gotoxy(0, 17);
	cout << "Press L or l to move right";
	gotoxy(0, 18);
	cout << "Press K or k to rotate clockwise";
	gotoxy(0, 19);
	cout << "Press I or i to rotate counterclockwise";
	gotoxy(0, 20);
	cout << "Or press M or m to drop";


	while (!_kbhit())
	{
		if (_kbhit())
			break;
	}
	clear_screen();
	return;
}
int Menu::whichLevel()
{
	int choice;
	cout << "Please select level from the following opetions: \n (1)BEST \n (2)GOOD \n (3)NOVICE " << endl;
	cin >> choice;
	cin.ignore(1, '\n');
	return choice;
}