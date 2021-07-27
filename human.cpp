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

void Human::setKeys(char arr[10])
{//each plaer has a unique set of keys. this function will assign it to the player - based on out input
	for (int i = 0; i < 10; i++)
	{
		keys[i] = arr[i];
	}
}
bool Human::setPlayerInput(char input)
{//this function is checking if an input belong to the set of the player's keys
	for (int i = 0; i < 10; i++)
	{
		if (input == keys[i])
		{
			return true;
		}
	}
	return false;
}